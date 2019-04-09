public class PoupancaOuro extends ContaPoupanca {

    public PoupancaOuro(String n, int dia) {
        super(n, dia);
    }

    public void atualiza(double taxa) {
        double s = getSaldo();
        setSaldo(s * (1.5 + taxa));
    }
}
