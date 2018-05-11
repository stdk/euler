#!/usr/bin/env python
def is_binary_palindrome(x):
    b = bin(x)[2:]    
    l = len(b)//2
    return b[:l] == b[::-1][:l]

def reverse_number(x,base):
    r = 0
    while x:
        r = r*base + x%base
        x //= base
    return r

def range_with_digits(n):
    begin = 0
    end = 0
    while n > 0:
        begin = begin*10 if begin else 1
        end = 10*end + 9
        n -= 1
    return begin,end
    
s = 0

for l in range(1,6+1):
    begin,end = range_with_digits(l//2)
    for m in range(10 if l%2==1 else 1):
        for k in range(begin,end+1):
            n = reverse_number(k,10) + m*10**(l//2) + k*10**(l//2 + l%2)
            if is_binary_palindrome(n):
                s += n

print s
