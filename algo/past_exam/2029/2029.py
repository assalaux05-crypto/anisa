


#ex1


def lvl_up(t):


if t.children==[]:
    return True 
q=Queueu()
q.enqueu(t)
qn=Queueu()
actuel=0
prev=0

    while not q.is_empty():
        while not q.is_empty():
            e=q.dequeue()
            actuel+=1
            for child in e.children:
            
                qn.enqueu(child)
        if prev >=actuel:
            return False
         q,qn=qn,q
 
        prev=actuel
        actuel=0
    return True 

def aux(t):

    k=0
    c=t.child
    while c:
        k+=c.key
        c=c.sibling
    return k
    

def check(t):
    if t.child==None:
        return True 
    else:
        k_child=aux(t)
        if t.key!=k_child:
            return False 
        else:
            c=t.child
            while c:
                res=check(c)
                if res==False:
                    return False 
                c=c.sibling
        
    return True
        
