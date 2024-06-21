from Product import *
from CashRegister import *

class Store:
    def __init__(self):
        self.cash_register = CashRegister()
        self.sticky_tape = Product("Sticky tape", 200, 2.99)

    def help_menu(self):
        print("Menu options\ns = sell\nr = restock\nv = view stock\nc = view cash\nx = exit")
    
    def sell(self):
        amount = int(input("Number: "))
        if amount > self.sticky_tape.get_stock():
            print("Not enough stock")
        else:
            self.cash_register.add(self.sticky_tape.sell(amount))
    def restock(self):
        amount = int(input("Number: "))
        self.sticky_tape.restock(amount)
    
    def view_stock(self):
        print(self.sticky_tape.to_string())
    
    def view_cash(self):
        print(self.cash_register.to_string())
    
    def use(self):
        decision = 0
        while decision != 'x':
            decision = str(input("Choice (s/r/v/c/x): "))
            if decision =='s':
                self.sell()
            if decision == 'r':
                self.restock()
            if decision == 'c':
                self.view_cash()
            if decision == 'v':
                self.view_stock()
            if decision == '?':
                self.help_menu()
        print("Done")
store = Store()
store.use()
