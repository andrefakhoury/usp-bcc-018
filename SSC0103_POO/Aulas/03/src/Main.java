import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException  {
        String str1 = EntradaTeclado.leString();

        String s = str1.toUpperCase();

        int qtt[] = new int[5];
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt((i)) == 'A') qtt[0]++;
            if (s.charAt((i)) == 'E') qtt[1]++;
            if (s.charAt((i)) == 'I') qtt[2]++;
            if (s.charAt((i)) == 'O') qtt[3]++;
            if (s.charAt((i)) == 'U') qtt[4]++;
        }

        System.out.println("A: " + qtt[0]);
        System.out.println("E: " + qtt[1]);
        System.out.println("I: " + qtt[2]);
        System.out.println("O: " + qtt[3]);
        System.out.println("U: " + qtt[4]);

        System.out.println("\nUpper: " + s);

        String str2 = EntradaTeclado.leString();

        if (str1.startsWith(str2)) System.out.println("Aparece no comeco.\n");
        if (str1.endsWith(str2)) System.out.println("Aparece no final.\n");
    }
}
