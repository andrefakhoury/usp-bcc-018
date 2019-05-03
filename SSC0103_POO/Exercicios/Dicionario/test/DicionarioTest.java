import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class DicionarioTest {

    @Test
    void add() {
        Dicionario<String, Integer> freq = new Dicionario<>(100000);
        freq.add("Jorge", 1);
        freq.add("Jorge", 2);
    }

    @Test
    void get() {
        Dicionario<String, Integer> freq = new Dicionario<>(100000);
        freq.add("Jorge", 1);
        freq.add("Jorge", 2);

        Integer t1 = freq.get("Jorge");
        Integer t2 = freq.get("Abacaba");
    }

    @Test
    void contains() {
        Dicionario<String, Integer> freq = new Dicionario<>(100000);
        freq.add("Jorge", 1);
        freq.add("Jorge", 2);

        boolean t1 = freq.contains("Jorge");
        boolean t2 = freq.contains("Abacaba");
    }

    @Test
    void containsValue() {
        Dicionario<String, Integer> freq = new Dicionario<>(100000);
        freq.add("Jorge", 1);
        freq.add("Jorge", 2);

        boolean t1 = freq.containsValue(2);
        assertTrue(t1);

        boolean t2 = freq.containsValue(31);
        assertFalse(t2);

        Dicionario<String, Integer> maximo = new Dicionario<>(2);

        try {
            maximo.add("Jorge", 1);
            maximo.add("Maria", 2);
            maximo.add("Prexa", 5);
            assert(false);
        } catch (Exception ex) {
            assertTrue(maximo.contains("Jorge"));
        }
    }
}