import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Classe de uma Loja, que armazena produtos em seu estoque.
 */
public class Loja {
    private List<ProdQtt> estoque;

    /**
     * Construtor da Loja
     */
    public Loja() {
        estoque = new ArrayList<>();
    }

    /**
     * Adiciona um produto em determinada quantidade.
     * @param prod Produto a ser adicionado
     * @param qtt Quantidade do produto
     */
    public void addProduto(Produto prod, int qtt) {
        for (int i = 0; i < estoque.size(); i++) {
            if (estoque.get(i).getProd().equals(prod)) {
                estoque.get(i).increaseQtt(qtt);
                return;
            }
        }

        estoque.add(new ProdQtt(prod, qtt));
    }

    /**
     * Retorna um produto da loja a partir do codigo de barras
     * @param codBar Codigo de barras para fazer a busca
     * @return Produto encontrado, ou nulo caso nao encontre nada.
     */
    public Produto getProdutoByCodBar(String codBar) {
        for (int i = 0; i < estoque.size(); i++) {
            if (estoque.get(i).getProd().getCodBar().equals(codBar)) {
                return estoque.get(i).getProd();
            }
        }

        return null;
    }

    /**
     * Retorna um produto da loja a partir do seu nome
     * @param name Nome para fazer a busca
     * @return Produto encontrado, ou nulo caso nao encontre nada.
     */
    public Produto getProdutoByName(String name) {
        for (int i = 0; i < estoque.size(); i++) {

            Produto at = estoque.get(i).getProd();
            String toCompare = "";

            if (at instanceof Livro) {
                toCompare = ((Livro) at).getNome();
            } else if (at instanceof CD) {
                toCompare = ((CD) at).getNome();
            } else if (at instanceof DVD) {
                toCompare = ((DVD) at).getNome();
            }

            if (toCompare.equals(name))
                return at;
        }

        return null;
    }

    /**
     * Vende um produto, ou seja, diminui sua quantidade no estoque por 1.
     * @param codBar Codigo de barras do produto vendido
     */
    public void vendeProduto(String codBar) {
        for (int i = 0; i < estoque.size(); i++) {
            if (estoque.get(i).getProd().getCodBar().equals(codBar)) {
                estoque.get(i).decreaseQtt();
                return;
            }
        }

        // Excecao: produto nao encontrado, venda impossivel.
        throw new IllegalArgumentException("Produto nao encontrado");
    }

    /**
     * Retorna a quantidade de estoque de um produto.
     * @param prod Produto a ser pesquisado
     * @return Quantidade em estoque deste produto
     */
    public int estoqueProduto(Produto prod) {
        for (int i = 0; i < estoque.size(); i++) {
            if (estoque.get(i).getProd().equals(prod))
                return estoque.get(i).getQtt();
        }

        return 0;
    }

    /**
     * Retorna uma string com todos os produtos da loja, e suas quantidades em estoque
     * @return
     */
    @Override
    public String toString() {

        Map<Livro, Integer> livros = new HashMap<>();
        Map<CD, Integer> cds = new HashMap<>();
        Map<DVD, Integer> dvds = new HashMap<>();

        for (int i = 0; i < estoque.size(); i++) {
            Produto at = estoque.get(i).getProd();
            Integer curQtt = estoque.get(i).getQtt();

            if (at instanceof Livro)
                livros.put((Livro)at, curQtt);
            else if (at instanceof CD)
                cds.put((CD)at, curQtt);
            else if (at instanceof DVD)
                dvds.put((DVD)at, curQtt);
        }

        String ret = "Livros:\n";
        for (Livro l : livros.keySet())
            ret += l + " [" + livros.get(l) + "]\n";
        ret += "\nCDS:\n";
        for (CD c : cds.keySet())
            ret += c + " [" + cds.get(c) + "]\n";
        ret += "\nDVDS:\n";
        for (DVD d : dvds.keySet())
            ret += d + " [" + dvds.get(d) + "]\n";

        return ret;
    }

    /**
     * Classe para organizar o estoque de produtos, com o Produto e sua Quantidade.
     */
    private class ProdQtt {
        private Produto prod;
        private int qtt;

        /**
         * Construtor a partir do Produto e quantidade
         * @param prod Produto a ser criado
         * @param qtt Quantidade deste produto
         */
        public ProdQtt(Produto prod, int qtt) {
            this.prod = prod;
            this.qtt = qtt;
        }

        /**
         * Retorna o produto atual
         * @return Produto atual, independentemente de sua quantidade
         */
        public Produto getProd() {
            return prod;
        }

        /**
         * Altera o produto atual
         * @param prod Produto novo a ser incluido
         */
        public void setProd(Produto prod) {
            this.prod = prod;
        }

        /**
         * Retorna a quantidade em estoque do produto
         * @return Quantidade do produto
         */
        public int getQtt() {
            return qtt;
        }

        /**
         * Altera a quantidade disponivel do produto
         * @param qtt Nova quantidade a ser alterada
         */
        public void setQtt(int qtt) {
            this.qtt = qtt;
        }

        /**
         * Aumenta a quantidade do produto em "qtt" unidades.
         * @param qtt Quantidade a ser adicionada ao produto.
         */
        public void increaseQtt(int qtt) {
            this.qtt += qtt;
        }

        /**
         * Aumenta a quantidade do produto em 1 unidade
         */
        public void increaseQtt() {
            this.qtt++;
        }

        /**
         * Diminui a quantidade do produto atual em 1 unidade.
         * Se isso resultar em um numero negativo, uma excecao eh criada.
         */
        public void decreaseQtt() {
            if (this.qtt > 0)
                this.qtt--;
            else {
                this.qtt = 0;
                throw new IllegalArgumentException("Produto sem estoque.");
            }
        }

        /**
         * Diminui a quantidade do produto atual em "qtt" unidade.
         * Se isso resultar em um numero negativo, uma excecao eh criada.
         * @param qtt Quantidade a decrescer.
         */
        public void decreaseQtt(int qtt) {
            if (this.qtt >= qtt)
                this.qtt -= qtt;
            else
                throw new IllegalArgumentException("Produto sem estoque.");
        }
    }
}
