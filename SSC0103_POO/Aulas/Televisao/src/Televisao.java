public class Televisao {
    private int canalAtual, volumeAtual;
    private int minCanal, maxCanal, minVolume, maxVolume;

    /**
     * Cria uma televisao com os intervalos de canal e volume mandados por parametro.
     * @param minCanal canal minimo permitido
     * @param maxCanal canal maximo permitido
     * @param minVolume volume minimo permitido
     * @param maxVolume volume maximo permitido
     */
    public Televisao(int minCanal, int maxCanal, int minVolume, int maxVolume) {
        this.minCanal = minCanal;
        this.maxCanal = maxCanal;
        this.minVolume = minVolume;
        this.maxVolume = maxVolume;
    }

    /**
     * @return o canal atual
     */
    public int getCanalAtual() {
        return this.canalAtual;
    }

    /**
     * @return volume atual
     */
    public int getVolumeAtual() {
        return this.volumeAtual;
    }

    /**
     * Muda o canal atual, se possivel
     * @param canal novo canal
     * @return booleano se foi possivel alterar o canal
     */
    public boolean setCanalAtual(int canal) {
        if (canal >= minCanal && canal <= maxCanal) {
            this.canalAtual = canal;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Muda o volume atual, se possivel
     * @param volume novo volume
     * @return booleano se foi possivel alterar o volume
     */
    public boolean setVolumeAtual(int volume) {
        if (volume >= minVolume && volume <= maxVolume) {
            this.volumeAtual = volume;
            return true;
        } else {
            return false;
        }
    }
}
