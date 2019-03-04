public class Ex02 {
    public static void main(String args[]) throws Exception {
        System.out.printf("Digite o valor de n: ");
        int n = 0;

        try {
            n = EntradaTeclado.leInt();
        } catch (Exception ex) {
            System.out.println("Valor de n invalido.");
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n-i; j++) {
                System.out.printf("*"); //imprime as primeiras n-i estrelas
            }
            System.out.printf("\n"); //acabou a linha atual, pula para a proxima
        }
    }
}
