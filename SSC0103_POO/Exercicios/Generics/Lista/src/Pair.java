import java.util.Objects;

/**
 * Classe que representa um par
 * @param <T> tipo do primeiro elemento
 * @param <S> tipo do segundo elemento
 */
public class Pair<T, S> {
    private T first;
    private S second;

    /**
     * Gerador do pair, recebendo nenhum parametro
     */
    @SuppressWarnings("unchecked")
    public Pair() {
        first = (T) new Object();
        second = (S) new Object();
    }

    /**
     * Constroi um pair a partir dos parametros enviados
     * @param first primeiro elemento
     * @param second segundo elemento
     */
    public Pair(T first, S second) {
        this.first = first;
        this.second = second;
    }

    /**
     * Retorna o primeiro elemento do pair
     * @return primeiro elemento do pair
     */
    public T getFirst() {
        return first;
    }

    /**
     * Altera o primeiro elemento do pair
     * @param first elemento a ser alterado
     */
    public void setFirst(T first) {
        this.first = first;
    }

    /**
     * Retorna o segundo elemento do pair
     * @return segundo elemento do pair
     */
    public S getSecond() {
        return second;
    }

    /**
     * Altera o segundo elemento do pair
     * @param second elemento a ser alterado
     */
    public void setSecond(S second) {
        this.second = second;
    }

    /**
     * Retorna uma string com o primeiro e ultimo elemento do pair
     * @return string com first + second
     */
    @Override
    public String toString() {
        return this.first + " " + this.second;
    }

    /**
     * Comparador para o pair
     * @param o objeto a ser comparado
     * @return booleano se os elementos sao iguais
     */
    @Override
    public boolean equals(Object o) {
        if (o instanceof Pair) {
            return Objects.equals(((Pair) o).first, this.first) &&
                    Objects.equals(((Pair) o).second, this.second);
        }
        return false;
    }
}
