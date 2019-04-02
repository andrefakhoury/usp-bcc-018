public class Main {

    /**
     * Main para testar as classes desenvolvidas
     * @param args
     */
    public static void main(String[] args) {
        Livro l = new Livro("1234", 12.50,"Harry Potter", "JKR", 300);
        CD c = new CD("4321", 9.99, "Queen 2", "Queen");
        DVD d = new DVD("21AB", 14.50, "Madagascar 3", "Rei Julian");

        Loja loja = new Loja();
        loja.addProduto(l, 10);
        loja.addProduto(c, 30);
        loja.addProduto(l, 15);
        loja.addProduto(d, 50);

        loja.vendeProduto("1234");

        System.out.println(loja);

        System.out.printf("Estoque de Harry Potter: %d\n", loja.estoqueProduto(l));
    }
}
