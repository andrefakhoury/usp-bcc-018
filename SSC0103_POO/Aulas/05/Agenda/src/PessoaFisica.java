/**
 * Crie uma agenda de contatos. Nessa agenda, contatos podem ser adicionados, removidos, ou
 * pesquisados por nome ou por CPF/CNPJ. Deve ser possível, também, visualizar todos os contatos
 * da agenda.
 * Dois tipos de contatos podem fazer parte da agenda: pessoa física e pessoa jurídica. A pessao física
 * tem os seguintes atributos: CPF, data de nascimento, estado civil.
 * A pessoa jurídica possui: CNPJ, inscrição estadual, razão social.
 */

public class PessoaFisica extends Pessoa {
    private String CPF;
    private String dataNasc, estadoCivil;

    public PessoaFisica(String nome, String endereco, String email, String CPF, String dataNasc, String estadoCivil) {
        super(nome, endereco, email);
        this.CPF = CPF;
        this.dataNasc = dataNasc;
        this.estadoCivil = estadoCivil;
    }

    public String getCPF() {
        return CPF;
    }

    public void setCPF(String CPF) {
        this.CPF = CPF;
    }

    public String getDataNasc() {
        return dataNasc;
    }

    public void setDataNasc(String dataNasc) {
        this.dataNasc = dataNasc;
    }

    public String getEstadoCivil() {
        return estadoCivil;
    }

    public void setEstadoCivil(String estadoCivil) {
        this.estadoCivil = estadoCivil;
    }

    @Override
    public String toString() {
        String ret = super.toString();
        ret += " " + CPF + " " + dataNasc + " " + estadoCivil;
        return ret;
    }
}
