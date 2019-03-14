public class Main {

    public static void main(String[] args) {
        Elevador elevador = new Elevador(10, 10);
        elevador.desceAndar();
        elevador.entraPessoa();
        elevador.desceAndar();
        elevador.saiPessoa();
        System.out.println("" + elevador.saiPessoa()); // falso, nao foi possivel sair uma pessoa do elevador
    }
}
