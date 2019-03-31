/**
 * Classe que armazena informacoes basicas de uma pessoa.
 */
public class Pessoa {
    private String nome, endereco, email;

    /**
     * Constroi uma pessoa a partir de informacoes basicas
     * @param nome Nome da pessoa
     * @param endereco Endereco da pessoa
     * @param email Email da pessoa
     */
    public Pessoa(String nome, String endereco, String email) {
        this.nome = nome;
        this.endereco = endereco;
        this.email = email;
    }

    /**
     * Constroi uma pessoa com informacoes vazias
     */
    public Pessoa() {
        nome = "";
        endereco = "";
        email = "";
    }

    /**
     * Retorna o nome da pessoa armazenado
     * @return Nome da pessoa
     */
    public String getNome() {
        return nome;
    }

    /**
     * Altera o nome da pessoa
     * @param nome Novo nome da pessoa
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Retorna o endereco da pessoa armazenado
     * @return Endereco da pessoa
     */
    public String getEndereco() {
        return endereco;
    }


    /**
     * Altera o endereco da pessoa
     * @param endereco Novo endereco da pessoa
     */
    public void setEndereco(String endereco) {
        this.endereco = endereco;
    }

    /**
     * Retorna o email da pessoa armazenado
     * @return Email da pessoa
     */
    public String getEmail() {
        return email;
    }

    /**
     * Altera o email da pessoa
     * @param email Novo email da pessoa
     */
    public void setEmail(String email) {
        this.email = email;
    }

    /**
     * Retorna string com informacoes basicas da pessoa.
     * @return String com o nome, email e endereco da pessoa
     */
    @Override
    public String toString() {
        String ret = nome + " " + email + " " + endereco;
        return ret;
    }
}
