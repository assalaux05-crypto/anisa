#include "../include/recruit.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



void* fct_t(void*arg)
{

    int* id=(int*)arg;

    printf("Pirate %d wants to join!\n",*id );
    free(id);
    return NULL;

}





int recruit_pirates(int n) { 

    if(n<0)return 42;
    pthread_t t;
    int *id;
    for(int i=0;i<n;i++)
    {
        id=malloc(sizeof(int));
        if(!id)return 42;

        *id = i + 1; 

        if(pthread_create(&t, NULL,fct_t, id)!=0)
        {
            free(id);
            return 42;
        }
        // puisque jai pas besoin du res du thread jai pas besoin de le wait donc je dis a linux qd mon thread a  termine son job fais le menage apres lui
        if(pthread_detach(t)!=0)
        {
        //free(id) jaurais un double free
        return 42;

        }

    }
 

    return 0;
}


/*

int main(void)
{
    if (recruit_pirates(5) != 0)
        return 42;
    pthread_exit(NULL);
}
*/


