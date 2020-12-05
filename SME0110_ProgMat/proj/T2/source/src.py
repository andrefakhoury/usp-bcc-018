# -*- coding: utf-8 -*-

import math
import time

from random import shuffle
from itertools import chain, combinations

import pandas as pd
import matplotlib.pyplot as plt

from ortools.linear_solver import pywraplp

def powerset(iterable, k):
    '''Generates the powerset for iterable with minimum size 2 and maximum size k'''
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(2, min(k, len(s))+1))

def read_data(filename):
    '''Reads graph data into list of float-tuples (x, y)'''
    coords = set()
    with open(filename, 'r') as f:
        lines = f.readlines()
    
    for l in lines:
        _, x, y = l.split()
        coords.add((float(x), float(y)))

    return list(coords)

def plot_solution(galaxies, solution, filename=None):
    '''
    Plots tour given galaxies
    
    Parameters
    ------------
    galaxies: list (graph as list of tuples (x,y))
    solution: list (TSP tour in the form [initial_node, ..., initial_node])
    '''
    x, y = list(zip(*galaxies))
    fig, ax = plt.subplots(1, 1, figsize=(10,10))
    ax.scatter(x=x, y=y, marker=r'$\star$', c='darkorange', s=128)
    
    for i in range(len(solution) - 1):
        u, v = solution[i] - 1, solution[i + 1] - 1
        ax.annotate("", xy=(x[u], y[u]), xytext=(x[v], y[v]), arrowprops=dict(arrowstyle='-', color='black', alpha=0.8, connectionstyle='arc3'))
    ax.set_facecolor('white')

    if filename is not None:
        plt.savefig(filename)
    else:
        plt.plot()

def solve_greedy(n, d):
    '''
    Solves TSP greedily (useful to find initial solution)
    
    Parameters
    ------------
    n: int (graph size)
    d: list (graph distance matrix)
    '''
    vis = set()
    nxt = [[0 for i in range(n)] for j in range(n)]

    u = 0
    vis.add(0)
    while len(vis) != n:
        closer = -1
        for i in range(n):
            if not i in vis:
                if closer == -1 or d[u][i] < d[u][closer]:
                    closer = i
        nxt[u][closer] = 1
        u = closer
        vis.add(u)
    nxt[u][0] = 1
    return nxt

def solve_random(n, d):
    '''
    Generates random solution to TSP (useful to find initial solution)
    
    Parameters
    ------------
    n: int (graph size)
    d: list (graph distance matrix)
    '''
    nxt = [[0 for i in range(n)] for j in range(n)]
    pos = [i for i in range(n)]

    shuffle(pos)
    pos += [pos[0]]

    for i in range(n):
        nxt[pos[i]][pos[i + 1]] = 1

    return nxt

def join_cycles(d, paths):
    '''
    Joins all subcycles by greedily making best edge-cuts 
    (generates valid solution from invalid one)

    
    Parameters
    ------------
    d: list (graph distance matrix)
    paths: list (subcycles)
    '''
    while len(paths) > 1:
        min_cost = -1
        for i in range(len(paths)):
            for j in range(len(paths)):
                if i == j:
                    continue
                for u_i in range(len(paths[i]) - 1):
                    for x_i in range(len(paths[j]) - 1):
                        u, v = paths[i][u_i] - 1, paths[i][u_i + 1] - 1
                        x, y = paths[j][x_i] - 1, paths[j][x_i + 1] - 1
                        cost = d[u][x] + d[y][v] - d[u][v] - d[x][y]
                        if min_cost == -1 or cost < min_cost:
                            min_cost = cost
                            best_i, best_j = i, j
                            best_u_i, best_x_i = u_i, x_i

        paths[best_j] = paths[best_j][:-1]
        paths[best_i] = paths[best_i][:(best_u_i + 1)] + (paths[best_j][:(best_x_i + 1)])[::-1] + paths[best_j][(best_x_i + 1):] + paths[best_i][(best_u_i + 1):]
        del paths[best_j]
    return paths[0]

#https://stackoverflow.com/questions/3838329/how-can-i-check-if-two-segments-intersect
def ccw(A,B,C):
    '''Cross product'''
    return (C[1]-A[1]) * (B[0]-A[0]) > (B[1]-A[1]) * (C[0]-A[0])

def intersect(A,B,C,D):
    '''Determines if two segments AB and CD intersect'''
    return ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D)

