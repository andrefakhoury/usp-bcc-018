public class Elevador {
    private int andarAtual, totalAndares, capElevador, qtdPessoas;

    /**
     * Construtor do elevador, pode ser alterada a capacidade e o total de andares.
     * O andar atual e qtd de pessoas comeca com 0.
     * @param capElevador capacidade do elevador
     * @param totalAndares total de andares do predio
     */
    public Elevador(int capElevador, int totalAndares) {
        this.andarAtual = 0;
        this.totalAndares = totalAndares;
        this.capElevador = capElevador;
        this.qtdPessoas = 0;
    }

    /**
     * @return andar atual do elevador
     */
    public int getAndarAtual() {
        return this.andarAtual;
    }

    /**
     * @return total de andares do predio
     */
    public int getTotalAndares() {
        return this.totalAndares;
    }

    /**
     * @return capacidade do elevador
     */
    public int getCapElevador() {
        return this.capElevador;
    }

    /**
     * @return quantidade de pessoas atualmente no elevador
     */
    public int getQtdPessoas() {
        return this.qtdPessoas;
    }

    /**
     * Muda o total de andares do elevador.
     * @return booleano indicando se a operacao foi bem sucedida
     */
    public boolean setTotalAndares(int totalAndares) {
        if (totalAndares >= 0) {
            this.totalAndares = totalAndares;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Muda o andar atual do elevador
     * @return booleano indicando se a operacao foi bem sucedida
     */
    public boolean setAndarAtual(int andarAtual) {
        if (andarAtual <= totalAndares && andarAtual >= 0) {
            this.andarAtual = andarAtual;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Muda a capacidade do elevador
     * @return booleano indicando se a operacao foi bem sucedida
     */
    public boolean setCapElevador(int capElevador) {
        if (capElevador >= 0) {
            this.capElevador = capElevador;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Muda a quantidade de pessoas atuais.
     * @return booleano indicando se a operacao foi bem sucedida
     */
    public boolean setQtdPessoas(int qtdPessoas) {
        if (qtdPessoas <= capElevador && qtdPessoas >= 0) {
            this.qtdPessoas = qtdPessoas;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Aumenta em 1 a quantidade de pessoas do elevador.
     * @return boolean indicando se a pessoa conseguiu entrar.
     */
    public boolean entraPessoa() {
        if (qtdPessoas < capElevador) {
            qtdPessoas++;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Diminui em 1 a quantidade de pessoas do elevador.
     * @return boolean indicando se a pessoa conseguiu sair.
     */
    public boolean saiPessoa() {
        if (this.qtdPessoas > 0) {
            qtdPessoas--;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Aumenta em 1 a o andar atual do elevador.
     * @return boolean indicando se o elevador nao ultrapassou o limite de andares.
     */
    public boolean sobeAndar() {
        if (this.andarAtual < this.totalAndares) {
            andarAtual++;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Diminui em 1 a o andar atual do elevador.
     * @return boolean indicando se o elevador nao ultrapassou o limite de andares.
     */
    public boolean desceAndar() {
        if (this.andarAtual > 0) {
            this.andarAtual--;
            return true;
        } else {
            return false;
        }
    }

}
