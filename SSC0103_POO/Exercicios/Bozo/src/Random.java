import java.util.Calendar;

/**
 * Classe que gera numeros pseudo-aleatorios de acordo com uma semente.
 */
public class Random {
    private long p = 2147483648L;
    private long m = 843314861;
    private long a = 453816693;

    private long x;

    /**
     * Construtor que atribui a semente como o tempo em milisegundos atual.
     */
    public Random() {
        try {
            Thread.sleep(100); //espera um tempo para as seeds serem diferentes
        } catch (Exception ex) {
        } finally {
            this.x = Calendar.getInstance().getTimeInMillis()%p;
        }
    }

    /**
     * Construtor em que se pode mandar a semente desejada
     * @param k semente que sera utilizada
     */
    public Random(int k) {
        this.x = k;
    }

    /**
     * Setter do valor da semente
     * @param semente valor da semente
     */
    public void setSemente(int semente) {
        this.x = semente;
    }

    /**
     * Retorna um valor no intervalo [0, 1)
     * @return o numero gerado
     */
    public double getRand() {
        x = (a + m*x)%p;
        return x/(double)p;
    }

    /**
     * Retorna um valor inteiro no intervalo [0, m)
     * @param m valor maximo desejado
     * @return
     */
    public int getIntRand(int m) {
        return (int)(getRand()*m);
    }

    /**
     * Retorna um valor inteiro no intervalo [min, max)
     * @param min valor minimo desejado
     * @param max valor maximo desejado
     * @return valor gerado
     * @throws IllegalArgumentException
     */
    public int getIntRand(int min, int max) throws IllegalArgumentException {
        if (max <= min) {
            throw new IllegalArgumentException("Parâmetros inválidos");
        }

        return min + getIntRand(max - min);
    }

    /**
     * Retorna um valor inteiro no intervalo [0, Integer.MAX_VALUE), ou seja, qualquer valor inteiro que caiba em um Integer.
     * @return o valor gerado
     */
    public int getIntRand() {
        return getIntRand(Integer.MAX_VALUE);
    }
}