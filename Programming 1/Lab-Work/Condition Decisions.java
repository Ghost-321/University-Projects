import java.util.Scanner;

public class Letter {
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		sc.useDelimiter(""); //Side question for the advanced - what's this doing?
		char c = sc.next().charAt(0);


		//Add your conditional statement here
		if (c == 'a' || c == 'e' || c== 'i' ||c== 'o' ||c== 'u'){
		System.out.println("Vowel");
		}
		else{
		System.out.println("Consonant");
		}
	}
}
