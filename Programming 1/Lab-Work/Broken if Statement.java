import java.util.Scanner;

public class BrokenIf {
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		
		if (n % 3 == 1 ||n % 3 == 2){
			System.out.println("Adding 1 to n.");
			n++;
		}
		if (n % 3 == 2) {
			System.out.println("Adding another 1 to n.");
			n++;
		}
		
		if (n == 6)
			System.out.println("n is 6.");
		else
			System.out.println("n is multiple of 3, but not 6.");		
	}
}
