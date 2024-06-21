public class Player {
    private String name;
    private Double credit;
    private String level;
    private Integer age;
    private String team;
    private Integer No;
    
    //private //Input menu class
    
    public Player(String name, Double credit, Integer age, Integer No, String team)
    {
        this.name = name;
        this.credit = credit;
        this.age = age;
        this.No = No;
        this.team = team;

        calculate();
    }

    public String getName() {
        return this.name;
    }

    public int getNumber() {
        return this.No;
    }
    public double getCredit() {
        return credit;
    }

    public int getAge() {
        return age;
    }

    public String getTeam() {
        return team;
    }
    public void calculate() {
        if (this.credit < 1000) {
            this.level = "Edge";
        }
        else if (this.credit >= 1000 && this.credit < 1500) {
            this.level = "Common";
        }
        else if (this.credit >= 1500 && this.credit < 2000){
            this.level = "Core";
        }
        else {
        this.level = "All Star";
        }
    }
        public String getLevel() {
        return level;
    }
    public void setName(String name) {
        this.name = name;
    }

    public void setCredit(double credit) {
        this.credit = credit;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setNumber(int number) {
        this.No = number;
    }

    public void setLevel(double credit) {
        if (credit < 1000) {
            this.level = "Edge";
        } else if (credit >= 1000 && credit < 1500) {
            this.level = "Common";
        } else if (credit >= 1500 && credit < 2000) {
            this.level = "Core";
        } else {
            this.level = "All Star";
        }
    }
}
