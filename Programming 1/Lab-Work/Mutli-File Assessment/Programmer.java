public class Programmer extends Person {
	
	private String language;
	
	public Programmer(String name, String language) {
		super(name);
		this.language = language;
	}
	
	@Override
	public String toString() {
		return super.toString() + " I like to program in " + this.language + ".";
	}

    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        if (!(o instanceof Programmer)) return false;
        Programmer other = (Programmer)o;
        return (this.getName().equals(other.getName()) && this.language.equals(other.language));
    }
}
