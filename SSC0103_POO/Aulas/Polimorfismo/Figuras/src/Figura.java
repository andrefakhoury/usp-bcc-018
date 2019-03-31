/**
 * Classe que representa uma figura geometrica.
 * Funciona como se fosse uma classe abstrata.
 */
public class Figura {
    private String cor;
    private boolean filled;

    /**
     * Constroi uma figura sem preenchimento
     */
    public Figura() {
        cor = "";
        filled = false;
    }

    /**
     * Adiciona uma cor a figura, e a marca como preenchida.
     * @param cor Nova cor da figura
     */
    public void addCor(String cor) {
        this.cor = cor;
        this.filled = true;
    }

    /**
     * Retorna a cor atual da String (se houver).
     * @return Cor da string
     */
    public String getCor() {
        return this.cor;
    }

    /**
     * Retorna 0
     * @return 0 (metodo sera sobrescrito pelas funcoes filhas)
     */
    public double getArea() {
        return 0;
    }

    /**
     * Retorna 0
     * @return 0 (metodo sera sobrescrito pelas funcoes filhas)
     */
    public double getPerimetro() {
        return 0;
    }

}
