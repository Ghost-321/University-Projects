# Write your function here.
def mult(x,y):
    return x*y
# You do not need to change anything below here.
# It shouldn't hurt though.


if __name__ == "__main__":
    print("Enter a number: ", end="")
    a = int(input())
    print("Enter another number: ", end="")
    b = int(input())

    print("a x b = " + str(mult(a, b)))
