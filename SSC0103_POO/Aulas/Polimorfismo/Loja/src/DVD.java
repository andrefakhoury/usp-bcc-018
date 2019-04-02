/**
 * Classe que representa um DVD.
 */

public class DVD extends Produto {
    private String nome, produtora;

    /**
     * Construtor do DVD, a partir de informacoes basicas
     * @param codBar Codigo de barras do DVD
     * @param preco Preco do DVD
     * @param nome Nome do DVD
     * @param produtora Produtora do DVD
     */
    public DVD(String codBar, double preco, String nome, String produtora) {
        super(codBar, preco);
        this.nome = nome;
        this.produtora = produtora;
    }

    /**
     * Retorna o titulo do DVD
     * @return nome/titulo do DVD
     */
    public String getNome() {
        return nome;
    }

    /**
     * Altera o nome do DVD
     * @param nome Novo nome do DVD
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Retorna o nome da produtora do DVD
     * @return nome da produtora armazenado
     */
    public String getProdutora() {
        return produtora;
    }

    /**
     * Altera o produtora armazenado
     * @param produtora Nova produtora a ser armazenado
     */
    public void setProdutora(String produtora) {
        this.produtora = produtora;
    }

    /**
     * Retorna uma string com as informacoes basicas do DVD
     * @return String com o nome e produtora do DVD
     */
    @Override
    public String toString() {
        return super.toString() + nome + " - " + produtora;
    }
}
