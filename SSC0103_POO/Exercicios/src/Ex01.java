public class Ex01 {
    public static void main(String args[]) throws Exception {
        System.out.printf("Digite o valor que quer calcular a Raíz: ");
        double x = 0; // valor inicial de x

        try {
            x = EntradaTeclado.leDouble();
        } catch (Exception ex) {
            System.out.println("Valor da raiz invalido.");
        }

        System.out.printf("Digite o valor inicial do chute: ");
        double last = EntradaTeclado.leDouble(); //valor de x0 (x_i-1)
        double error = 0.00000001, curError;

        do { //calcula a média entre x_i-1 e x/x_i-1, e recalcula o erro
            double actual = (last + (x/last))/2;
            curError = Math.abs(actual-last);
            last = actual;
        } while(curError >= error);

        System.out.println("A raíz de " + x + " vale " + last);
    }
}
