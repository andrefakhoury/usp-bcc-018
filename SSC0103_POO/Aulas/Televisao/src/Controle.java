public class Controle {
    private Televisao televisao;

    public Controle(Televisao televisao) {
        this.televisao = televisao;
    }

    /**
     * Aumenta em 1 o volume da TV.
     * @return booleano se foi possivel alterar o volume.
     */
    public boolean aumentaVolume() {
        return televisao.setVolumeAtual(televisao.getVolumeAtual() + 1);
    }

    /**
     * Diminui em 1 o volume da TV.
     * @return booleano se foi possivel alterar o volume.
     */
    public boolean abaixaVolume() {
        return televisao.setVolumeAtual(televisao.getVolumeAtual() - 1);
    }

    /**
     * Aumanta em 1 o canal da TV.
     * @return booleano se foi possivel alterar o canal.
     */
    public boolean aumentaCanal() {
        return televisao.setCanalAtual(televisao.getCanalAtual() + 1);
    }

    /**
     * Diminui em 1 o canal da TV.
     * @return booleano se foi possivel alterar o canal.
     */
    public boolean abaixaCanal() {
        return televisao.setCanalAtual(televisao.getCanalAtual() - 1);
    }

    /**
     * Muda o canal para um especifico mandado por parametro
     * @param canal novo canal para assistir
     * @return booleano se foi possivel alterar o canal
     */
    public boolean mudaCanal(int canal) {
        return televisao.setCanalAtual(canal);
    }
}
