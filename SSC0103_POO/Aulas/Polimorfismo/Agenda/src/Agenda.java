import java.util.ArrayList;
import java.util.List;

/**
 * Classe Agenda, armazena lista de pessoas e permite operacoes sobre ela.
 */
public class Agenda {
    private List<Pessoa> list;

    /**
     * Constroi uma nova Agenda
     */
    public Agenda() {
        list = new ArrayList<>();
    }

    /**
     * Retorna a lista de pessoas na Agenda.
     * @return
     */
    public List<Pessoa> getList() {
        return this.list;
    }

    /**
     * Retorna string com informacoes de todas as pessoas na agenda.
     * @return
     */
    @Override
    public String toString() {
        String ret = "";
        for (int i = 0; i < list.size(); i++) {
            ret += list.get(i) + "\n";
        }
        return ret;
    }

    /**
     * Adiciona uma pessoa na Agenda
     * @param p
     */
    public void add(Pessoa p) {
        list.add(p);
    }

    /**
     * Remove uma pessoa da Agenda, a partir do CPF ou CNPJ
     * @param id CPJ/CNPJ da pessoa a ser removida
     */
    public void remove(String id) {
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i) instanceof PessoaFisica && ((PessoaFisica)list.get(i)).getCPF() == id)
                list.remove(i);
            if (list.get(i) instanceof PessoaJuridica && ((PessoaJuridica)list.get(i)).getCNPJ() == id)
                list.remove(i);
        }
    }

    /**
     * Retorna uma pessoa da Agenda a partir de CPF/CNPJ, ou uma nova pessoa se nao existir.
     * @param id CPF/CPNJ da pessoa
     * @return
     */
    public Pessoa getPessoa(String id) {
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i) instanceof PessoaFisica && ((PessoaFisica)list.get(i)).getCPF() == id)
                return list.get(i);
            if (list.get(i) instanceof PessoaJuridica && ((PessoaJuridica)list.get(i)).getCNPJ() == id)
                return list.get(i);
        }

        return new Pessoa();
    }

    /**
     * Utiliza o metodo BubbleSort para ordenar a lista.
     */
    public void ordenaLista() {
        for (int i = 0; i < list.size(); i++) {
            for (int j = 0; j < i; j++) {
                boolean canSwap = false;

                if (list.get(i) instanceof PessoaFisica && list.get(j) instanceof PessoaFisica)
                    canSwap = ((PessoaFisica)list.get(i)).getCPF().compareTo(((PessoaFisica)list.get(j)).getCPF()) > 0;
                else if (list.get(i) instanceof PessoaFisica && list.get(j) instanceof PessoaJuridica)
                    canSwap = false;
                else if (list.get(i) instanceof PessoaJuridica && list.get(j) instanceof PessoaFisica)
                    canSwap = true;
                else if (list.get(i) instanceof PessoaJuridica && list.get(j) instanceof PessoaJuridica)
                    canSwap = ((PessoaJuridica)list.get(i)).getCNPJ().compareTo(((PessoaJuridica)list.get(j)).getCNPJ()) > 0;

                if (!canSwap) {
                    Pessoa temp = list.get(i);
                    list.set(i, list.get(j));
                    list.set(j, temp);
                }
            }
        }
    }

}
