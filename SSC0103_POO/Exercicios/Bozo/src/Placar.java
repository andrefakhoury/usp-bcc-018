import javax.management.RuntimeErrorException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;

public class Placar {
    private int[] pontos;

    public Placar() {
        pontos = new int[10];
        for (int i = 0; i < pontos.length; i++)
            pontos[i] = -1;
    }

    /**
     * Adiciona uma sequencia de dados em uma determinada posição do placar.
     * @param posicao
     * @param dados
     */
    public void add(int posicao, int[] dados) throws Exception {
        if (this.pontos[posicao-1] != -1) {
            throw new Exception("Posicao invalida\n");
        }

        if (posicao < 7) { // quantidade * posicao
            int count = 0;
            for (int i = 0; i < dados.length; i++)
                count += (dados[i] == posicao ? 1 : 0);
            this.pontos[posicao-1] = count * posicao;
        } else if (posicao == 7) { // trio e par
            int cnt[] = new int[6];
            for (int i = 0; i < dados.length; i++)
                cnt[dados[i] - 1]++;

            boolean tem3 = false, tem2 = false;
            for (int i = 0; i < cnt.length; i++) {
                if (cnt[i] == 3) tem3 = true;
                else if (cnt[i] == 2) tem2 = true;
            }

            if (tem3 && tem2)
                this.pontos[6] = 15;
            else
                this.pontos[6] = 0;
        } else if (posicao == 8) { // sequencia
            Arrays.sort(dados);
            boolean notSequence = false;
            for (int i = 1; i < dados.length; i++)
                if (dados[i] != dados[i-1]) {
                    notSequence = true;
                    break;
                }
            this.pontos[7] = notSequence ? 0 : 20;
        } else { // quadra ou quina
            int cnt[] = new int[6];
            for (int i = 0; i < dados.length; i++)
                cnt[dados[i] - 1]++;

            if (posicao == 9) {
                boolean tem4 = false;
                for (int i = 0; i < cnt.length; i++) {
                    if (cnt[i] == 4) tem4 = true;
                }

                this.pontos[8] = tem4 ? 30 : 0;
            } else if (posicao == 10) {
                boolean tem5 = false;
                for (int i = 0; i < cnt.length; i++) {
                    if (cnt[i] == 5) tem5 = true;
                }

                this.pontos[9] = tem5 ? 40 : 0;
            }
        }
    }

    /**
     * Computa a soma dos valores obtidos, considerando apenas as posições que já estão ocupadas.
     * @return
     */
    public int getScore() {
        int ret = 0;
        for (int i = 0; i < pontos.length; i++) { //apenas soma todos os valores validos
            if (pontos[i] != -1)
                ret += pontos[i];
        }
        return ret;
    }

    /**
     * A representação na forma de string, mostra o placar completo, indicando quais são as posições livres (com seus respectivos números) e o valor obtido nas posições já ocupadas.
     */
    public String toString() {
        String ret = "";

        int[] posicao = {0, 6, 3, 1, 7, 4, 2, 8, 5, 9}; // posicao dos placares

        for (int i = 0; i < pontos.length; i++) {
            int num = posicao[i];
            int val = pontos[num];

            if (i == 9)
                ret += "           ";

            if (i%3 == 1 || i == 9)
                ret += "|";

            if (val == -1)
                ret += "    (" + (num+1) + ")   ";
            else
                ret += "     " + val + "    ";

            if (i != 9 && val < 10)
                ret += " ";


            if (i%3 == 1 || i == 9)
                ret += "|";
            if (i%3 == 2)
                ret += "\n-----------------------------------\n";
            if (i == 9)
                ret += "\n           +-----------+";
        }

        return ret + "\n";
    }
}
