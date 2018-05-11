#!/usr/bin/env python
criteria = [
    (lambda avail: avail,               lambda n: n%13==0),                           # d7
    (lambda avail: avail & {0,5},       lambda n: n%11==0),                           # d6
    (lambda avail: avail,               lambda n: n%7==0),                            # d5
    (lambda avail: avail & {0,2,4,6,8}, lambda n: True),                              # d4 
    (lambda avail: avail,               lambda n: n%3==0),                            # d3
    (lambda avail: avail,               lambda n: True),                              # d2
    (lambda avail: avail - {0},         lambda n: True),                              # d1   
]

def problem43():
    numbers = []
    basis_len = 3
    for basis in [17*i for i in range(10**(basis_len-1)//17,10**basis_len//17+1)]:
        digits = {basis//10**i%10 for i in range(basis_len)}
        if len(digits) != basis_len:
            continue
            
        candidates = [(basis, {i for i in range(0,10)} - digits)]
        for r,(available_filter,check_digits) in enumerate(criteria):
            if not candidates: break
            candidates = [(d+d0*10**(r+basis_len),avail-{d0})
                          for d,avail in candidates
                          for d0 in available_filter(avail)                          
                          if check_digits(d0*100+d//10**(r+1))]
        numbers += [d for d,a in candidates]
    return numbers

numbers = problem43()
print sum(numbers)
