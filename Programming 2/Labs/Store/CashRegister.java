import java.text.*;


public class CashRegister {
    private double cash;

    public CashRegister() {
        this.cash = 0;
    }

    public void add(double n) {
        this.cash += n;
    }

     public String formatted (double value) {
        DecimalFormat f = new DecimalFormat("###,##0.00");
        return f.format(value);
     }
    @Override
    public String toString() {
        if (cash < 1) { 
            return "Cash register: empty";
        }
        else {
            return "Cash register: $" + formatted(this.cash);
        }
        
    }
}
