public abstract class Funcionario {
    private String nome, CPF;
    private double salarioBase;

    public Funcionario(String nome, String CPF, double salarioBase) {
        this.nome = nome;
        this.CPF = CPF;



        this.salarioBase = salarioBase;
    }

    private static boolean verificaCPF(String CPF) {
        CPF = CPF.replace(".", "");
        CPF = CPF.replace("-", "");

        if (CPF.length() != 11) {
            return false;
        }



        return false;
    }

    public abstract double calculaSalario();

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCPF() {
        return CPF;
    }

    public void setCPF(String CPF) {
        this.CPF = CPF;
    }

    public double getSalarioBase() {
        return salarioBase;
    }

    public void setSalarioBase(double salarioBase) {
        this.salarioBase = salarioBase;
    }
}
