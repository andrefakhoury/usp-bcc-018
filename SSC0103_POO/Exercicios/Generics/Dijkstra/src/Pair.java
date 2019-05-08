/**
 * Classe que representa um par de elementos
 * @param <T> tipo do primeiro elemento
 * @param <S> tipo do segundo elemento
 */
public class Pair<T, S> {
    private T first;
    private S second;

    /**
     * Controi um par vazio
     */
    @SuppressWarnings("unchecked")
    public Pair() {
        first = (T) new Object();
        second = (S) new Object();
    }

    /**
     * Constroi um par definido
     * @param first primeiro elemento
     * @param second segundo elemento
     */
    public Pair(T first, S second) {
        this.first = first;
        this.second = second;
    }

    /**
     * Retorna o primeiro elemento
     * @return o primeiro elemento do pair
     */
    public T getFirst() {
        return first;
    }

    /**
     * Altera o primeiro elemento do pair
     * @param first novo elemento
     */
    public void setFirst(T first) {
        this.first = first;
    }

    /**
     * Retorna o segundo elemento
     * @return o segundo elemento do pair
     */
    public S getSecond() {
        return second;
    }

    /**
     * Altera o segundo elemento do pair
     * @param second novo elemento
     */
    public void setSecond(S second) {
        this.second = second;
    }
}