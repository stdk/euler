from sys import argv

def gcd(p,q):
    if p == q:
        if p == 0:
            return 1
        else:
            return p

    a = abs(p)
    b = abs(q)

    common_multiplier = 1
    while a % 2 == 0 and b % 2 == 0:
        a /= 2
        b /= 2
        common_multiplier *= 2

    while a != 0 and b != 0:
        a,b = max(a,b) - min(a,b), min(a,b)
        a,b = (a/2 if a % 2 == 0 else a), (b/2 if b % 2 == 0 else b)

    if a == 0:
        return b*common_multiplier
    else:
        return a*common_multiplier

def numerator(q):
    return divmod(3*q - 1,7)

def search(limit):    
    q = limit
    while q != 0:
        p,mod = numerator(q)
        if mod == 0:
            return p/gcd(p,q)
        q -= 1

if len(argv) != 2:
    print 'Usage:', argv[0], '<max denominator>'
else:        
    print search(int(argv[1]))          
