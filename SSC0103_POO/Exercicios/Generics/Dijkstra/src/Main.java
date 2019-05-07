import java.io.FileNotFoundException;
import java.util.TreeMap;

public class Main {

    public static void main(String[] args) throws FileNotFoundException {
        Graph graph = new Graph("input.txt");
        System.out.println(graph);

        TreeMap<String, Integer> minDist = graph.minDist("S.J.Rio_Preto");

        System.out.println(">>Partindo de S.J.Rio_Preto");
        for (String v : minDist.keySet()) {
            System.out.println(v + " : " + minDist.get(v));
        }
    }
}
