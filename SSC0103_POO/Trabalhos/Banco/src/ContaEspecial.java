public class ContaEspecial extends ContaBancaria {
    private double limite;

    public void sacar(double x) {
        if (this.saldo - x >= limite) {
            this.saldo -= x;
        }
    }

    public double getLimite() {
        return limite;
    }

    public void setLimite(double limite) {
        this.limite = limite;
    }
}
