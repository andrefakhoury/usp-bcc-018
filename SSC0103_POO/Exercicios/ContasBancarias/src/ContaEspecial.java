
public class ContaEspecial extends ContaBancaria {
    private double limite;

    public ContaEspecial(String n, double l) {
        super(n);
        limite = l;
    }

    @Override
    public void saca(double qto) {
        double s = getSaldo();
        if ( qto > s + limite )
            throw new IllegalArgumentException("Limite excedido para esse saque");
        setSaldo( s - qto );
    }

    public void atualiza(double taxa) {

    }

    @Override
    public int compareTo(ContaBancaria cb) {
        if (cb instanceof ContaEspecial)
            return super.compareTo(cb);

        return -1;
    }

}