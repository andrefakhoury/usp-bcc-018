public class Assistente extends Funcionario {
    public Assistente(String nome, String CPF, double salarioBase) {
        super(nome, CPF, salarioBase);
    }

    @Override
    public double calculaSalario() {
        return getSalarioBase();
    }
}
