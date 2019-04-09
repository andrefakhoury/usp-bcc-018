/**
 * Classe de um assistente - funcionario que possui salario especifico.
 */
public class Assistente extends Funcionario {
    /**
     * Construtor do Assistente, apenas chama o construtor do Funcionario.
     * @param nome nome do assistente
     * @param CPF CPF do assistente
     * @param salarioBase salario base do assistente
     */
    public Assistente(String nome, String CPF, double salarioBase) {
        super(nome, CPF, salarioBase);
    }

    /**
     * Calcula o salario do assistente: 1 * salarioBase.
     * @return salario do assistente
     */
    @Override
    public double calculaSalario() {
        return getSalarioBase();
    }

    /**
     * Imprime as informacoes do assistente, e seu salario especifico.
     * @return String com informacoes
     */
    @Override
    public String toString() {
        return super.toString() + ". Assistente. Salario: " + calculaSalario();
    }
}
