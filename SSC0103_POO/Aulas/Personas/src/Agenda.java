public class Agenda {
    private Pessoa[] pessoas;
    private int qtd;

    public Agenda() {
        this.pessoas = new Pessoa[10];
        this.qtd = 0;
    }

    public void armazenaPessoa(String nome, int idade, double altura) {
        if (qtd >= 10) return;

        pessoas[qtd] = new Pessoa(nome, idade, altura);
        qtd++;
    }

    public void removePessoa(String nome) {
        int i = 0;
        while (i < qtd && !pessoas[i].getNome().equals(nome)) i++;
        if (i == qtd) return;
        for (int j = i+1; j <= qtd; j++)
            pessoas[j-1] = pessoas[j];
        this.qtd--;
    }

    public int buscaPessoa(String nome) {
        int i = 0;
        while (i < qtd && !pessoas[i].getNome().equals(nome)) i++;
        if (i == qtd) return -1;
        return i;
    }

    public void imprimeAgenda() {
        for (int i = 0; i < qtd; i++) {
            System.out.println(pessoas[i].toString());
        }
    }

    public void imprimePessoa(int i) {
        System.out.println(pessoas[i].toString());
    }

}
