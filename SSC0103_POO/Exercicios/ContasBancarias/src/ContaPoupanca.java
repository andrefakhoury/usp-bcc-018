
public abstract class ContaPoupanca extends ContaBancaria {
    private int vencimento;

    public ContaPoupanca(String n, int dia) {
        super(n);
        vencimento = dia;
    }

    public int getVencimento() {
        return vencimento;
    }

    public void setVencimento(int vencimento) {
        this.vencimento = vencimento;
    }

    @Override
    public int compareTo(ContaBancaria cb) {
        if (cb instanceof ContaEspecial)
            return 1;

        return super.compareTo(cb);
    }

}