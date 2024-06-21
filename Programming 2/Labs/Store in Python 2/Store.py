from Product import *
from CashRegister import *

class Store:

    def __init__(self):
        self.cash_register = CashRegister()
        self.products = [Product("Whiteboard Marker", 85, 1.5),
                        Product("Whiteboard Eraser", 45, 5),
                        Product("Black Pen", 100, 1.5), 
                        Product("Red Pen", 100, 1.5),
                        Product("Blue Pen", 100, 1.5)]
    
    def readChoice(self):
        return str(input("Choice (s/r/v/c/p/x): "))

    def use(self):
        choice = 0
        while choice != 'x':
            choice = self.readChoice()
            if choice == 'v':
                self.view_stock()
            elif choice == 'r':
                self.restock()
            elif choice == 's':
                self.sell()
            elif choice == 'c':
                self.view_cash()
            elif choice == 'p':
                self.prune()
            elif not choice == 'x':
                self.help_menu()
        print("Done")
    

    def readPrice(self):
        return float(input("Price: $"))
    def readNumber(self):
        return int(input("Number: "))
    def readName(self):
        return str(input("Name: "))
    
    def restock(self):
        name = self.readName()
        matching_products = []
        for product in self.products:
            if name.lower() in product.get_name().lower():
                matching_products.append(product)
        if len(matching_products) == 0:
            print ("Adding new product")
            new_amount = self.readNumber()
            new_price = self.readPrice()
            self.products.append(Product(str(name), new_amount, new_price))
        else:
            for product in matching_products:
                print("Restocking " + str(product.get_name()))
                product.restock(int(self.readNumber()))
    def sell(self):
        name = self.readName()
        potential_products = []
        for product in self.products:
            if name.lower() in product.get_name().lower():
                potential_products.append(product)
        if len(potential_products) == 0:
            print("No such product")
        elif len(potential_products) == 1:
            selected_product = potential_products[0]
            print ("Selling " + str(selected_product.get_name()))
            amount = self.readNumber()
            if selected_product.has(amount):
                self.cash_register.add(selected_product.sell(amount))
            else:
                print("Not enough stock")
        else:
            print("Multiple products match:")
            for product in potential_products:
                print(product.to_string())
    def view_cash(self):
        print(self.cash_register.to_string())
    def  prune(self):
        removed_products = []
        for product in self.products:
            if product.is_empty():
                removed_products.append(product)
        for product in removed_products:
            self.products.remove(product)
    def view_stock(self):
        for product in self.products:
            print(product.to_string())
    def help_menu(self):
        print("Menu options\ns = sell\nr = restock\nv = view stock\nc = view cash\np = prune products\nx = exit")
store = Store()
store.use()
