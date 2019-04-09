public class Gerente extends Funcionario {
    public Gerente(String nome, String CPF, double salarioBase) {
        super(nome, CPF, salarioBase);
    }

    @Override
    public double calculaSalario() {
        return 2 * getSalarioBase();
    }
}
