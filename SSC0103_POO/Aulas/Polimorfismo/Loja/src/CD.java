/**
 * Classe para representar CD, que e um tipo de produto
 */

public class CD extends Produto {
    private String nome, artista;

    /**
     * Construtor do CD a partir de informacoes basicas
     * @param codBar Codigo de barras do CD
     * @param nome Nome do CD
     * @param artista Artista do CD
     */
    public CD(String codBar, String nome, String artista) {
        super(codBar);
        this.nome = nome;
        this.artista = artista;
    }

    /**
     * Retorna o nome desse CD
     * @return nome do CD
     */
    public String getNome() {
        return nome;
    }

    /**
     * Altera o nome do CD
     * @param nome Novo nome
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Retorna o artista do CD
     * @return Artista deste CD
     */
    public String getArtista() {
        return artista;
    }

    /**
     * Altera o artista deste CD
     * @param artista nome do novo artista
     */
    public void setArtista(String artista) {
        this.artista = artista;
    }

    /**
     * Retorna uma string com as informacoes basicas do CD
     * @return String com nome e artista do CD
     */
    @Override
    public String toString() {
        return nome + " - " + artista;
    }
}
