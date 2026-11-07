#n uplet



#=============================BASIC===========================
"""
squellete de count

if condition :
    res=
else:
    res=
for child in t.children:
    res+=rec(child)
return res 

"""
def count(t):
    if t==None:
        return 0
    cpt=0
    for child in range(t.nbchildren):
        cpt+=1
    return cpt 
def is_leaf(t);
    if t==None:
        return false
    else:
        if t.children==[]
            return true
        return false 

def is_intern(t):
    if t==None:
        return false
    else:
        if t.children==[]:
            return False
        return True
def size(t):
    s=1
    for child in t.children:
        s+=size(child)
    return s

def nb_leaves(t):
    res=0

    if t.children==None:
        return 0:
    if t.children==[]:
        return 1
    for child in t.children:
        res+=nb_leaves(child)
    return res 


"""

                A
            B       C
        D     E
    F
     [D,e]
     [f]
"""

def nb_inter(t):
    if t.children!=[]:
        res=1 
    else:
        res=0
    for child in t.children:
        res+=nb_inter(child)
    return res 
#lvl bfs
"""
def bfs(t):
    q = Queue()
    q.enqueue(t)
    qn=Queue()
    while not q.is_empty():
                        
        while not q.is_empty():       
            e = q.dequeue()
            
            for child in e.children:
                qn.enqueue(child)
        
        q,qn = qn,q           

"""
def node_at_level (t,k):

    q=Queue()
    q.enqueu(t)
    qn=Queue()
    cpt=0
    while not q is_empty() and k>0:
        while not q is_empty():
            e=q.dequeue()
            for child in e.children:
                qn.enqueu(child)
        k=k-1
        q,qn=qn,q
    if k==0:
        while not q is_empty():
            q.dequeu()
            cpt=cpt+1
    return cpt

def count(t,x):
    if t.key==x:
        res=1
    else :
        res=0
    for child in t.children:
        res+=count(child,x)
    return res 



#======================HEIGH DEPTH ARITY=================

"""
squellette rec

res=moi
for child int.children:
    option : filtre sur child => je peux avoir une condition sur que le fils que je veux faire lappel
    r_child=f(child)reponse de child
    je combine res=moi et child 
 return res
"""
def height(t):
    
    h=0
    for child in t.children:
        h=max(h,height(child)+1)
    return h
# nv concept res de mon fils +1 
def depth(t,x,p):
    if t.key==x:
        return 0
    for child in t.children:
        res = depth(child)# reponse de mon child
        if res!=-1: #trouver 
            return res+1 # res= depuis mon fils plus moi 
    return -1
def maxi_depth(t):
    #fct height 
def arity(t):

    cpt=0
    for child in t.children:
        cpt+=1
    return cpt

def max_arity(t):
    maxi=arity(t)
    for child in t.children:
        res=max_arity(child)
        if res>maxi:
            maxi=res
        
    return maxi


def min_arity(t):
    mini=arity(t)

    for child in t.children:
        if is_intern(child):
            res=min_arity(child)
            if res < mini:
                    mini=res

    return mini

def arity_sum(t):
    if t.childern==[]:
        return (0,0)
    else:
        nb_fils=t.nbchildren
        intern=1
        for child in t.children:
            s,i=arity_sum(child)
            intern+=i
            nb_fils+=s
    return (nb_fils,intern)

def avrg(t):
    s,n=arity_sum(t)
    if n==0:
        return 0
    return s/n

def count(t,k):
    
    if k==0:
        return 1
    res=0
    for child in t.children:
        
        res+=count(child,k-1)
        
    return res


def level(t):

    q=Queue()
    q.enqueue(t)
    qn=Queue()
    maxl=0
    cpt=0
    maxi=0
    lvl=0
    while not q is_empty():#lvl=0
    #init cpt 
    cpt=0
    
        while not q is_empty():
            e=q.dequeue()#nb node lvl0
            cpt=cpt+1
            for child in e.children:
                qn.enqueu(child)
        if cpt>maxi:
            maxi=cpt
            maxl=lvl #0

        lvl=lvl+1

        q,qn=qn,q
    return maxl
