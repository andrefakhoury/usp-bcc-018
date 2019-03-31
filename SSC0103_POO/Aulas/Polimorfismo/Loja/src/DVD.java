/**
 * Classe de um DVD, que e um tipo de Produto
 */

public class DVD extends Produto {
    private String nome, artista;

    /**
     * Construtor do DVD, a partir de informacoes basicas
     * @param codBar Codigo de barras do DVD
     * @param nome Nome do DVD
     * @param artista Artista do DVD
     */
    public DVD(String codBar, String nome, String artista) {
        super(codBar);
        this.nome = nome;
        this.artista = artista;
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
     * Retorna o nome do Artista do DVD
     * @return nome do artista armazenado
     */
    public String getArtista() {
        return artista;
    }

    /**
     * Altera o artista armazenado
     * @param artista Novo artista a ser armazenado
     */
    public void setArtista(String artista) {
        this.artista = artista;
    }

    /**
     * Retorna uma string com as informacoes basicas do DVD
     * @return String com o nome e artista do DVD
     */
    @Override
    public String toString() {
        return nome + " - " + artista;
    }
}
