class CashRegister:
    
    def __init__(self):
        self.cash = 0
    def add(self, amount):
        self.cash += amount
    def formatted(self, value):
        return '${:,.2f}'.format(value).replace("$","")
    def to_string(self):
        return "Cash: $" + str(self.formatted(self.cash))
