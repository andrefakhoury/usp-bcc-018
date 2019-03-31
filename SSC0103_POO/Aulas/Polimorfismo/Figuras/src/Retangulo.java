/**
 * Classe que representa um retangulo, armazenando a sua base e altura.
 */
public class Retangulo extends Figura {
    private double base, altura;

    /**
     * Constroi um retangulo a partir da base a altura
     * @param base Base do retangulo
     * @param altura Altura do retangulo
     */
    public Retangulo(double base, double altura) {
        this.base = base;
        this.altura = altura;
    }

    /**
     * Retorna a base do retangulo
     * @return Base do retangulo
     */
    public double getBase() {
        return base;
    }

    /**
     * Altera a base do retangulo
     * @param base Nova base para alterar
     */
    public void setBase(double base) {
        this.base = base;
    }

    /**
     * Retorna a altura do retangulo
     * @return Altura armazenada do retangulo
     */
    public double getAltura() {
        return altura;
    }

    /**
     * Altera a altura do retangulo
     * @param altura Nova altura do retangulo
     */
    public void setAltura(double altura) {
        this.altura = altura;
    }

    /**
     * Retorna a area do retangulo
     * @return Area do retangulo (base * altura
     */
    @Override
    public double getArea() {
        return base * altura;
    }

    /**
     * Calcula e retorna o perimetro do retangulo
     * @return Perimetro do retangulo
     */
    @Override
    public double getPerimetro() {
        return 2 * base + 2 * altura;
    }
}
