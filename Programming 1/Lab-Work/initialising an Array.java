import java.util.Scanner;

public class BasicArray {
	public static void main(String[] args) {
		
		//Your code goes here
		int[] a = new int[3];
		
		//Don't change anything below here.
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the first number: ");
		a[0] = sc.nextInt();
		System.out.print("Enter the second number: ");
		a[1] = sc.nextInt();
		System.out.print("Enter the third number: ");
		a[2] = sc.nextInt();
		
		System.out.println("The sum of the numbers is " + (a[0] + a[1] + a[2]));
		System.out.println("The average of the numbers is " + (float)(a[0] + a[1] + a[2])/a.length);
		
	}
}
