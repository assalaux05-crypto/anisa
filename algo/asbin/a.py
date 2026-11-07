
#=====================Travals=====================


def pref(a):
    if a==None:
        return []
    res=[a.key]
    c=a.child
    while c:
        res+=pref(c)
        c=c.sibling
    return res 
def suff(a):
    if a==None:
        return []
    c=a.child
    res=[]
    while c:

        res+=suff(c)
        c=c.sibling
    return res+[a.key]
def lvl(a):

    q=Queue()
    q.enqueu(a)
    qn=Queue()
    l=[]
    while not q is_empty():
        nv=[]
        while not q is_empty():
            e=q.dequeu()
            nv.append(e.key)
            c=e.child
            while c:
                qn.enqueu(c)


                c=c.sibling
        q,qn=qn,q
        l.append(nv)
    return l

def plvl(a,k):
    q=Queue()
    q.enqueu(a)
    qn=Queue()
    while not q is_empty() k>0:
        while not q is_empty():
            e=q.dequeue()
            c=e.child
            while c:
                qn.enqueu(c)

                c=c.sibling
        q,qn=qn,qn
        k=k-1
    while not q is_empty():

        e=q.dequeu()
        print(e.key).dequeu()
        print(e.key)
#<3 <3
#<3 <3
"""
            a
        b       c    d        res+=rev(l[i])
    e      f   g  h   k
    a d k c hg bfe 
"""
def rev(a):
    l=[]
    c=a.child
    while c:
        l.append(c)
       c= c.sibling
    res=[a.key]
    for i in range(len(l)-1,-1,-1):
        res+=rev(l[i])
    return res 
# jai pas le droit dappler ma fct rec dans lair tant que ma fct return un truc 
def leaf(a):
    if a.child==None:
        return a
    
    c=a.child
    while c:
        res=leaf(c)


        if res!=None:
            return res
        c=c.sibling
    return None
def lst(a):
    if a.child==None:
        return a

    c=a.child
    res=None
    while c:
        res=lst(c)
        c=c.sibling
        
    return res



#=========================AGGREGATUIN=====================

def sum(t):
    res=t.key
    
    c=t.child
    while c:
            res+=sum(c)
            c=c.sibling
    return res

def min(t):
    mini=t.key
    if t.child==None:
        return t.key
    c=t.child
    while c:
        res=min(c)
        if res<mini:
            mini=res
        c=c.sibling
    return mini

def max(t):


    if t.child ==None:
        return t.key
    maxi=t.key
    c=t.child
    while c:
        res=max(c)
        if res>maxi:
            maxi=res
        c=c.sibling
    return maxi


def sumnb(t):
    #if t.child==None:
        #return (t.key,1) ca rentre pas dans la boucle et ca me return directement 

    else:
        c=t.child
        k=t.key
        n=1
        while c:
            sum,nb=sumnb(c)
            k+=sum
            n+=nb
            c=c.sibling
        return (k,n)

def avrg(t):
    k,n=sumnb(t)
    if n==0:
        return 0
    return k/n


def suml(t):

    if t.child==None:
        res=t.key
    else:
        res=0
    c=t.child
    while c:
        res+=suml(c)
        c=c.sibling
    return res
def pair(t):

    if t.key%2==0:
        res=1
    else:
        res=0
    c=t.child
    while c:
        res+=pair(c)
        c=c.sibling
    return res 


def count(t,x):
    if t.key> x:
        res=1
    else:
        res=0
    c=t.child
    while c:
        res+=count(c,x)
        c=c.sibling
    return res 

### pas de recurssivite je reste sur le premier lvl c qlui qui minteresse 

def max_s(t):
    c=t.child
    maxi=0
    
    while c:
        taille=size(c)
        if taille>maxi:
            maxi=taille 
        c=c.sibling
    return maxi
def sum_level(T, k):
    if k==0:
        return t.key
    res=0
    c=t.child
    
    while c:
        res+=sum_level(c,k-1)
        c=c.sibling
    return res

    

def count(t):
    s=0
    c=t.child
    while c:
        s+=1
        c=c.sibling
    return s

def avrg(t):
    if t==None:
        return 0
    nb_child=count(t)
    c=t.child
    res=0
    while c:
        taille=size(c)
        res+=taille
        c=c.sibling
    return res/nb_child
#===============================SEARCH=======================
"""
    if moi:
        return imediat 
    while c:
        res=fct(c)
        if condition succce:
            return 
        c=c.sibling
    return echou

"""
def contains(t,x):
    
    if t.key==x:
        return True 
    else :
        c=t.child
        while c:

            res=contains(c,x)
            if res==True:
                return res
            c=c.sibling
        return False 
    
def find(t,x)
    if t.key==x:
        return t 
    c=t.child
    while c:
        res=find(c,x)
        if res!=None:
            return res
        c=c.sibling
    return None 
#suffix je commence pas mes fils apres moi en dernier 
def findsuff(t,x):
    c=t.child
    while c:
        res=findsuff(c,x)
        if res!=None:
            return res
        c=c.sibling
        if t.key==x:
            return t 
    return None 
def occ(t,x):
    if t==None:
        return 0
    cpt=0
    if t.key==x:
        cpt+=1
    c=t.child
    while c:
        cpt+=occ(c,x)
        c=c.sibling
    return cpt 
def mini(t)
    if t==None:
        return None
    c=t.child
    min=t

    while c:
        res=mini(c)

        if res!= None and min.key>res.key:
            min=res
        c=c.sibling

    return min




#================== struct Prop===================


def is_chain(t)
    if t==None:
        return True 
 
    if  not t.child and not t.child.sibling:
        return False 
    c=t.child
    while c:
        res=is_chain(c)
        if res==False :
            return res
        c=c.sibling
    return True 


def star(t):
    if t==None:
        return True 
    c=t.child
    while c:
        if c.child!=None:
            return False 
        c=c.sibling
    return True 