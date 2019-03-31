/**
 * Crie uma agenda de contatos. Nessa agenda, contatos podem ser adicionados, removidos, ou
 * pesquisados por nome ou por CPF/CNPJ. Deve ser possível, também, visualizar todos os contatos
 * da agenda.
 * Dois tipos de contatos podem fazer parte da agenda: pessoa física e pessoa jurídica. A pessao física
 * tem os seguintes atributos: CPF, data de nascimento, estado civil.
 * A pessoa jurídica possui: CNPJ, inscrição estadual, razão social.
 */

public class PessoaJuridica extends Pessoa {
    String CNPJ, inscricaoEstadual, razaoSocial;

    public PessoaJuridica(String nome, String endereco, String email, String CNPJ, String inscricaoEstadual, String razaoSocial) {
        super(nome, endereco, email);
        this.CNPJ = CNPJ;
        this.inscricaoEstadual = inscricaoEstadual;
        this.razaoSocial = razaoSocial;
    }

    public String getCNPJ() {
        return CNPJ;
    }

    public void setCNPJ(String CNPJ) {
        this.CNPJ = CNPJ;
    }

    public String getInscricaoEstadual() {
        return inscricaoEstadual;
    }

    public void setInscricaoEstadual(String inscricaoEstadual) {
        this.inscricaoEstadual = inscricaoEstadual;
    }

    public String getRazaoSocial() {
        return razaoSocial;
    }

    public void setRazaoSocial(String razaoSocial) {
        this.razaoSocial = razaoSocial;
    }

    @Override
    public String toString() {
        String ret = super.toString();
        ret += " " + CNPJ + " " + inscricaoEstadual + " " + razaoSocial;
        return ret;
    }
}
