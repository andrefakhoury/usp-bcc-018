import java.io.IOException;
import java.util.*;

public class Conta {
    public static void main(String[] args) throws IOException {
        LinkedList<ContaBancaria> lc = new LinkedList<>();

        while (true) {
            System.out.println("Digite a conta q quer criar: 1especial 2poupanca");
            int op = EntradaTeclado.leInt();

            if (op == 1) {
                lc.add(new ContaEspecial());
            } else {
                lc.add(new ContaPoupanca());
            }

            System.out.println("Aaa manda dinheiro: ");
            double d = EntradaTeclado.leDouble();

            lc.getLast().deposita(d);

            if (lc.getLast() instanceof ContaEspecial) {
                ((ContaEspecial) lc.getLast()).setLimite(-100);
            }

            System.out.println("AAAAAA tira dinheiros agora: ");
            d = EntradaTeclado.leDouble();
            lc.getLast().sacar(d);

            System.out.println("voce tem " + lc.getLast().getSaldo());
        }
    }
}
