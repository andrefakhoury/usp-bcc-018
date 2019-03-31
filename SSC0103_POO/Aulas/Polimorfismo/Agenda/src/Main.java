public class Main {

    /**
     * Testador da agenda e pessoas
     * @param args
     */
    public static void main(String[] args) {
        Agenda ag = new Agenda();
        ag.add(new PessoaFisica("Jorge", "rua", "aa", "001", "12/12/1222", "solteiro"));
        ag.add(new PessoaJuridica("Juri", "rua", "aa", "321", "23234", "abc"));
        ag.add(new PessoaFisica("Maria", "rua", "aa", "122", "12/12/1222", "solteiro"));

        System.out.println(ag);
        ag.ordenaLista();
        System.out.println(ag);
    }
}
