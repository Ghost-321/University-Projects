class CashRegister:
    def __init__(self):
        self.cash = 0

    def add(self, n):
        self.cash += n
    
    def formatted(self, value):
        integer = int(value)
        Int_part = int((value - integer) * 100)
        return '${:d}.{:02d}'.format(integer, Int_part)

    def to_string(self):
        if self.cash < 1:
            return "Cash register: empty"
        else:
            return 'Cash register: {}'.format(self.formatted(self.cash))
