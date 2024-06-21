import java.text.*;

/**
 * Each product has a name, stock and price.
 *
 * You can sell and restock a product.
 */
public class Product {
    private String name;
    private int stock;
    private double price;
    // insert 3 fields here
    // insert 1 constructor here
    public Product (String name, int stock, double price){
        this.name = name;
        this.stock = stock;
        this.price = price;
    }
    /**
     * This pseudo-procedure sells "n" amount of stock.
     * The stock should decrease by "n".
     *
     * This method also returns the money earned from the sale.
     *
     * This is a rare occasion where a procedure returns something.
     */
    public double sell(int n) {
        this.stock -= n;
        return n*price;
        // insert your code here to update the stock
        // a dummy return value - which you will change
    }

    /**
     * Add "n" amount to this product's stock.
     */
    public void restock(int n) {
        this.stock += n;
    }

    public int get_stock() {
        return this.stock;
    }
    /**
     * Return a string in the form:
     *
     * [stock] [name] at $[price]
     *
     * e.g. "200 Sticky tape at $2.99"
     *
     * DO NOT hard code the data in this string
     * or you will be penalised for a spoof.
     */
    @Override
    public String toString() {
        return this.stock + " " + this.name + " at $" + this.price;
    }
}