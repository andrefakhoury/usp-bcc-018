public class Ex06 {

    public static void main(String args[])  {
        double x = 0, menor, maior;

        System.out.printf("Digite um valor de ponto flutuante: ");



        try {
            x = EntradaTeclado.leDouble();
        } catch (Exception ex) {
            System.out.println("Valor lido invalido.");
        }

        menor = x;
        maior = x;

        while (x != 0) { //o último X inserido vale 0
            menor = Math.min(menor, x); //atualiza o menor valor
            maior = Math.max(maior, x); //atualiza o maior valor

            System.out.printf("Digite um valor de ponto flutuante: ");

            try {
                x = EntradaTeclado.leDouble();
            } catch (Exception ex) {
                System.out.println("Valor lido invalido.");
            }
        }

        //imprime os valores conseguidos
        System.out.println("Menor valor: " + menor + "\nMaior valor: " + maior);

    }
}
