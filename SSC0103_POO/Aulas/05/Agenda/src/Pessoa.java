/**
 * Crie uma agenda de contatos. Nessa agenda, contatos podem ser adicionados, removidos, ou
 * pesquisados por nome ou por CPF/CNPJ. Deve ser possível, também, visualizar todos os contatos
 * da agenda.
 * Dois tipos de contatos podem fazer parte da agenda: pessoa física e pessoa jurídica. A pessao física
 * tem os seguintes atributos: CPF, data de nascimento, estado civil.
 * A pessoa jurídica possui: CNPJ, inscrição estadual, razão social.
 */

public class Pessoa {
    private String nome, endereco, email;

    public Pessoa(String nome, String endereco, String email) {
        this.nome = nome;
        this.endereco = endereco;
        this.email = email;
    }

    public Pessoa() {
        nome = "";
        endereco = "";
        email = "";
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEndereco() {
        return endereco;
    }

    public void setEndereco(String endereco) {
        this.endereco = endereco;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Override
    public String toString() {
        String ret = nome + " " + email + " " + endereco;
        return ret;
    }
}
