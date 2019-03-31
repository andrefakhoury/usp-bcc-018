/**
 * Classe que representa um quadrado, armazenando o seu lado.
 */
public class Quadrado extends Figura {
    private double lado;

    /**
     * Constroi um quadrado a partir de seu lado
     * @param lado Lado do quadrado
     */
    public Quadrado(double lado) {
        this.lado = lado;
    }

    /**
     * Retorna o lado do quadrado
     * @return Lado armazenado do quadrado
     */
    public double getLado() {
        return lado;
    }

    /**
     * Altera o lado do quadrado
     * @param lado Novo lado do quadrado
     */
    public void setLado(double lado) {
        this.lado = lado;
    }

    /**
     * Calcula e retorna a area do Quadrado
     * @return Area do quadrado
     */
    @Override
    public double getArea() {
        return lado * lado;
    }

    /**
     * Calcula e retorna o perimetro do Quadrado
     * @return Perimetro do quadrado
     */
    @Override
    public double getPerimetro() {
        return 4 * lado;
    }
}