def opt2(galaxies, d, tour, k=-1):
    '''
    Performs the 2-OPT heuristic optimization to improve a solution.

    Parameters
    ------------
    galaxies: list (list of tuples containing each integer-point (x,y))
    d: list (matrix containing distances between each node, 0-based)
    tour: list (path containing the solution we want to improve, 1-based)
    k: int (number of iterations, -1 if as many as possible)
    '''
    i = 0
    while k == -1 or i < k:
        found = False
        best_diff = 0
        best_i, best_j = -1, -1
        for i in range(1, len(tour) - 1):
            for j in range(i+2, len(tour) - 1):
                A, B = galaxies[tour[i] - 1], galaxies[tour[i+1] - 1]
                C, D = galaxies[tour[j] - 1], galaxies[tour[j+1] - 1]

                if not intersect(A,B,C,D):
                    continue

                cur_cost = d[tour[i]-1][tour[i+1]-1] + d[tour[j]-1][tour[j+1]-1]
                new_cost = d[tour[i]-1][tour[j]-1] + d[tour[i+1]-1][tour[j+1]-1]

                if cur_cost - new_cost > best_diff:
                    found = True
                    best_diff = cur_cost - new_cost
                    best_i, best_j = i, j

        if found:
            tour[best_i+1:best_j+1] = reversed(tour[best_i+1:best_j+1])
            i += 1
        else:
            break

def compute_cost(n, d, path):
    '''Computes the cost of a given path'''
    cost = 0
    for i in range(n):
        cost += d[path[i] - 1][path[i + 1] - 1]
    return cost

def add_restrictions(solver, n, p, max_subcycle):
    '''
    Parameters
    ------------
    solver: MIP SCIP Solver
    n: int (graph size)
    p: MIP Solver binary variable
    max_subcycle: int (maximum size of the subcycles to be restricted)
    '''
    # Restriction 1 
    for i in range(n):
        solver.Add(p[i][i] == 0)

    # Restriction 2 
    for i in range(n):
        sum = 0
        for j in range(n):
            sum += p[i][j]
        solver.Add(sum == 1)

    # Restriction 3
    for i in range(n):
        sum = 0
        for j in range(n):
            sum += p[j][i]
        solver.Add(sum == 1)

    # Restriction 4 (partial)
    S = list(powerset(range(1, n+1), max_subcycle))
    for s in S:
        sum = 0
        for i in s:
            for j in s:
                sum += p[i-1][j-1]
        solver.Add(sum <= len(s) - 1)

def add_path_restrictions(solver, p, paths):
    # Restriction 4 (partial)
    for path in paths:
        sum = 0
        for i in range(len(path) - 1):
            for j in range(len(path) - 1):
                sum += p[path[i] - 1][path[j] - 1]
        solver.Add(sum <= len(path) - 2)

def solve(galaxies, max_subcycle=-1, time_limit=None, hint='greedy', opt_iter=-1):
    n = len(galaxies)
    d = [[round(math.hypot(i[0]-j[0], i[1]-j[1])) for i in galaxies] for j in galaxies]

    if max_subcycle == -1:
        max_subcycle = n

    # Create the mip solver with the SCIP backend and create the variables.
    solver = pywraplp.Solver.CreateSolver('SCIP')
    p = [[solver.IntVar(0, 1, f'p{i}_{j}') for j in range(1, n + 1)] for i in range(1, n + 1)]

    if hint == 'greedy': # use greedy solution as initial solution
        solver.SetHint([x for sublist in p for x in sublist], [x for sublist in solve_greedy(n, d) for x in sublist])
    elif hint == 'random': # use random solution as initial solution
        solver.SetHint([x for sublist in p for x in sublist], [x for sublist in solve_random(n, d) for x in sublist])

    add_restrictions(solver, n, p, max_subcycle)

    # Objective function
    sum = 0
    for i in range(n):
        for j in range(n):
            sum += p[i][j] * d[i][j]
    solver.Minimize(sum)

    if time_limit is not None:
        solver.SetTimeLimit(time_limit[0])
    status = solver.Solve()
    
    tries = 0
    max_tries = -1
    if time_limit is not None:
        max_tries = len(time_limit)

    best = -1
    best_path = []
    best_iter = -1

    total_nodes = 0

    while status == pywraplp.Solver.OPTIMAL or status == pywraplp.Solver.FEASIBLE:
        tries += 1
        total_nodes += solver.nodes()
        
        def next(i):
            for j in range(n):
                if p[i-1][j].solution_value() == 1:
                    return j + 1
            return -1
        
        # Recover tour using function next
        def get_path(start):
            path = [start]
            cur = next(start)
            while cur != start:
                path.append(cur)
                cur = next(cur)
            path.append(start)
            return path

        paths = [get_path(1)]
        ok = set(paths[0])
        for i in range(1, n + 1):
            if i not in ok:
                path_i = get_path(i)
                paths += [path_i]
                ok.update(path_i)
        
        assert len(ok) == n

        value = solver.Objective().Value()

        num_cycles = len(paths)
        if num_cycles > 1:
            add_path_restrictions(solver, p, paths)

        # Join cycles to obtain a valid solution from the current iteration.
        path = join_cycles(d, paths)

        # Calculate total cost
        total_cost = compute_cost(n, d, path)

        assert len(path) == n + 1

        # Store the best solution across all iterations
        if best == -1 or total_cost < best:
            best = total_cost
            best_path = path
            best_iter = tries

        if num_cycles == 1 or (max_tries != -1 and tries >= max_tries):
            # Perform opt-2 on the final solution
            opt2(galaxies, d, best_path, k=opt_iter)
            best = compute_cost(n, d, best_path)

            return status, best_iter, best, best_path, total_nodes

        if time_limit is not None:
            solver.SetTimeLimit(time_limit[tries])
        status = solver.Solve()
    else:
        return status, -1, -1.0 , [], -1

