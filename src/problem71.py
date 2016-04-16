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

def search(limit,a,b):    
    q = limit
    while q != 0:
        p,mod = divmod(a*q-1,b)
        if mod == 0:
            return p/gcd(p,q)
        q -= 1

if len(argv) != 4:
    print 'Usage:', argv[0], '<max denominator> <a> <b>'
else:        
    print search(*[int(arg) for arg in argv[1:]])
