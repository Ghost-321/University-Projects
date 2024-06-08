public class MarksReport {
	
	public static void main(String[] args) {
		
		StudentDatabase database = new StudentDatabase(StudentDatabase.readStudentsFromFile(args[0]));
		
		System.out.println("There are " + database.totalStudents() + " students.");
		System.out.println("The average mark is " + database.averageMark() + ".");
		System.out.println("The best student is " + database.bestMarkName() + " with a mark of " + database.bestMark() + ".");
		System.out.println("The worst student is " + database.worstMarkName() + " with a mark of " + database.worstMark() + ".");
	}
	
}