def time_per_iteration(iteration_time=60*1000, step=30*1000, max_time=30*60*1000):
    '''Generates a list of maximum times for each iteration'''
    l = []
    sum = 0

    while sum + iteration_time <= max_time:
        l.append(iteration_time)
        sum += iteration_time
        iteration_time += step

    return l

if __name__ == '__main__':
    instances = {
        'toy': {
            'filename': 'data/toy.tsp',
            'optimal_tour': 21.0,
            'time_limit': time_per_iteration(10*1000, 0),
            '2_opt_iter': -1, 
        },
        'western_sahara': {
            'filename': 'data/western_sahara.tsp',
            'optimal_tour': 27603.0,
            'time_limit': time_per_iteration(30*1000, 0),
            '2_opt_iter': -1, 
        },
        'djibouti': {
            'filename': 'data/djibouti.tsp',
            'optimal_tour': 6656.0,
            'time_limit': time_per_iteration(30*1000, 0),
            '2_opt_iter': -1,
        },
        'qatar': {
            'filename': 'data/qatar.tsp',
            'optimal_tour': 9352.0,
            'time_limit': time_per_iteration(45*1000, 10*1000),
            '2_opt_iter': -1,
        },
        'uruguay': {
            'filename': 'data/uruguay.tsp',
            'optimal_tour': 79114.0,
            'time_limit': time_per_iteration(60*1000, 20*1000),
            '2_opt_iter': -1, 
        },
        'luxemburgo': {
            'filename': 'data/luxemburgo.tsp',
            'optimal_tour': 11340.0,
            'time_limit': time_per_iteration(60*1000, 20*1000),
            '2_opt_iter': -1, 
        },
        'rwanda': {
            'filename': 'data/rwanda.tsp',
            'optimal_tour': 26051.0,
            'time_limit': time_per_iteration(60*1000, 20*1000),
            '2_opt_iter': -1, 
        },
        'zimbabwe': {
            'filename': 'data/zimbabwe.tsp',
            'optimal_tour': 95345.0,
            'time_limit': time_per_iteration(60*1000, 20*1000),
            '2_opt_iter': -1,
        },
    }

    results = pd.DataFrame(columns=['name', 'solution', 'total_nodes', 'best_iteration', 'time', 'hint', 'optimal_value'])
    for hint in ['random', 'greedy']:
        for key, instance in instances.items():
            print(f'Running {key} {hint}: ', end='', flush=True)
            data = read_data(instance['filename'])
    
            initial_time = time.time()
            _, best_iter, solution_value, path, total_nodes = solve(data, max_subcycle=2, time_limit=instance['time_limit'], hint=hint, opt_iter=instance['2_opt_iter'])
            final_time = time.time()
     
            delta = round(final_time - initial_time, 2)
     
            results = results.append({'name': instance['filename'], 
                'solution': solution_value, 
                'optimal_value': instance['optimal_tour'], 
                'best_iteration': best_iter, 'time': delta, 
                'hint': hint, 'total_nodes': total_nodes}, 
                ignore_index=True)
        
            print(f'--> {solution_value}/{instance["optimal_tour"]}, iteration {best_iter}, {total_nodes} nodes and {delta} time')
            plot_solution(data, path, filename=f'img/{key}_{hint}.png')

    random_results = results[results['hint'] == 'random']
    greedy_results = results[results['hint'] == 'greedy']

    random_results.to_csv('random_results.csv', index=False)
    greedy_results.to_csv('greedy_results.csv', index=False)
