public class Agenda {
    private Pessoa[] pessoas; //array de pessoas
    private int qtd;           //quantidade de pessoas atualmente na lista

    public Agenda() {
        this.pessoas = new Pessoa[10]; //cria um array de 10 elementos para armazenar pessoas
        this.qtd = 0; //o array inicialmente esta vazio.
    }

    /**
     * Armazena uma nova pessoa na agenda, se possivel.
     * @param nome nome a ser inserido
     * @param idade idade a ser inserida
     * @param altura altura a ser inserida
     * @return booleano indicando se a operacao foi bem sucedida.
     */
    public boolean armazenaPessoa(String nome, int idade, double altura) {
        if (qtd >= 10)
            return false;

        pessoas[qtd] = new Pessoa(nome, idade, altura);
        qtd++;
        return true;
    }

    /**
     * Retorna o indice da pessoa na agenda (0-based).
     * @param nome nome a ser procurado na agenda
     * @return indice da pessoa na agenda
     */
    public int buscaPessoa(String nome) {
        int i = 0;
        while (i < qtd && !pessoas[i].getNome().equals(nome))
            i++;
        if (i == qtd)
            return -1;
        return i;
    }

    /**
     * Remove uma pessoa da agenda.
     * @param nome nome da pessoa a ser removida
     * @return booleano se a operacao for bem sucedida.
     */
    public boolean removePessoa(String nome) {
        int i = buscaPessoa(nome);
        if (i == -1) //pessoa nao esta na agenda
            return false;

        for (int j = i+1; j <= qtd; j++) //sobescreve os dados da pessoa
            pessoas[j-1] = pessoas[j];

        this.qtd--;
        return true;
    }

    /**
     * Imprime a agenda
     */
    public void imprimeAgenda() {
        for (int i = 0; i < qtd; i++) {
            System.out.println(pessoas[i].toString());
        }

        if (qtd == 0)
            System.out.println("Agenda vazia.");
    }

    /**
     * Imprime a pessoa de indice i da agenda
     * @param i indice da pessoa para ser impressa.
     */
    public void imprimePessoa(int i) {
        if (i < 0 || i >= qtd)
            System.out.println("Pessoa fora do intervalo da agenda.\n");
        else {
            System.out.println(pessoas[i].toString());
        }
    }

}
