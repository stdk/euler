#!/usr/bin/env python
from itertools import permutations

digits = set('123456789')
guess = '236 248 274 286 298 342 368 371 384 397 478 482 496 672 694 786 793 892'.split()

products = set()
for g in guess:
    available_digits = digits - set(g)
    for p in permutations(available_digits,6):
        s = ''.join(p)
        a,b,c = [int(k) for k in [s[0]+g[0],s[1:3]+g[1],s[3:]+g[2]]]
        if a*b == c:
            #print a,b,c
            products.add(c)
        a,b,c = [int(k) for k in [s[0]+g[1],s[1:3]+g[0],s[3:]+g[2]]]
        if a*b == c:
            #print a,b,c
            products.add(c)
        a,b,c = [int(k) for k in [g[0],s[0:3]+g[1],s[3:]+g[2]]]
        if a*b == c:
            #print a,b,c
            products.add(c)
        a,b,c = [int(k) for k in [g[1],s[0:3]+g[0],s[3:]+g[2]]]
        if a*b == c:
            #print a,b,c
            products.add(c)

print sum(products)
