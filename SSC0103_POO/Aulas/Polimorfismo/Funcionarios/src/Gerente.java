/**
 * Classe de um gerente - funcionario que possui salario especifico.
 */
public class Gerente extends Funcionario {
    /**
     * Construtor do gerente, apenas chama o construtor do Funcionario.
     * @param nome nome do gerente
     * @param CPF CPF do gerente
     * @param salarioBase salario base do gerente
     */
    public Gerente(String nome, String CPF, double salarioBase) {
        super(nome, CPF, salarioBase);
    }

    /**
     * Calcula o salario do gerente: 2 * salarioBase.
     * @return salario do gerente
     */
    @Override
    public double calculaSalario() {
        return 2 * getSalarioBase();
    }

    /**
     * Imprime as informacoes do gerente, e seu salario especifico.
     * @return String com informacoes
     */
    @Override
    public String toString() {
        return super.toString() + ". Gerente. Salario: " + calculaSalario();
    }
}
