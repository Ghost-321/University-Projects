public class Student extends Person {

	private String degree;
	private int year;
	
	public Student(String name, String degree, int year) {
		super(name);
		this.degree = degree;
		this.year = year;
	}
	
	private String ordinalEnding(int cardinal) {
		
		if (cardinal % 100 >= 11 && cardinal % 100 <= 13) return "th";
		
		switch (cardinal % 10) {
			case 1 : 
				return "st";
			case 2 : 
				return "nd";
			case 3 : 
				return "rd";
			default : 
				return "th";
		}
	}
	
	@Override
	public String toString() {
		return super.toString() + " I am studying " + this.degree + ". I am in my " + this.year + ordinalEnding(this.year) + " year.";
	}

    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        if (!(o instanceof Student)) return false;
        Student other = (Student)o;
        return (this.getName().equals(other.getName()) && this.degree.equals(other.degree) && this.year == other.year);
    }

}
