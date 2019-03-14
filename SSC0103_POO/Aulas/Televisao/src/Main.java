public class Main {

    public static void main(String[] args) {
        Televisao televisao = new Televisao(0, 10, 0, 10);
        Controle controle = new Controle(televisao);

        System.out.println("Volume atual: " + televisao.getVolumeAtual());
        controle.aumentaVolume();
        System.out.println("Volume atual: " + televisao.getVolumeAtual());
        controle.aumentaCanal();
        System.out.println("Canal atual: " + televisao.getCanalAtual());
        controle.mudaCanal(7);
        System.out.println("Canal atual: " + televisao.getCanalAtual());
    }
}
