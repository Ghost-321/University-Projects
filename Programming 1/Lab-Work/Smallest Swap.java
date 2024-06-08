import java.util.Scanner;

public class SmallestSwap {
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		
		int[] values = new int[n];
		
		for (int i = 0; i < values.length; i++){
			values[i] = sc.nextInt();
		}
		int smallestSoFar = values[0];
		int smallestPosition = 0;

		for (int i = 0; i < values.length; i++){
			if (values[i] < smallestSoFar){
				smallestSoFar = values[i];
				smallestPosition = i;
			}
		}
		int temp = values[0];
		values[0] = values[smallestPosition];
		values[smallestPosition] = temp;

		for (int i = 0; i < values.length; i++) {
			System.out.println(values[i]);
		}
		//Let the looping begin! (and declare the array)
		//While this can be done in two loops,
		//if you're not sure, do the three
		//steps that require loops as separate loops.
		//Always remember, working is better than
		//perfect.
	}
}
