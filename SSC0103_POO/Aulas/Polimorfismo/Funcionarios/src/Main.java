import java.util.ArrayList;

public class Main {

    /**
     * Funcao para testar as classes criadas. Pode-se adicionar funcionarios a uma lista, ou imprimir as informacoes e salario de cada um.
     * @param args
     */
    public static void main(String[] args) {
        int op = readMenuOptions();
        ArrayList<Funcionario> funcionarios = new ArrayList<>();

        while (op != 0) {
            if (op == 1) { // Novo funcionario
                System.out.println("\nNovo funcionario...");

                System.out.println("Digite o nome:");
                String nome;
                try {
                    nome = EntradaTeclado.leString();
                } catch(Exception ex) {
                    nome = "";
                }

                String CPF;
                do {
                    System.out.println("Digite o CPF:");
                    try {
                        CPF = EntradaTeclado.leString();
                    } catch (Exception ex) {
                        CPF = "";
                    }
                } while (!Funcionario.verificaCPF(CPF));

                System.out.println("Digite o salario base:");
                double salarioBase;
                try {
                    salarioBase = EntradaTeclado.leDouble();
                } catch (Exception ex) {
                    salarioBase = 0;
                }

                Funcionario func = null;
                int tipoFuncionario = readTipoFuncionario();

                switch (tipoFuncionario) {
                    case 1:
                        func = new Gerente(nome, CPF, salarioBase);
                        break;
                    case 2:
                        func = new Assistente(nome, CPF, salarioBase);
                        break;
                    case 3:
                        System.out.println("Digite a comissao:");
                        double comissao;
                        try {
                            comissao = EntradaTeclado.leDouble();
                        } catch (Exception ex) {
                            comissao = 0;
                        }
                        func = new Vendedor(nome, CPF, salarioBase, comissao);
                }

                funcionarios.add(func); // adiciona na lista de funcionarios.
                System.out.println("Funcionario adicionado!");
            } else { // Folha salarial
                System.out.println("Impressao da folha salarial...");
                for (Funcionario func : funcionarios) {
                    System.out.println(func);
                }
                System.out.println();
            }

            op = readMenuOptions();
        }

    }

    /**
     * Le e retorna a opcao de menu desejada, prevenindo-se contra possiveis erros de entrada de teclado.
     * @return Opcao desejada (1 - novo funcionario, 2 - folha salarial, 0 - sair do programa).
     */
    private static int readMenuOptions() {
        System.out.println("Digite o que quer fazer:");
        System.out.println("1 - Novo funcionario\n2 - Folha salarial\n0 - Sair");

        int opcao = 0;
        try {
            opcao = EntradaTeclado.leInt();
        } catch (Exception ex) {
            System.out.println("Numero invalido.");
            opcao = readMenuOptions();
        } finally {
            if (opcao < 0 || opcao > 2) {
                System.out.println("Opcao invalida.");
                opcao = readMenuOptions();
            }

            return opcao;
        }
    }

    /**
     * Le e retorna a opcao do tipo de funcionario.
     * @return Tipo do funcionario (1 - gerente, 2 - assistente, 3 - vendedor).
     */
    private static int readTipoFuncionario() {
        System.out.println("Digite o tipo de funcionario\n1 - Gerente\n2 - Assistente\n3 - Vendedor");

        int tipo = 0;
        try {
            tipo = EntradaTeclado.leInt();
        } catch (Exception ex) {
            System.out.println("Numero invalido.");
            tipo = readTipoFuncionario();
        } finally {
            if (tipo < 1 || tipo > 3) {
                System.out.println("Opcao invalida...");
                tipo = readTipoFuncionario();
            }
            return tipo;
        }
    }
}
