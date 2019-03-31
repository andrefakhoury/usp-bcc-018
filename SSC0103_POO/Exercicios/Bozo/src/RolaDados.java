import java.util.Calendar;

public class RolaDados {

    private Dado[] dados;

    /**
     * Construtor, cria n dados
     * @param n quantidade de dados
     */
    public RolaDados(int n) {
        dados = new Dado[n];
        for (int i = 0; i < n; i++) {
            dados[i] = new Dado();
        }
    }

    /**
     * Rola todos os dados e retorna os seus valores
     * @return
     */
    public int[] rolar() {
        int[] res = new int[dados.length];
        for (int i = 0; i < dados.length; i++) {
            res[i] = dados[i].rolar();
        }
        return res;
    }

    /**
     * Rola os dados de acordo com um vetor de booleano
     * @param quais vetor de booleanos informando quais dados rolar
     * @return
     */
    public int[] rolar(boolean[] quais) {
        int[] res = new int[dados.length];
        for (int i = 0; i < dados.length; i++) {
            if (quais[i]) {
                res[i] = dados[i].rolar();
            } else {
                res[i] = dados[i].getLado();
            }
        }
        return res;
    }

    /**
     * Rola os dados de acordo com uma string, separando os dados por espacos.
     * @param s posicoes dos dados a serem rolados
     * @return
     * @throws RuntimeException
     */
    public int[] rolar(String s) throws RuntimeException {
        String[] quais = s.split(" ");
        int[] res = new int[dados.length];

        for (int i = 0; i < dados.length; i++)
            res[i] = dados[i].getLado();

        try {
            for (int i = 0; i < quais.length; i++) {
                int d = Integer.parseInt (quais[i]) - 1;
                res[d] = dados[d].rolar();
            }
        } catch (Exception ex) {
            throw new RuntimeException("Numero do dado invalido.");
        }

        return res;
    }

    /**
     * Retorna uma string com os dados
     * @return a string com os valores dos dados
     */
    public String toString() {
        String ret = "";

        for (int i = 0; i < dados.length; i++)
            ret += (i+1) + "          ";
        ret += "\n";

        for (int l = 0; l <= 4; l++) {
            for (int i = 0; i < dados.length; i++) {
                ret += dados[i].toString(l);
            }
            ret += "\n";
        }

        return ret;
    }
}
