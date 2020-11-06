# -*- coding: utf-8 -*-
import math
from ortools.linear_solver import pywraplp

from itertools import chain, combinations

def powerset(iterable):
    '''Generates the powerset of a given list'''
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(2, len(s)+1))

# Problem data
galaxies = [(1, 1), (4, 5), (10, 1), (7, 2), (3, 3)]
n = len(galaxies)
d = [[math.hypot(i[0]-j[0], i[1]-j[1]) for i in galaxies] for j in galaxies]

if __name__ == "__main__":
    # Create the mip solver with the SCIP backend.
    solver = pywraplp.Solver.CreateSolver('SCIP')

    p = [[solver.IntVar(0, 1, f'p{i}_{j}') for j in range(1, n + 1)] for i in range(1, n + 1)]
    print('Number of variables =', solver.NumVariables())

    # Guarantees that there is only one out-edge for each node
    for i in range(n):
        sum = 0
        for j in range(n):
            sum += p[i][j]
        solver.Add(sum == 1)

    # Guarantees that there is only one in-edge for each node
    for i in range(n):
        sum = 0
        for j in range(n):
            sum += p[j][i]
        solver.Add(sum == 1)

    # Guarantees that there is no self edge
    for i in range(n):
        solver.Add(p[i][i] == 0)

    # Guarantees there is no sub-cycle
    S = list(powerset(range(2, n+1)))
    for s in S:
        sum = 0
        for i in s:
            for j in s:
                sum += p[i-1][j-1]
        solver.Add(sum <= len(s) - 1)

    solver.NumConstraints()

    # Calculates the objective function
    sum = 0
    for i in range(n):
        for j in range(n):
            sum += p[i][j] * d[i][j]
    solver.Minimize(sum)

    status = solver.Solve()

    # Solution
    if status == pywraplp.Solver.OPTIMAL:
        print('Solution:')
        print('Objective value =', solver.Objective().Value())

        def next(i):
            for j in range(n):
                if p[i-1][j].solution_value() == 1:
                    return j + 1
            return -1

        print("Path found:", 1, end=' ')
        cur = next(1)
        while cur != 1:
            print(cur, end = ' ')
            cur = next(cur)
        print(1)
    else:
        print('The problem does not have an optimal solution.')