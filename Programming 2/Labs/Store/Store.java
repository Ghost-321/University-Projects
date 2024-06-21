/**
 * The store has and sells one product: Sticky tape.
 *
 * You can sell and restock a product, view stock and view cash.
 */
public class Store {
    private CashRegister cash_register;
    private Product sticky_tape;
    
    public static void main(String[] args){
        Store store = new Store();
        store.use(); 
    }
    // insert main method here
    // insert 2 fields here
    // insert 1 constructor here
    public Store() {
        this.cash_register = new CashRegister(); 
        this.sticky_tape = new Product("Sticky tape", 200, 2.99); 
    }
    public void use() {
        char choice;
        while ((choice = readChoice()) != 'x') {
            switch (choice) {
            case '?':
                help();
                break;
            case 'v':
                viewStock();
                break;
            case 's':
                sell();
                break;
            case 'r':
                restock();
                break;
            case 'c':
                viewCash();
                break;
            default:
                break;
            }
        }
        System.out.println("Done");
    }

    private void sell() {
        System.out.print("Number: ");
        int amount = In.nextInt();
        if (amount > sticky_tape.get_stock()) {
            System.out.println("Not enough stock");
        }
        else {
            this.cash_register.add(this.sticky_tape.sell(amount));
        }
    }

    private void restock() {
        System.out.print("Number: ");
        int amount = In.nextInt();
        this.sticky_tape.restock(amount);
    }

    private void viewStock() {
        System.out.println(this.sticky_tape.toString());
    }

    private void viewCash() {
        System.out.println(this.cash_register.toString());
    }

    private void help() {
        System.out.println("Menu options");
        System.out.println("s = sell");
        System.out.println("r = restock");
        System.out.println("v = view stock");
        System.out.println("c = view cash");
        System.out.println("x = exit");
    }
    public char readChoice() {
        System.out.print("Choice (s/r/v/c/x): ");
        return In.nextChar();
    }
}
