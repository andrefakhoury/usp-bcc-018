import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.FileNotFoundException;
import java.util.TreeMap;

import static org.junit.jupiter.api.Assertions.*;

class GraphTest {

    private Graph graph;

    @BeforeEach
    void setup() {
        try {
            graph = new Graph("input.txt");
        } catch (FileNotFoundException ex) {
            assert(false);
        }
    }

    @Test
    void testString() {
        String gr = graph.toString();
        assertNotNull(gr);
    }

    @Test
    void wrongFile() {
        assertThrows(FileNotFoundException.class, () -> new Graph("aaa"));
    }

    @Test
    void minDist() {
        TreeMap<String, Integer> minDist = graph.minDist("S.J.Rio_Preto");
        TreeMap<String, Integer> expected = new TreeMap<>();

        expected.put("Campinas", 365);
        expected.put("Limeira", 310);
        expected.put("Mogi_Mirim", 369);
        expected.put("Ribeirão_Preto", 211);
        expected.put("Rio_Claro", 272);
        expected.put("S.J.Rio_Preto", 0);
        expected.put("São_Carlos", 207);

        assertEquals(minDist, expected);
    }
}