import java.util.ArrayList;

/**
 * Classe de uma lista circular, representada por uma array
 * @param <T> elemento da lista
 */
public class ListaCircular<T> {
    private T list[];
    private int first, last, size, qtdElem;

    /**
     * Constroi uma lista circular com no maximo maxSize elementos
     * @param maxSize qtd maxima de elementos da lista
     */
    @SuppressWarnings("unchecked")
    public ListaCircular(int maxSize) {
        this.list = (T[]) new Object[maxSize];
        this.first = 0;
        this.last = 0;
        this.size = maxSize;
        this.qtdElem = 0;
    }

    /**
     * Retorna a posicao anterior do ponteiro
     * @param cur posicao atual
     * @return posicao anterior a cur
     */
    private int getPreviousPosition(int cur) {
        return ((cur - 1) + size) % size;
    }

    /**
     * Retorna a proxima posicao do ponteiro
     * @param cur posicao atual
     * @return posicao posterior a cur
     */
    private int getNextPosition(int cur) {
        return (cur + 1) % size;
    }

    /**
     * Insere um elemento no inicio da lista
     * @param elem elemento a ser adicionado
     */
    public void insereInicio(T elem) {
        if (this.qtdElem == this.size)
            throw new ArrayIndexOutOfBoundsException("A lista esta cheia");

        list[first] = elem;
        first = getPreviousPosition(first);
        qtdElem++;
    }

    /**
     * Insere um elemento no final da lista
     * @param elem elemento a ser adicionado
     */
    public void insereFim(T elem) {
        if (this.qtdElem == this.size)
            throw new ArrayIndexOutOfBoundsException("A lista esta cheia");

        last = getNextPosition(last);
        list[last] = elem;
        qtdElem++;
    }

    /**
     * Remove o elemento do inicio da lista
     * @return elemento removido
     */
    public T removeInicio() {
        if (this.qtdElem == 0)
            throw new ArrayIndexOutOfBoundsException("A lista esta vazia");

        T elem = list[getNextPosition(first)];
        first = getNextPosition(first);
        qtdElem--;
        return elem;
    }

    /**
     * Remove o elemento do final da lista
     * @return elemento removido
     */
    public T removeFim() {
        if (this.qtdElem == 0)
            throw new ArrayIndexOutOfBoundsException("A lista esta vazia");

        T elem = list[last];
        last = getPreviousPosition(last);
        qtdElem--;
        return elem;
    }

    /**
     * Retorna um array list correspondente a lista atual
     * @return ArrayList com todos os elementos da lista
     */
    public ArrayList<T> getList() {
        ArrayList<T> newList = new ArrayList<>();
        for (int i = getNextPosition(first); i != getNextPosition(last); i = getNextPosition(i)) {
            newList.add(list[i]);
        }

        return newList;
    }

}
