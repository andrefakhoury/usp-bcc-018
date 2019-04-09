public class Vendedor extends Funcionario {
    private double comissao;

    public Vendedor(String nome, String CPF, double salarioBase, double comissao) {
        super(nome, CPF, salarioBase);
        this.comissao = comissao;
    }

    @Override
    public double calculaSalario() {
        return getSalarioBase() + comissao;
    }
}
