public class Main {

    public static void main(String[] args) {
        Agenda ag = new Agenda();

        ag.armazenaPessoa("Jorge", 31, 1.73);
        ag.armazenaPessoa("Moreira", 12, 1.75);
        ag.imprimeAgenda();
        ag.removePessoa("Jorge");
        ag.imprimeAgenda();
        ag.imprimePessoa(ag.buscaPessoa("Moreira"));
    }
}
