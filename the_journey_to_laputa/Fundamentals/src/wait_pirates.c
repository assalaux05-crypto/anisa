#include "../include/wait_pirates.h"
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>



static void*fct_t(void*arg)
{
    int *id=(int*)arg;
    int prime=1;
    if(*id==1 || *id==0)
    {
        prime=0;
    }
    for(int i=2;i<*id;i++)
    {
        if(*id%i==0)
        {
            prime=0;
            break;
        }
    }
    if(prime==1)
    {
        printf("Pirate %d joined the crew!\n",*id);
    }
        free(id);

    return NULL;

}




int wait_for_pirates(int n) { 


    if(n<0)return 42;
    
    if(n==0)
    {
            printf("All pirates have been checked!\n");
            return 0;
    }
        
    
    pthread_t* t=malloc(n*sizeof(pthread_t));
    if(!t)return 42;
    for(int i=0;i<n;i++)
    {

        
        int*id=malloc(sizeof(int));
        if(!id)
        {
            for(int j=0;j<i;j++)
            {
                pthread_join(t[j],NULL);// je pense tjr a join ce quil ont reussi 

            }    
            
            free(t);
            return 42;

        }
        *id=i;
        if(pthread_create(&t[i],0,fct_t,id)!=0)
        {
            for(int j=0;j<i;j++)
            {
                pthread_join(t[j],NULL);// je pense tjr a join ce quil ont reussi 

            }
            free(id);
            free(t);
            return 42;
        }
        

    }
    for(int i=0;i<n;i++)
    {
        pthread_join(t[i],NULL);
    }
    printf("All pirates have been checked!\n");
    free(t);
    return 0;






}

/*
int main(void)
{
    return wait_for_pirates(10);
}
*/