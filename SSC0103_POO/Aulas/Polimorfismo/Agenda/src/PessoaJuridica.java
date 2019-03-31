/**
 * Classe de pessoa juridica, armazenando elementos de uma pessoa mais os atributos de CNPJ, IE e Razao Social.
 */
public class PessoaJuridica extends Pessoa {
    String CNPJ, inscricaoEstadual, razaoSocial;

    /**
     * Construtor de uma PessoaJuridica a partir de informacoes mandadas por parametro
     * @param nome Nome da Pessoa Juridica
     * @param endereco Endereco da Pessoa Juridica
     * @param email Email da Pessoa Juridica
     * @param CNPJ CNPJ da Pessoa Juridica
     * @param inscricaoEstadual Inscricao Estadual da Pessoa Juridica
     * @param razaoSocial Razao Social da Pessoa Juridica
     */
    public PessoaJuridica(String nome, String endereco, String email, String CNPJ, String inscricaoEstadual, String razaoSocial) {
        super(nome, endereco, email);
        this.CNPJ = CNPJ;
        this.inscricaoEstadual = inscricaoEstadual;
        this.razaoSocial = razaoSocial;
    }

    /**
     * Retorna o CNPJ da pessoa
     * @return CNPJ armazenado
     */
    public String getCNPJ() {
        return CNPJ;
    }

    /**
     * Altera o CNPJ atual da pessoa.
     * @param CNPJ Novo CNPJ para a alteracao.
     */
    public void setCNPJ(String CNPJ) {
        this.CNPJ = CNPJ;
    }

    /**
     * Retorna a Inscricao Estadual da pessoa
     * @return Inscricao Estadual armazenada
     */
    public String getInscricaoEstadual() {
        return inscricaoEstadual;
    }

    /**
     * Altera a inscricao estadual atual da pessoa.
     * @param inscricaoEstadual Nova inscricao estadual para a alteracao.
     */
    public void setInscricaoEstadual(String inscricaoEstadual) {
        this.inscricaoEstadual = inscricaoEstadual;
    }

    /**
     * Retorna a razao social da pessoa
     * @return Razao Social armazenada
     */
    public String getRazaoSocial() {
        return razaoSocial;
    }

    /**
     * Altera a Razao Social atual da pessoa juridica.
     * @param razaoSocial nova Razao Social para a alteracao.
     */
    public void setRazaoSocial(String razaoSocial) {
        this.razaoSocial = razaoSocial;
    }

    /**
     * Retorna uma string com as informacoes basicas da PessoaJuridica
     * @return String com os dados da pessoa concatenados
     */
    @Override
    public String toString() {
        String ret = super.toString();
        ret += " " + CNPJ + " " + inscricaoEstadual + " " + razaoSocial;
        return ret;
    }
}
