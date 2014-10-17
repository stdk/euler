f = z*(10*y + x) - y*(10*x+z)

for a in range(0,10):
    for b in range(0,10):
        for c in range(0,10):
            if f.subs(x,a).subs(y,b).subs(z,c) == 0:
                if a != 0 and b != 0 and c != 0:
                    print a,b,c
