import java.util.Scanner;

public class Marks {
	public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
		// int[] a = new int[10];
		System.out.print("How many students are there? ");
		int a = sc.nextInt();

		String[] names = new String[a];
		int[] marks = new int[a];
		int i = 0;
		int z = 0;
		String x = "";
		sc.nextLine();

		do {
			System.out.print("Enter name of student " + (i + 1) + ": ");
			x = sc.nextLine();
			names[i] = x;
			System.out.print("Enter mark " + (i + 1) + ": ");
			z = sc.nextInt();
			marks[i] = z;
			i++;
			sc.nextLine();



		}
		while (i < a);
		int top = 0;
		int top_id = 0;
		for (i = 0; i < a; i++) {
			if (marks[i] > top){
				top_id = i;
				top = marks[i];
			}
		}
	
		int bottom = top;
		int bottom_id = 0;
		for (i=0; i < a; i++) {
			if (marks[i] < bottom){
				bottom = marks[i];
				bottom_id = i;
			}
		}
		float total = 0;
		for (i = 0; i < a; i++){
			total += marks[i];
		}
		float number = a;
		float average = total/number;
		
		System.out.println("The average mark is: " + average);
		System.out.println("The best student is " + names[top_id]);
		System.out.println("The worst student is " + names[bottom_id]);
	}
}
