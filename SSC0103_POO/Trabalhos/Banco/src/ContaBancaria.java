public class ContaBancaria {
    protected String nome;
    protected int numConta;
    protected double saldo;

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getNumConta() {
        return numConta;
    }

    public void setNumConta(int numConta) {
        this.numConta = numConta;
    }

    public double getSaldo() {
        return saldo;
    }

    public void setSaldo(double saldo) {
        this.saldo = saldo;
    }

    public void deposita(double x) {
        this.saldo += x;
    }

    public void sacar(double x) {
        if (this.saldo >= x)
            this.saldo -= x;
    }
}
