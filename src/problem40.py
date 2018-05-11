#!/usr/bin/env python
d = iter([10**i for i in range(1,10)])
current_position = d.next()
end_position = 9
product = 1
for i in range(2,7):
    begin = 10**(i-1)
    end = 10**i - 1
    count = (end-begin+1)*i
    new_end_position = end_position + count
    while current_position < new_end_position:
        relative_position = current_position - end_position
        q,r = divmod(relative_position,i)
        digit = ((q+begin) // 10**(i-r)) % 10
        product *= digit
        current_position = d.next()
    end_position = new_end_position
print product
