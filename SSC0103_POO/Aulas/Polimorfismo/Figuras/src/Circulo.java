/**
 * Classe Circulo, que extende a classe Figura.
 */
public class Circulo extends Figura {
    private double raio;
    private double PI = 3.1415;

    /**
     * Constroi um circulo a partir de um Raio
     * @param raio Raio do novo Circulo
     */
    public Circulo(double raio) {
        this.raio = raio;
    }

    /**
     * Retorna o Raio armazenado
     * @return Raio do circulo
     */
    public double getRaio() {
        return raio;
    }

    /**
     * Altera o raio do circulo
     * @param raio Novo raio
     */
    public void setRaio(double raio) {
        this.raio = raio;
    }

    /**
     * Retorna a area do circulo
     * @return Area do circulo (PI * r * r)
     */
    @Override
    public double getArea() {
        return PI * raio * raio;
    }

    /**
     * Retorna o perimetro (comprimento) do circulo
     * @return Perimetro do circulo
     */
    @Override
    public double getPerimetro() {
        return 2 * PI * raio;
    }
}
