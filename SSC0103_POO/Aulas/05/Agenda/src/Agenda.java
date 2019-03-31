import java.util.ArrayList;
import java.util.List;

public class Agenda {
    private List<Pessoa> list;

    public Agenda() {
        list = new ArrayList<>();
    }

    public List<Pessoa> getList() {
        return this.list;
    }

    @Override
    public String toString() {
        String ret = "";
        for (int i = 0; i < list.size(); i++) {
            ret += list.get(i) + "\n";
        }
        return ret;
    }

    public void add(Pessoa p) {
        list.add(p);
    }

    public void remove(String id) {
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i) instanceof PessoaFisica && ((PessoaFisica)list.get(i)).getCPF() == id)
                list.remove(i);
            if (list.get(i) instanceof PessoaJuridica && ((PessoaJuridica)list.get(i)).getCNPJ() == id)
                list.remove(i);
        }
    }

    public Pessoa getPessoa(String id) {
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i) instanceof PessoaFisica && ((PessoaFisica)list.get(i)).getCPF() == id)
                return list.get(i);
            if (list.get(i) instanceof PessoaJuridica && ((PessoaJuridica)list.get(i)).getCNPJ() == id)
                return list.get(i);
        }

        return new Pessoa();
    }

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
