import java.util.Objects;

public class Dicionario<K, V> {
    private K[] key;
    private V[] value;
    private int curIndex = 0, maxSize;

    @SuppressWarnings("all")
    public Dicionario(int size) {
        key = (K[]) new Object[size];
        value = (V[]) new Object[size];
        maxSize = size;
    }

    private int indexOfKey(K chave) {
        for (int i = 0; i < curIndex; i++) {
            if (Objects.equals(key[i], chave))
                return i;
        }
        return -1;
    }

    public void add(K chave, V valor) throws ArrayIndexOutOfBoundsException {
        if (curIndex == maxSize)
            throw new ArrayIndexOutOfBoundsException("Tamanho invalido");

        int index = indexOfKey(chave);
        if (index != -1) {
            value[index] = valor;
        } else {
            key[curIndex] = chave;
            value[curIndex] = valor;
            curIndex++;
        }
    }

    public V get(K chave) {
        int index = indexOfKey(chave);
        return index != -1 ? value[index] : null;
    }


    public boolean contains(K chave) {
        return indexOfKey(chave) != -1;
    }

    boolean containsValue(V valor) {
        for (int i = 0; i < curIndex; i++) {
            if (Objects.equals(value[i], valor))
                return true;
        }
        return false;
    }
}
