import java.util.Objects;

public class Pair<T, S> {
    private T first;
    private S second;

    @SuppressWarnings("unchecked")
    public Pair() {
        first = (T) new Object();
        second = (S) new Object();
    }

    public Pair(T first, S second) {
        this.first = first;
        this.second = second;
    }

    public T getFirst() {
        return first;
    }

    public void setFirst(T first) {
        this.first = first;
    }

    public S getSecond() {
        return second;
    }

    public void setSecond(S second) {
        this.second = second;
    }
}
