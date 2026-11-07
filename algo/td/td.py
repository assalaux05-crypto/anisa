#ex3.2

def count(t):
    s=0
    c=t.child
    while c:
        s=s+1
        c=c.sibling
    return s

"""
le nb nod de pere =>p
nb fils 
p>=nb fils return false 

"""
def aux(t,p)

c=t.child
nb_fils=count(t)
if c==None:
    return True 
if p>=nb_fils:
    return false
while c:
    res=aux(c,nb_fils)
    if  res==false:
     return false
    c=c.sibling
return True 


def or(t)
return aux(t,0)

"""

            a
b     c    d    e      
hijkf hhhh ooooo  mmmmm
    rr
"""
def or(t)

c=t.child
nb_fils=count(t)
if c==None:
    return True 

while c:
    if count(c)>=nb_fils:
    return false
    res=aux(c)
   if  res==false:
    return false
    c=c.sibling
return True 





#ex3.3
#[b c d e]
"""
   
"""

            a
b     c    d    e      
hijkf hhhh ooooo  mmmmm
    rr
""" 
"""
def aux(t)

tot=1
interne=0
a,b=aux
c=a
d=b
if t.nbchildren !=0:
    intern +=1
for child in t.children:
    a,b=aux(t)
    tot+=a
    intern+=b
        

return tot,intern 

def arite(t)
tot,interne=aux(t)
tot=tot-1
return tot /intern 




