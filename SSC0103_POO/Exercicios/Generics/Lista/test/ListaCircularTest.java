import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class ListaCircularTest {
    private ListaCircular<Pair<Integer, String>> list;

    @BeforeEach
    void setup() {
        list = new ListaCircular<>(2);
    }

    @Test
    void insereInicio() {
        Pair<Integer, String> p = new Pair<>(10, "abc");
        list.insereInicio(p);
        assertNotNull(list.getList());
    }

    @Test
    void insereInicioCheio() {
        Pair<Integer, String> p = new Pair<>(10, "abc");
        list.insereInicio(p);
        list.insereInicio(p);
        assertThrows(ArrayIndexOutOfBoundsException.class, () -> list.insereInicio(p));
    }

    @Test
    void insereFim() {
        Pair<Integer, String> p = new Pair<>(10, "abc");
        list.insereFim(p);
        assertNotNull(list.getList());
    }

    @Test
    void insereFimCheio() {
        Pair<Integer, String> p = new Pair<>(10, "abc");
        list.insereFim(p);
        list.insereFim(p);
        assertThrows(ArrayIndexOutOfBoundsException.class, () -> list.insereFim(p));
    }

    @Test
    void removeInicio() {
        Pair<Integer, String> p = new Pair<>(10, "abc");
        list.insereFim(p);

        Pair<Integer, String> l = list.removeInicio();
        assertEquals(p, l);
    }

    @Test
    void removeInicioNull() {
        assertThrows(ArrayIndexOutOfBoundsException.class, () -> list.removeInicio());
    }

    @Test
    void removeFim() {
        Pair<Integer, String> p = new Pair<>(10, "abc");
        list.insereFim(p);

        Pair<Integer, String> l = list.removeFim();
        assertEquals(p, l);
    }

    @Test
    void removeFimNull() {
        assertThrows(ArrayIndexOutOfBoundsException.class, () -> list.removeFim());
    }

    @Test
    void getList() {
        list = new ListaCircular<>(100);

        list.insereFim(new Pair<Integer, String>(10, "abc"));
        list.insereFim(new Pair<Integer, String>(20, "abc"));
        list.insereFim(new Pair<Integer, String>(30, "abc"));
        list.removeFim();
        list.removeInicio();

        ArrayList<Pair<Integer, String>> arr = list.getList();
        Pair<Integer, String> f = arr.get(0);

        assertEquals(f, new Pair<Integer, String>(20, "abc"));
    }
}