import java.util.Scanner;

public class UnadvancedDnD {
	public static void main(String[] args) {
	Scanner sc = new Scanner(System.in);
	char action;
	do {
		System.out.print("Please enter an action:");
		action=sc.nextLine().charAt(0);

		switch(action){
			case 'x':
			System.out.println(" Bye!");
			break;
			case 'u':
			System.out.println(" You go one square up.");
			break;
			case 'd':
			System.out.println(" You go one square down.");
			break;
			case 'l':
			System.out.println(" You go one square left.");
			break;
			case 'r':
			System.out.println(" You go one square right.");
			break;
			case 's':
			System.out.println(" You search the square for treasure. You find nothing.");
			break;
			case 'h':
			System.out.println(" You hide, waiting for enemies to come by. It gets boring after about an hour and a half, so you give up.");
			break;
			case 'e':
			System.out.println(" You eat some food. You regain 0 hit points.");
			break;
			default:
			System.out.println(" I don't understand.");
			break;
		}

	}	while (action != 'x');
	
	sc.close();
}
}
