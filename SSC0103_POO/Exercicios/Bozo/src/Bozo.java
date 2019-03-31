public class Bozo {

    /**
     * Retorna um array com o valor dos dados, atualizados apos o usuario escolher os dados que quer rolar.
     * @param rolaDados objeto do tipo RolaDados
     * @return array com os dados atualizados
     * @throws java.io.IOException
     */
    public static int[] digitaDados(RolaDados rolaDados) throws java.io.IOException {
        System.out.println("Digite os dados a serem rolados:");
        String escolha = EntradaTeclado.leString();

        try {
            int[] dados = rolaDados.rolar(escolha);
            return dados;
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            return digitaDados(rolaDados);
        }
    }

    /**
     * Estrutura do jogo Bozo
     * @param args
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws java.io.IOException {
        RolaDados rolaDados = new RolaDados(5);
        Placar placar = new Placar();
        int[] dados;

        for (int rodada = 1; rodada <= 10; rodada++) {
            System.out.println("Digite alguma string para iniciar a rodada"); //espera o usuario interagir para comecar o jogo
            EntradaTeclado.leString();
            rolaDados.rolar();
            System.out.println(rolaDados);

            dados = digitaDados(rolaDados);
            System.out.println(rolaDados);

            dados = digitaDados(rolaDados);
            System.out.println(rolaDados);

            boolean flag = true;
            while (flag) { // continua perguntando caso o usuario digite lugares invalidos
                System.out.println(placar);
                System.out.println("Digite o lugar que deseja alterar:");
                try {
                    int posicao = EntradaTeclado.leInt();
                    placar.add(posicao, dados);
                    flag = false;
                } catch (Exception ex) {
                    System.out.println(ex.getMessage());
                }
            }

            System.out.println(placar);
        }

        System.out.println("Placar final: " + placar.getScore());
    }

}

