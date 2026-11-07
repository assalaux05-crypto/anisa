#include "../include/update_crew.h"
#include <stdio.h>
#include <stdlib.h>






size_t crew_strlen(const char *str) { 



    int i=0;
    while(str[i]!='\0')
    {
        i++;
    }
    return i;
}


/*
int main(void)
{


    printf("%zu\n", crew_strlen("Pazu")); // 4
printf("%zu\n", crew_strlen(""));     // 0
return 0;
}
*/

int crew_strcmp(const char *s1, const char *s2) { 

    int i=0;
  
   
        while(s1[i]!='\0'&& s1[i]==s2[i])
        {
         
            i++;

        }
        return ((unsigned char)s1[i]-(unsigned char)s2[i]);
    }


/*
int main(void)
{
    printf("%d\n", crew_strcmp("Dora", "Dora"));     // 0
printf("%d\n", crew_strcmp("Dora", "Pazu") ); // 1
}

*/

char *crew_strcpy(char *dest, const char *src) { 


    int i=0;
    while(src[i]!='\0')
    {
        dest[i]=src[i];
        i++;
    }
   dest[i]='\0';
    return dest;


}
/*
int main(void)
{

char name[5];
crew_strcpy(name, "Pazu");
printf("%s\n", name); // Pazu (name[4] is '\0')

}
*/
/*
struct crew_args
{
    struct airship *ship;    dest[i]='\0';
    const char *name;
    int error;
};
*/
// tjr je pense que tous les ouvrier travaillent en meme temps 

void *add_pirate(void *arg) { 

    struct crew_args*grp=(struct crew_args*)arg;
    if(!grp || !grp->ship || !grp->name)
    {
        if(grp)
        {
            grp->error=42;
        }
        return NULL;
    }
   
    /*
    size_t i=0;
    while(i<grp->crew->crew_count)
    {
        i++;
    }*/
    pthread_mutex_lock(&grp->ship->mutex);
    if(grp->ship->crew->crew_capacity==grp->ship->crew->crew_count)
    {
        grp->error=0;
        pthread_mutex_unlock(&grp->ship->mutex);// tjr je pense a unlock 

        return NULL;
    }
    size_t i=grp->ship->crew->crew_count;

    size_t len=crew_strlen(grp->name);
    grp->ship->crew->members[i]=malloc((len+1)*sizeof(char));
    if(!grp->ship->crew->members[i])
    {
        grp->error=42;
        pthread_mutex_unlock(&grp->ship->mutex);

        return NULL;
    }
    crew_strcpy(grp->ship->crew->members[i],grp->name);
    grp->error=0;
  


    grp->ship->crew->crew_count++;
    pthread_mutex_unlock(&grp->ship->mutex);

    
    return NULL;

}
// je pense tjr que le t1 et t2 work in the same time
// tjr lock unlock et bien gerer les cas derruer 
// si un ila fini il return ca impacte pas lautre 
// bien pense a unlock dans les cas derruer 
void *remove_pirate(void *arg) { 


    struct crew_args*grp=(struct crew_args*)arg;
    if(!grp || !grp->ship || !grp->name)
    {
        if (grp)
        {
            grp->error=42;
        }
        return NULL;
    }
    pthread_mutex_lock(&grp->ship->mutex);
    for(size_t i=0;i<grp->ship->crew->crew_count;i++)
    {
        if(crew_strcmp(grp->name,grp->ship->crew->members[i])==0)
        {
            free(grp->ship->crew->members[i]);
            for(size_t j=i;j<grp->ship->crew->crew_count-1;j++){

                grp->ship->crew->members[j]=grp->ship->crew->members[j+1];

            }
            grp->ship->crew->members[grp->ship->crew->crew_count-1]=NULL;

                grp->ship->crew->crew_count--;

            pthread_mutex_unlock(&grp->ship->mutex);
            grp->error=0;
            return NULL;// oblige pour dire que le thread actuel a terminer son travail

        }
    }
    grp->error=0;
    pthread_mutex_unlock(&grp->ship->mutex);//oblige unlock si le name nexiste pas 

    return NULL;




}

// lecture seul jai pas besoin de mutex 
// pas besoin de join chaque t est indepandant de lautre 
void *find_pirate_worker(void *arg) { 


struct crew_search_args* grp=(struct crew_search_args*)arg;


if(!grp || !grp->crew || !grp->name)
{

    if(grp)
    {
        grp->found=0;
    }
    return NULL;

}
    for (size_t i=0;i<grp->crew->crew_count;i++)
    {
        if(crew_strcmp(grp->name,grp->crew->members[i])==0)
        {
            grp->found=1;
            return NULL;
        }
    }
    grp->found=0;
    return NULL;





}
/*
struct crew_search_args
{
    const struct crew *crew;
    const char *name;
    int found;
};

*/

int update_crew(struct airship *ship, const char **names, size_t n) { 

        if (!ship || !ship->crew)return 42;
        
        if(n==0)return 0;
    
        if(!names)return 42;
        for(size_t i=0;i<n;i++)
        {
            if(!names[i])
            {
                return 42;
            }
        }
    

    
    pthread_t *t=malloc(n*sizeof( pthread_t));
    if(!t)return 42;
    struct crew_search_args* grp=malloc(n*sizeof(struct crew_search_args));
    if(!grp)
    {
        free(t);
         return 42;
    }
   

    for(size_t i=0;i<n;i++)
    {
        grp[i].crew=ship->crew;
        grp[i].name=names[i];
        grp[i].found=0;
       if( pthread_create(&t[i],0,find_pirate_worker,&grp[i])!=0)
       {
        for(size_t j=0;j<i;j++)
        {
            pthread_join(t[j],NULL);
        }
       
        free(grp);
        free(t);
        return 42;
        }
    }
    for(size_t i=0;i<n;i++)
    {
         pthread_join(t[i],NULL);
    }
    
    /*
struct crew_args
{
    struct airship *ship;    dest[i]='\0';
    const char *name;
    int error;
};
*/
    
    
    struct crew_args m;
    m.ship=ship;
    for(size_t i=0;i<n;i++)
    {
        m.name=names[i];
        m.error=0;
        if(grp[i].found==1)
    {
        remove_pirate(&m);
        
    }
    else 
    {
            add_pirate(&m);

    }
    if(m.error!=0)
    {
        free(grp);
        free(t);
        return 42;
    }
    
   


    }
    

     free(grp);
    free(t);
    return 0;


    

}