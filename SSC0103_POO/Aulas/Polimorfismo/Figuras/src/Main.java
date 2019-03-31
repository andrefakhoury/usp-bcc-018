public class Main {

    public static void main(String[] args) {
        Figura fig1 = new Retangulo(10, 5);
        Figura fig2 = new Quadrado(7);
        Figura fig3 = new Circulo(3);

        System.out.println(fig1.getArea() + " - " + fig1.getPerimetro());
        System.out.println(fig2.getArea() + " - " + fig2.getPerimetro());
        System.out.println(fig3.getArea() + " - " + fig3.getPerimetro());
    }
}
