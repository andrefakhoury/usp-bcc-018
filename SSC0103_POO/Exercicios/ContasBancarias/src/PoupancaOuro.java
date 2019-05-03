public class PoupancaOuro extends ContaPoupanca {

    public PoupancaOuro(String n, int dia) {
        super(n, dia);
    }

    public void atualiza(double taxa) {
        double s = getSaldo();
        setSaldo(s * (1.5 + taxa));
    }

    @Override
    public int compareTo(ContaBancaria cb) {
        if (cb instanceof PoupancaSimples)
            return -1;

        if (cb instanceof ContaEspecial)
            return 1;

        return super.compareTo(cb);
    }
}
