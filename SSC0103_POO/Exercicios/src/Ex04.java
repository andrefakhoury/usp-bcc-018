public class Ex04 {
    public static void main(String args[]) throws Exception {
        System.out.printf("Digite o valor de n: ");
        int n = 0; //valor para conferir se eh primo ou composto

        try {
            n = EntradaTeclado.leInt();
        } catch (Exception ex) {
            System.out.println("Valor lido invalido.");
        }

        boolean isPrime = true;
        int menorDivisor = 0;

        // confere se é primo, e caso não seja, armazena o menor divisor.
        for (int i = 2; i < n; i++) {
            if (n%i == 0) {
                isPrime = false;
                menorDivisor = i;
                break;
            }
        }

        if (isPrime) {
            System.out.println(n + " é primo.");
        } else {
            System.out.println(n + " é composto. Menor divisor: " + menorDivisor);
        }

    }
}
