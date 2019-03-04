public class Ex03 {
    public static void main(String args[]) throws Exception {
        System.out.printf("Digite o valor de n: ");
        int n = 0; //valor de n

        try {
            n = EntradaTeclado.leInt();
        } catch (Exception ex) {
            System.out.println("Valor lido invalido.");
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++)
                System.out.printf(" "); //imprime os i-espacos

            for (int j = 0; j < n-i; j++)
                System.out.printf("*"); //imprime as linhas que faltam com estrelas

            System.out.printf("\n");
        }
    }
}
