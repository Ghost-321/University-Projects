public abstract class Person {

    private String name;

    public Person(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

	@Override
	public String toString() {
		return "Hi, I'm " + name + ".";
	}

    @Override
    public abstract boolean equals(Object other);
}
