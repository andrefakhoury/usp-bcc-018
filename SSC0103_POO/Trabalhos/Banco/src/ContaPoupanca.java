public class ContaPoupanca extends ContaBancaria {
    private int diaRendimento;

    void atualiza(double taxa) {
        this.saldo *= 1.0 + taxa;
    }

    public int getDiaRendimento() {
        return diaRendimento;
    }

    public void setDiaRendimento(int diaRendimento) {
        this.diaRendimento = diaRendimento;
    }
}