import numpy as np

def combo_count_bruteforce(target,value=0,nominals=None):
    if nominals is None:
        nominals = [200,100,50,20,10,5,2,1]    
    sum = 0
    if len(nominals)==1:
        return 1 if value % nominals[0] == 0 else 0    
    for i in range(value, target+1, nominals[0]):
        sum += combo_count(target,i,nominals[1:])
    return sum
    
def combo_count_dynamic(target,value=0,nominals=None):
    if nominals is None:
        nominals = [1,2,5,10,20,50,100,200]
        
    table = np.zeros((target+1,len(nominals)),dtype=np.int32)    
    
    for i in range(len(nominals)):
        table[0][i] = 1
    
    for i in range(len(table)):
        table[i][0] = 1 if i % nominals[0] == 0 else 0
    
    for i in range(1,len(table)):
        for j in range(1,len(nominals)):
            p,q = divmod(i,nominals[j])
            table[i][j] = table[i][j-1] + (table[i-nominals[j]][j] if i >= nominals[j] else 0)
            
    #for i in range(len(table)):
    #    print i,table[i]
        
    return table[-1][-1]

print combo_count_dynamic(200)   
