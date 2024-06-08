import java.util.function.Function;
import java.util.function.IntUnaryOperator;
import java.util.*;
import java.io.*;

public class Processor {

    public static <O> void mapData(String inputFilename, String outputFilename, Function<Integer, O> map) {
       try {
           BufferedReader br = new BufferedReader(new FileReader(inputFilename));
           try (PrintWriter pw= new PrintWriter (new File(outputFilename))) {
               while (br.ready()) {
                   String strline = br.readLine();
                   try {
                       int line = Integer.parseInt(strline);
                       pw.println(map.apply(line));
                   }
                   catch (NumberFormatException e) {
                       System.out.println("That's not an not an integer. Apprantely it doesn't matter.");
                   }
               }
           }
           catch (FileNotFoundException e) {
               System.out.print("File not found.");
           }
       } 
       catch (IOException e) {
           System.out.println("Error.");
       }
       // Stuff goes here
    }

    public static void main(String[] args) {
         mapData("inputTest.txt", "outputTest.txt", Function.<Integer>identity());
    }
}
