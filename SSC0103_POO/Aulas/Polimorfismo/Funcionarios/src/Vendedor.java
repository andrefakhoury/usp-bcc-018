/**
 * Classe de um vendedor - funcionario que possui comissao e salario especificos.
 */
public class Vendedor extends Funcionario {
    private double comissao;

    /**
     * Construtor do Vendedor, chama o construtor da superclasse, e possui o atributo especifico comissao
     * @param nome nome do vendedor
     * @param CPF CPF do vendedor
     * @param salarioBase salario base do vendedor
     * @param comissao Comissao do vendedor
     */
    public Vendedor(String nome, String CPF, double salarioBase, double comissao) {
        super(nome, CPF, salarioBase);
        this.comissao = comissao;
    }

    /**
     * Calcula o salario do vendedor: salarioBase + comissao.
     * @return salario do vendedor
     */
    @Override
    public double calculaSalario() {
        return getSalarioBase() + comissao;
    }

    /**
     * Imprime as informacoes do vendedor, e seu salario especifico.
     * @return String com informacoes
     */
    @Override
    public String toString() {
        return super.toString() + ", " + comissao + "de comissao. Vendedor. Salario: " + calculaSalario();
    }
}
