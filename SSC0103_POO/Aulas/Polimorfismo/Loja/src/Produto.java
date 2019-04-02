/**
 * Classe que representa um produto, exclusivo por seu Codigo de Barras.
 */
public class Produto {
    private String codBar;
    private double preco;

    /**
     * Construtor de um produto a partir do codigo de barras.
     * @param codBar Codigo de Barras do produto
     * @param preco Preco do produto
     */
    public Produto(String codBar, double preco) {
        this.codBar = codBar;
        this.preco = preco;
    }

    /**
     * Retorna o codigo de barras do produto
     * @return Codigo de Barras
     */
    public String getCodBar() {
        return codBar;
    }

    /**
     * Altera o codigo de barras do produto
     * @param codBar Codigo de barras a ser editado
     */
    public void setCodBar(String codBar) {
        this.codBar = codBar;
    }

    /**
     * Retorna o preco do produto
     * @return Preco do produto
     */
    public double getPreco() {
        return preco;
    }

    @Override
    public String toString() {
        return codBar + " - R$" + String.format("%.2f", preco) + " ";
    }
}
