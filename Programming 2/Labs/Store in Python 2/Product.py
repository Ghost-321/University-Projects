class Product:
    def __init__(self, name, stock, price):
        self.price = price
        self.stock = stock
        self.name = name
    def sell(self, amount):
        self.stock -= amount
        return amount*self.price   
    def get_name(self):
        return self.name
    def is_empty(self):
        return self.stock == 0
    def has(self, amount):
        return self.stock >= amount
    def restock(self, amount):
        self.stock += amount
    def formatted(self, value):
        return '${:,.2f}'.format(value).replace("$", "")
        
    def to_string(self):
        return str(self.name) + " - " + str(self.stock) + " at $" + str(self.formatted(self.price))
