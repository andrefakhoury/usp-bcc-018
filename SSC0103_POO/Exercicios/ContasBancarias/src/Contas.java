import java.util.HashMap;
import java.util.Vector;

public class Contas {

//    private Vector<ContaBancaria> contas = new Vector<ContaBancaria>();
    private HashMap<Integer, ContaBancaria> contas = new HashMap<Integer, ContaBancaria>();

    public static void main(String[] args) throws Exception {
        int op = 0;
        Contas ct = new Contas();

        while (op != 7) {
            op = ct.leOpcao();
            switch (op) {
                case 1:
                    System.out.println("Tipo de poupanca: 1-Simples, 2-Ouro: ");
                    int tipo = EntradaTeclado.leInt();

                    if (tipo < 1 || tipo > 2) {
                        System.out.println("************ Opcao invalida.**************");
                        break;
                    }

                    System.out.println("Nome do correntista: ");
                    String s = EntradaTeclado.leString();
                    System.out.println("Dia de vencimento: ");
                    int dia = EntradaTeclado.leInt();
                    ContaPoupanca cp;
                    if (tipo == 1) {
                        cp = new PoupancaSimples(s, dia);
                    } else {
                        cp = new PoupancaOuro(s, dia);
                    }
                    ct.add(cp);
                    System.out.println("************ Conta criada.**************");
                    break;

                case 2:
                    System.out.println("Nome do correntista: ");
                    s = EntradaTeclado.leString();
                    System.out.println("Limite de saque: ");
                    double limite = EntradaTeclado.leDouble();
                    ContaEspecial ce = new ContaEspecial(s, limite);
                    ct.add(ce);
                    System.out.println("************ Conta criada.**************");
                    break;
                case 3:
                    System.out.println("Numero da conta: ");
                    int conta = EntradaTeclado.leInt();
                    System.out.println("Valor a sacar: ");
                    double valor = EntradaTeclado.leDouble();
                    ContaBancaria cb = ct.procura(conta);
                    if ( cb == null )
                    {
                        System.out.println("************* Conta não existe **************");
                        break;
                    }
                    try {
                        cb.saca(valor);
                        System.out.println("****************** Saque realizado ***********");
                    }
                    catch (Exception e)
                    {
                        System.out.println("****************** Saque não realizado ***********");
                        System.out.println(e.getMessage());
                    }
                    break;
                case 4:
                    System.out.println("Numero da conta: ");
                    conta = EntradaTeclado.leInt();
                    System.out.println("Valor a depositar: ");
                    valor = EntradaTeclado.leDouble();
                    cb = ct.procura(conta);
                    if ( cb == null )
                    {
                        System.out.println("************* Conta não existe **************");
                        break;
                    }
                    cb.deposita(valor);
                    System.out.println("****************** Depósito realizado ***********");
                    break;
                case 6:
                    ct.printSaldos();
                    break;
                case 5:
                    System.out.println("Qual o valor da taxa? ");
                    double tx = EntradaTeclado.leDouble();
                    ct.atualizaPoupanca(tx);
                    System.out.println("Saldos atualizados");
                    break;
            }
            System.out.println("Digite ENTER para continuar");
            EntradaTeclado.leString();
            System.out.println("\n\n");
        }

    }

    private int leOpcao() {
        System.out.println("1) Criar poupança\n2) Criar conta especial\n3) Realizar saque\n4) Realizar deposito\n"
                + "5) Atualizar poupanças\n6) Mostrar saldos\n7) Sair");
        int k = -1;
        while (true)
        {
            System.out.println("Digite a opção desejada ===> ");
            try {
                k = EntradaTeclado.leInt();
                if ( k > 0 && k < 8 )
                    return k;
            }
            catch (Exception e) { }
        }
    }

    private void add(ContaBancaria cb) {
//        contas.add(cb);
        contas.put(cb.getNumConta(), cb);
    }

    private void printSaldos() {
        for (ContaBancaria ctb : contas.values()) {
            System.out.println("Numero da conta:" + ctb.getNumConta());
            System.out.println("Titular: " + ctb.getNomeCliente());
            System.out.println("Saldo: " + ctb.getSaldo());
            System.out.println();
        }
    }

    private void atualizaPoupanca(double tx) {
        for (ContaBancaria ctb : contas.values()) {
            ctb.atualiza(tx);
        }
    }

    private ContaBancaria procura(int conta) {
        return contas.get(conta);

        // com Vector:
//        for (ContaBancaria ctb : contas) {
//            if (conta == ctb.getNumConta())
//                return ctb;
//        }
//        return null;
    }
}