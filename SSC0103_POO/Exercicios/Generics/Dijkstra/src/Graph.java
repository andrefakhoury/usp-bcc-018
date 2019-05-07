import java.io.FileNotFoundException;
import java.util.*;
import java.io.File;

/**
 * Classe que representa um grafo de strings
 */
public class Graph {
    private Map<String, Map<String, Integer>> edges;

    /**
     * Constroi um grafo a partir de um arquivo com os dados
     * @param fileName nome do arquivo
     */
    public Graph(String fileName) throws FileNotFoundException {
        edges = new TreeMap<>();

        File file = new File(fileName);
        Scanner sc = null;

        try {
            sc = new Scanner(file);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            throw new FileNotFoundException("Invalid file");
        }

        /**
         * Percorre o arquivo e monta o grafo
         */
        String u = sc.next();
        edges.put(u, new TreeMap<>());
        while (sc.hasNextLine()) {
            String v = sc.next();

            if (!sc.hasNextInt()) {
                u = v;
                edges.put(u, new TreeMap<>());
                continue;
            }

            int w = sc.nextInt();

            edges.get(u).put(v, w);
        }
    }

    /**
     * Retorna uma string que representa as ligacoes do grafo
     * @return string representante do grafo
     */
    public String toString() {
        String ret = "";
        for (String u : edges.keySet()) {
            ret += u + "\n";
            for (String v : edges.get(u).keySet()) {
                ret += ">>" + v + " - " + edges.get(u).get(v) + "\n";
            }
            ret += "\n";
        }

        return ret;
    }

    /**
     * Calcula e retorna a distancia minima de um vertice original a todos os outros
     * Utiliza o algoritmo de Dijkstra
     * @param S vertice inicial
     * @return map com distancia de s para o vertice chave
     */
    public TreeMap<String, Integer> minDist(String S) {
        TreeMap<String, Integer> dist = new TreeMap<>();
        PriorityQueue<Pair<Integer, String>> pq = new PriorityQueue<>(edges.size(), new PairComparator());

        pq.add(new Pair<>(0, S));
        dist.put(S, 0);

        while(!pq.isEmpty()) {
            String u = pq.poll().getSecond();

            for (String v : edges.get(u).keySet()) {
                Integer w = edges.get(u).get(v);

                if (!dist.containsKey(v) || dist.get(v) > dist.get(u) + w) {
                    dist.put(v, dist.get(u) + w);
                    pq.add(new Pair<>(dist.get(u) + w, v));
                }
            }
        }

        return dist;
    }
}

/**
 * Compara um par de int,String em ordem crescente
 */
class PairComparator implements Comparator<Pair<Integer, String>> {
    public int compare(Pair<Integer, String> p1, Pair<Integer, String> p2){
        return Integer.compare(p1.getFirst(), p2.getFirst());
    }
}
