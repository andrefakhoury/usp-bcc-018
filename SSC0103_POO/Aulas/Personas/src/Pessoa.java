public class Pessoa {
    private String nome;
    int idade;
    double altura;

    /**
     * Constroi uma nova pessoa com os parametros indicados.
     * @param nome nome da pessoa
     * @param idade idade da pessoa
     * @param altura altura da pessoa
     */
    public Pessoa(String nome, int idade, double altura) {
        this.nome = nome;
        this.idade = idade;
        this.altura = altura;
    }

    /**
     * Muda o nome da pessoa
     * @param nome
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Muda a idade da pessoa
     * @param idade
     */
    public void setIdade(int idade) {
        this.idade = idade;
    }

    /**
     * Muda a altura da pessoa
     * @param altura
     */
    public void setAltura(double altura) {
        this.altura = altura;
    }

    /**
     * @return o nome da pessoa
     */
    public String getNome() {
        return this.nome;
    }

    /**
     * @return a idade da pessoa
     */
    public int getIdade() {
        return this.idade;
    }

    /**
     * @return a altura da pessoa
     */
    public double getAltura() {
        return this.altura;
    }

    /**
     * @return string com os dados da pessoa: nome, idade, altura.
     */
    public String toString() {
        return this.nome + ", " + this.idade + " anos, " + this.altura;
    }

    /**
     * Imprime na tela os dados da pessoa.
     */
    public void printPessoa() {
        System.out.println("Pessoa: " + this.toString());
    }
}
