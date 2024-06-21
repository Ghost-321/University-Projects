class Product:
    def __init__(self, name, stock, price):
        self.name = name
        self.stock = stock
        self.price = price

    def sell(self, amount):
        self.stock -= amount
        return self.price*amount
    
    def get_stock(self):
        return self.stock

    def restock(self, amount):
        self.stock += amount
    
    def to_string(self):
        return str(self.stock) + " " + str(self.name) + " at $" + str(self.price)
