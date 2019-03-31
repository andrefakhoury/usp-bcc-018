public class Figura {
    private String cor;
    private boolean filled;

    public Figura() {
        cor = "";
        filled = false;
    }

    public void addCor(String cor) {
        this.cor = cor;
        this.filled = true;
    }

    public double getArea() {
        return 0;
    }

    public double getPerimetro() {
        return 0;
    }

}
