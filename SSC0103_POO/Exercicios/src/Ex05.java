public class Ex05 {

    /**
     * Confere se o número N é primo ou não
     * @param n: número a ser checado
     * @return boolean de ser ou não primo
     */
    static boolean isPrime(int n) {
        for (int i = 2; i < n; i++)
            if (n%i == 0)
                return false;

        return true;
    }

    public static void main(String args[]) throws Exception {
        System.out.printf("Digite o valor de n: ");
        int n = 0; //valor limite para calcular os primos

        try {
            n = EntradaTeclado.leInt();
        } catch (Exception ex) {
            System.out.println("Valor lido invalido.");
        }

        //confere todos os números de N-1 até 2, checando a primalidade de cada um
        for (int i = n-1; i > 1; i--) {
            if (isPrime(i)) {
                System.out.println("O menor primo até " + n + " é " + i);
                return;
            }
        }

        // o número inserido foi 2
        System.out.println("Nao existe primo até " + n);
    }
}
