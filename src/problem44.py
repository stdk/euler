def pentagon(n):
    return n*(3*n-1)//2    

def is_perfect_square(x):
    if x < 0: return False
    if x < 2: return True
    a = x
    b = (a)//2
    while a > b:
        a = b
        b = (a + x//a)//2
    if b*b == x:
        return b

def is_pentagon(x):
    d = is_perfect_square(24*x+1)
    if d is not None:
        n,q = divmod(d+1,6)
        if q==0:
            return n

def search(max_distance = 1000,max_index = 3000):
    for distance in range(1,max_distance):
        for x in range(1,max_index):
            y = x + distance
            diff = pentagon(x)
            summ = pentagon(y)
            first,remainder = divmod(diff+summ,2)
            if remainder==0:
                first_index = is_pentagon(first)
                if first_index is not None:
                    second = summ - first
                    second_index = is_pentagon(second)
                    if second_index is not None:
                        return diff
                    
print search()