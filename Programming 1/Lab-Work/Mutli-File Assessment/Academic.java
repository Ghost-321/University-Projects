public class Academic extends Person {
	private String subject;
	
	public Academic(String name, String subject) {
		super(name);
		this.subject = subject;
	}
	
	@Override
	public String toString() {
		return super.toString() + " I teach " + this.subject + ".";
	}

    @Override
    public boolean equals(Object o) {
        if (o == null) return false;
        if (!(o instanceof Academic)) return false;
        Academic other = (Academic)o;
        return (this.getName().equals(other.getName()) && this.subject.equals(other.subject));
    }
}
