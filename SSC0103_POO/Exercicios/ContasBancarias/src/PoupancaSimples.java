public class PoupancaSimples extends ContaPoupanca {

    public PoupancaSimples(String n, int dia) {
        super(n, dia);
    }

    public void atualiza(double taxa) {
        double s = getSaldo();
        setSaldo(s * (1.0 + taxa));
    }

    @Override
    public int compareTo(ContaBancaria cb) {
        if (cb instanceof PoupancaOuro)
            return 1;

        if (cb instanceof ContaEspecial)
            return 1;

        return super.compareTo(cb);
    }
}
