public class Dado {
    private int numLados, lado;

    /**
     * Cria um dado com um numero especifico de lados
     * @param n
     */
    public Dado(int n) {
        this.numLados = n;
        rolar();
    }

    /**
     * Cria um dado com 6 lados
     */
    public Dado() {
        this(6);
    }

    /**
     * Retorna o lado atual
     * @return o lado atual do dado
     */
    public int getLado() {
        return this.lado;
    }

    /**
     * Rola o dado, atribuindo um valor aleatorio a ele.
     * @return
     */
    public int rolar() {
        this.lado = new Random().getIntRand(numLados) + 1;
        return this.lado;
    }

    /**
     * Retorna uma string de acordo com a linha especificada por parametro e o lado atual do dado.
     * @param linha linha a ser impressa
     * @return string da linha em questao
     */
    public String toString(int linha) {
        if (numLados > 6)
            return Integer.toString(lado);

        String s000 = "|     |    ";
        String s100 = "|*    |    ";
        String s010 = "|  *  |    ";
        String s001 = "|    *|    ";
        String s101 = "|*   *|    ";
        String sDIV = "+-----+    ";

        switch (linha) {
            case 0:
                return sDIV;
            case 1:
                if (this.lado == 1)
                    return s000;
                else if (this.lado == 2 || this.lado == 3)
                    return s100;
                else
                    return s101;
            case 2:
                if (this.lado == 1 || this.lado == 3 || this.lado == 5)
                    return s010;
                else if (this.lado == 2 || this.lado == 4)
                    return s000;
                else
                    return s101;
            case 3:
                if (this.lado == 1)
                    return s000;
                else if (this.lado == 2 || this.lado == 3)
                    return s001;
                else
                    return s101;
            case 4:
                return sDIV;
            default:
                return "";
        }
    }

    /**
     * Retorna uma string com o valor atual do dado.
     * @return
     */
    public String toString() {
        String ret = "";
        for (int i = 0; i <= 4; i++)
            ret += this.toString(i) + "\n";
        return ret;
    }
}
