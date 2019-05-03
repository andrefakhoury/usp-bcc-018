import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;
import java.util.TreeMap;

public class ContaPalavra {
    private TreeMap<String, Integer> freq;
    private File file;

    public ContaPalavra(String fileName) {
        file = new File(fileName);
    }

    public void criaMapa() {
        freq = new TreeMap<>();
        Scanner scanner;

        try {
            scanner = new Scanner(file);
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
            return;
        }

        while (scanner.hasNext()) {
            String str = scanner.next().toLowerCase();

            if (freq.containsKey(str)) {
                freq.put(str, freq.get(str) + 1);
            } else {
                freq.put(str, 1);
            }
        }

        scanner.close();
    }

    public void mostraMapa() {
        for (String str : freq.keySet()) {
            System.out.println(str + ": " + freq.get(str));
        }
    }
}
