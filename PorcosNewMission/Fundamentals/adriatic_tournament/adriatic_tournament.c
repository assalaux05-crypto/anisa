#include "adriatic_tournament.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>





void simulate_pilot(const char *pilot_name) {


    if(pilot_name==NULL)return ;
    int i=0;
    int score=0;
    while(pilot_name[i]!='\0')
    {
        if ('A'<=pilot_name[i] && 'Z'>=pilot_name[i])
        {
            score=score+(pilot_name[i]-'A'+1);
        }
        if ('a'<=pilot_name[i] && 'z'>=pilot_name[i] )
        {
            score=score+(pilot_name[i]-'a'+1);
        }
        i++;
    }
    score=score%1000;
    char filename[128];
    snprintf(filename,sizeof(filename),"result_%s.txt",pilot_name);
    FILE* f=fopen(filename,"w");
    if (!f)return ;
    fprintf(f,"%d\n",score);
    fclose(f);

}
/*
int main(void)
{
    const char *pilot_name = "Curtis";

simulate_pilot(pilot_name);
return 0;
}
*/

struct PilotResult *load_tournament_results(char **pilots_names) {

    /*
    struct PilotResult
{
    char name[64];
    int score;
    struct PilotResult *next;
};
    
    */
    if(pilots_names==NULL || *pilots_names==NULL)return NULL;
    int i=0;
    struct PilotResult* head=NULL;
    struct PilotResult* fin=NULL;
   
    while(pilots_names[i]!=NULL)
    {
        char file[128];
        int score=0;
        snprintf(file,sizeof(file),"result_%s.txt",pilots_names[i]);

        FILE* f=fopen(file,"r");
        if(!f)
        {
            printf("Error : Could not open file\n");
            destroy_results(head);
            return NULL;
        }
         struct PilotResult* box=malloc(sizeof(struct PilotResult));
        if(!box)
        {
            fclose(f);
            destroy_results(head);
            return NULL;
        }
        if(fscanf(f,"%d",&score)!=1)
        {
            free(box);
            fclose(f);
            destroy_results(head);
            return NULL;
        }
        strcpy(box->name,pilots_names[i]);
            box->score=score;
            box->next=NULL;
        if(head==NULL)
        {
            head=box;
            fin=box;
        }
        else 
        {
            fin->next=box;
            fin=box;
        }
        

        i++;
        fclose(f);
        
    }
    
    return head;



}

struct PilotResult *sort_results_by_score(struct PilotResult *head)
{
 if (head == NULL)return NULL;
int swap = 1;
while (swap == 1)
    {
        swap = 0;
        struct PilotResult *lst = head;
        while (lst != NULL && lst->next != NULL)
        {
            if (lst->score < lst->next->score)
            {
                char name[64];
                int score;
                strcpy(name, lst->name);
                strcpy(lst->name, lst->next->name);
                strcpy(lst->next->name, name);
                score = lst->score;
                lst->score = lst->next->score;
                lst->next->score = score;
                swap = 1;
            }
            lst = lst->next;
        }
    }

    return head;
}



void print_tournament_ranking(const struct PilotResult *head)
{
    int rank = 1;
    const struct PilotResult *lst= head;

    while (lst != NULL)
    {
        printf("%d. %s score : %d\n", rank, lst->name, lst->score);
        rank++;
        lst = lst->next;
    }
}

void destroy_results(struct PilotResult *head)
{
    struct PilotResult *lst= head;

    while (lst != NULL)
    {
        struct PilotResult *next = lst->next;
        free(lst);
        lst = next;
    }
}

void run_adriatic_tournament(char **pilots_names)
{
    int count = 0;

    while (pilots_names[count] != NULL)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            for(int i=0; i<count;i++)
            {
                wait(NULL);
            }
            return ;
        }

        if (pid == 0)
        {
            simulate_pilot(pilots_names[count]);
            exit(0);
        }

        count++;
    }

    for (int i = 0; i < count; i++)
    {
        wait(NULL);
    }

    struct PilotResult *results = load_tournament_results(pilots_names);
    struct PilotResult *sorted = sort_results_by_score(results);

    print_tournament_ranking(sorted);
    destroy_results(sorted);
}
