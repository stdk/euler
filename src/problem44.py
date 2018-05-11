#!/usr/bin/env python
def pentagon(n):
    return n*(3*n-1)//2    

def search(max_distance = 500,max_index = 3000):
    pentagons = [pentagon(i) for i in xrange(max_index+max_distance)]
    pentagons_set = frozenset(pentagons)
    for distance in range(1,max_distance):
        for x in range(1,max_index):
            y = x + distance
            diff = pentagons[x]
            summ = pentagons[y]
            
            first,remainder = divmod(diff+summ,2)
            if remainder==0:
                if first in pentagons_set:
                    second = summ - first
                    if second in pentagons_set:
                        return diff
                    
print search()
