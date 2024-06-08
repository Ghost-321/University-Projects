n = int(input())

if n >= 5 and n <= 10 and n != 7:
    n+= 2
# Put your if-elif in here
elif n < 5 and n % 2 == 0:
    n //= 2
elif n==7:
    n+= 1
elif n<5 and n % 2 ==1 or n > 10:
    n *= 3


# Anything after the print statement is not useful

print(n)
