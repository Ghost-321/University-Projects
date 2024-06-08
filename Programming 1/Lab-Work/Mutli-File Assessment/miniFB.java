import java.io.*;
import java.util.*;

public class MiniFB {

    public static List<Person> readInData(String filename) {
        List <Person> people = new ArrayList<Person>();
        int type;
        try {
            Scanner filesc = new Scanner(new File(filename));
            while (filesc.hasNextLine()) {
                switch (filesc.nextLine()) {
                case "Student":
                type = 1;
                break;
                case "Academic":
                type = 2;
                break;
                case "Programmer":
                type = 3;
                break;
                default:
                type = 0;
                break;

            }
            String name = filesc.nextLine();
            switch (type) {
                case 0:
                break;
                case 1:
                String degree = filesc.nextLine();
                int year = filesc.nextInt();
                String debug = filesc.nextLine();
                Student man = new Student(name, degree, year);
                people.add(man);
                break;
                case 2:
                String subject = filesc.nextLine();
                Academic man2 = new Academic(name, subject);
                people.add(man2);
                break;
                case 3:
                String language = filesc.nextLine();
                Programmer man3 = new Programmer (name, language);
                people.add(man3);
                break;
            }
        }
    }   
    catch (FileNotFoundException e) {
        System.out.println("File not found.");
    }
    return people;
    }
    public static void main(String[] args) {
        List<Person> people = readInData("testFile.txt");

        System.out.println(people);
    }

}
