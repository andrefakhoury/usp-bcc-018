import java.io.*;

public class Main {

    private static void writeUsingOutputStream(String data, String fileName) {
        OutputStream os = null;

        try {
            os = new FileOutputStream(new File(fileName));
            os.write(data.getBytes(), 0, data.length());
        } catch (IOException e) {
            e.printStackTrace();
        }finally{
            try {
                os.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        String fileName = "teste.txt";
        String data = "abc abc def aaa aaa abc";
        writeUsingOutputStream(data, fileName);

        ContaPalavra contaPalavra = new ContaPalavra(fileName);
        contaPalavra.criaMapa();
        contaPalavra.mostraMapa();
    }
}