def nb(t):
  q=Queue()
    q.enqueue(t)
    qn=Queue()
    
    cpt=0
    maxi=0
    
    while not q is_empty():#lvl=0
    #init cpt 
    cpt=0
        while not q is_empty():
            e=q.dequeue()#nb node lvl0
            cpt=cpt+1
            for child in e.children:
                qn.enqueu(child)
        if cpt>maxi:
            maxi=cpt
            maxl=lvl #0

        q,qn=qn,q
    return maxi  
#=========================RECHERCHE=====================
"""

                A
            B       C     e
        D     E
    F
     [D,e]
     [f]
"""
def countains(b,x):
    if b==None:
        return False 
    if b.key==x:
        return True
    for child in b.children:
        res=countains(child,x)
        if res:
            return res
    return False 

def find(t,x):
    if t==None:
        return None 
    if t.key==x:
        return t 
    for child in t.children:
        res=find(child)
        if res!=None:
            return res 
    return None
def occ (t,x):
    if t==None:
        return 0
    cpt=0
    if t.key==x:
        cpt=1
    for child in t.children:
        cpt+=occ(child,x)
    return cpt

def max(t)

    if t==None:
        return None 
    maxi=t 
    for child in t.children:
        res=max(child)
        if res!=None and res.key >maxi.key:
            maxi=res
    return maxi


def match(t,p):
    if t==None:
        return None
    if p(t.key):
        return t 
    for child in t.children:
        res=match(child)
        if res!=None:
            return res
    return None 
  
def path(t,x):
   
    if t==None:
        return None 
    if t.key==x:
        return [t.key]
    for c in t.children:
        res=path(c,x)
        if res!=None:
            return [t.key]+res
    return None

"""

qd jai besoin le papa 
    je lajoute on parametre p=None:
    if condition:
        return p 
    for c in t.children:
        res=fct(c,x,t)
        if res!=None:
            return res 
"""
def parent(t,x,p=None)

    if t==None:
        return None
    if t.key==x:
        return p
    for c in t.children:
       res=parent(c,x,t)
         if res!=None:
            return res 
    return None 


def sibling(t,x,y):
    papax=parent(t,x,p=None)
    if papax==None:
        return False 
    for child in papax.children:
        if child.key ==y:
            return True 
    return False 

def aux(t,order):
    if t==None:
            return []
    if order=="prefix":
        
        l=[t.keys]
        for c in t.children:
            l+=aux(c,order)
        return l
    elif order =="suffix":
        l=[]
        for c in t.children:
            l+=aux(c,order)
        return [t.key]+l
    elif order=="level":
        q=Queueu()
        q.enqueu(t)
        
        l=[]
        while not q.is_empty() :
                e=q.dequeue()
                l.append(e.key)
                for child in e.children:
                    qn.enqueue(child)
        return l

def after(t,x,order)
    l=aux(t,order)
    for i in range (len(l)):
        if lst[i]==x:
            return l[i+1:]

    return l
#======================Structural PROPRITIES==============


def pos(t):
    if t==None:
        return True
    if t.key <=0:
        return False
    for c in t.children:
        res=pos(c)
        if res==False:
            return False 
    return True 


def leaf_even(t):
    if t==None:
        return True
    if t.children==[]:
        if t.key%2!=0:
            return False 
    for child in t.children:
        res=leaf_even(child)
        if res==False:
            return False 
    return True 
def inter(t,cond):
    if t==None:
        return True 
    if t.children !=[]:
        if cond(len(t.children))==False :
            return False 
    for c in t.children:
        res=inter(c,cond)
        if res==False:
            return res 
    return True 

def most(t,k):
    if t==None:
        return True
    if len(t.childeren)>k:
        return False 
    for c in t.children:
        res=most(c,k)
        if res==False :
            return res 
    return True 
def fct(t,k):
    if t==None:
        return True 
    if t.children!=[]:
        if len(nb_children)!=k:
            return False 
    for c in t.children:
        res=fct(c,k)
        if res==False:
            return res
    return True 