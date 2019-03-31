/**
 * Classe de uma Pessoa Fisica, com os atributos da Pessoa e mais atributos de CPF, data de Nascimento e Estado Civil.
 */
public class PessoaFisica extends Pessoa {
    private String CPF, dataNasc, estadoCivil;

    /**
     * Constroi a PessoaFisica a partir de suas informacoes
     * @param nome Nome da pessoa
     * @param endereco Endereco da pessoa
     * @param email Email da pessoa
     * @param CPF CPF da pessoa
     * @param dataNasc Data de nascimento da pessoa
     * @param estadoCivil Estado Civil da pessoa
     */
    public PessoaFisica(String nome, String endereco, String email, String CPF, String dataNasc, String estadoCivil) {
        super(nome, endereco, email);
        this.CPF = CPF;
        this.dataNasc = dataNasc;
        this.estadoCivil = estadoCivil;
    }

    /**
     * Retorna o CPF da pessoa
     * @return CPF armazenado
     */
    public String getCPF() {
        return CPF;
    }

    /**
     * Altera o CPF da pessoa
     * @param CPF Novo CPF apos a alteracao
     */
    public void setCPF(String CPF) {
        this.CPF = CPF;
    }

    /**
     * Retorna a data de nasicmento da pessoa
     * @return Data de nascimento armazenado
     */
    public String getDataNasc() {
        return dataNasc;
    }

    /**
     * Altera a data de nascimento da pessoa
     * @param dataNasc Nova data de nascimento apos a alteracao
     */
    public void setDataNasc(String dataNasc) {
        this.dataNasc = dataNasc;
    }

    /**
     * Retorna o Estado Civil da pessoa
     * @return Estado civil armazenado
     */
    public String getEstadoCivil() {
        return estadoCivil;
    }

    /**
     * Altera o Estado Civil da pessoa
     * @param estadoCivil Novo estado civil apos a alteracao
     */
    public void setEstadoCivil(String estadoCivil) {
        this.estadoCivil = estadoCivil;
    }

    /**
     * Retorna uma string com as informacoes basicas da Pessoa
     * @return String com os dados da pessoa concatenados
     */
    @Override
    public String toString() {
        String ret = super.toString();
        ret += " " + CPF + " " + dataNasc + " " + estadoCivil;
        return ret;
    }
}
