/**
 * Classe que representa um Livro, que e um tipo de produto.
 */

public class Livro extends Produto {
    private String nome, autor;
    private int numPaginas;

    /**
     * Construtor do livro a partir de parametros basicos
     * @param codBar Codigo de Barras do livro
     * @param nome Nome do livro
     * @param autor Autor do Livro
     * @param numPaginas Numero de paginas do livro
     */
    public Livro(String codBar, String nome, String autor, int numPaginas) {
        super(codBar);
        this.nome = nome;
        this.autor = autor;
        this.numPaginas = numPaginas;
    }

    /**
     * Retorna o nome do livro atual
     * @return nome do livro
     */
    public String getNome() {
        return nome;
    }

    /**
     * Altera o nome do livro
     * @param nome Nome do livro a ser alterado
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Retorna o autor do livro
     * @return autor do livro
     */
    public String getAutor() {
        return autor;
    }

    /**
     * Altera o autor do livro
     * @param autor Autor do livro a ser alterado
     */
    public void setAutor(String autor) {
        this.autor = autor;
    }

    /**
     * Retorna o numero de paginas do livro
     * @return Numero de paginas do livro
     */
    public int getNumPaginas() {
        return numPaginas;
    }

    /**
     * Altera o numero de paginas do livro
     * @param numPaginas Novo numero de paginas
     */
    public void setNumPaginas(int numPaginas) {
        this.numPaginas = numPaginas;
    }

    /**
     * Retorna uma string com as informacoes do livro
     * @return Nome, autor e numero de paginas do livro em uma string
     */
    @Override
    public String toString() {
        return nome + " - " + autor + " (" + numPaginas + ")";
    }
}
