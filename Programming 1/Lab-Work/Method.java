import java.util.Scanner;

public class Divider {
	
	//Write your method here.
	//Remember that it has to have the
	//right name and right parameter list.
	public static int divide(int t, int g) {
		return t/g;
	}
	
	
	//You don't need to change anything below here.
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter first number: ");
		int a = sc.nextInt();
		
		System.out.print("Enter second number: ");
		int b = sc.nextInt();
		
		System.out.println("The result is " + divide(a, b));
		
	}
	
}
