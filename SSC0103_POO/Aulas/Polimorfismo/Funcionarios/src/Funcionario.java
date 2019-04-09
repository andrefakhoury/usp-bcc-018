/**
 * Classe abstrata de um funcionario. Armazena o nome, cpf e salario base do funcionario.
 * Tambem possui um metodo estatico validador de CPF.
 */

public abstract class Funcionario {
    private String nome, CPF;
    private double salarioBase;

    /**
     * Construtor de um funcionario
     * @param nome Nome do funcionario
     * @param CPF CPF do funcionario
     * @param salarioBase Salario base para o calculo do salario
     */
    public Funcionario(String nome, String CPF, double salarioBase) {
        this.nome = nome;
        setCPF(CPF);
        this.salarioBase = salarioBase;
    }

    /**
     * Verifica se um CPF e valido ou nao.
     * @param CPF CPF a ser verificado
     * @return
     */
    public static boolean verificaCPF(String CPF) {
        CPF = CPF.replace(".", "");
        CPF = CPF.replace("-", "");

        if (CPF.length() != 11) {
            return false;
        }

        if (CPF.equals("11111111111") || CPF.equals("22222222222") || CPF.equals("33333333333") || CPF.equals("44444444444") || CPF.equals("55555555555") ||
            CPF.equals("66666666666") || CPF.equals("77777777777") || CPF.equals("88888888888") || CPF.equals("99999999999"))
            return false;

        int primeiroResultado = 0;
        for (int i = 0, peso = 10; i < 9; i++, peso--) {
            primeiroResultado += (int)(CPF.charAt(i) - '0') * peso;
        }

        int segundoResultado = 0;
        for (int i = 0, peso = 11; i < 10; i++, peso--) {
            segundoResultado += (int)(CPF.charAt(i) - '0') * peso;
        }

        int primeiroResto = ((primeiroResultado * 10) % 11)%10;
        int segundoResto = ((segundoResultado * 10) % 11)%10;

        boolean primeiraValidacao = primeiroResto == (int)(CPF.charAt(9)) - '0';
        boolean segundaValidacao = segundoResto == (int)(CPF.charAt(10)) - '0';

        return primeiraValidacao && segundaValidacao;
    }

    /**
     * Funcao para calcular o salario, de acordo com o tipo de cada funcionario
     * @return salario calculado do funcionario
     */
    public abstract double calculaSalario();

    /**
     * Getter do nome do funcionario
     * @return nome
     */
    public String getNome() {
        return nome;
    }

    /**
     * Setter do nome do funcionario
     * @param nome nome a ser alterado
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Getter do CPF do funcionario
     * @return CPF
     */
    public String getCPF() {
        return CPF;
    }

    /**
     * Setter do CPF do funcionario. Verifica se eh valido, se nao for, uma excecao eh criada.
     * @param CPF CPF a ser alterado
     */
    public void setCPF(String CPF) {
        if (!verificaCPF(CPF))
            throw new RuntimeException("CPF invalido.");
        this.CPF = CPF;
    }

    /**
     * Getter do salario base do funcionario
     * @return salario base
     */
    public double getSalarioBase() {
        return salarioBase;
    }

    /**
     * Setter do salario base do funcionario
     * @param salarioBase base do salario a ser alterada
     */
    public void setSalarioBase(double salarioBase) {
        this.salarioBase = salarioBase;
    }

    /**
     * Imprime as informacoes de um funcionario
     * @return String com informacoes
     */
    @Override
    public String toString() {
        return "Funcionario " + nome + ", " + CPF;
    }
}
