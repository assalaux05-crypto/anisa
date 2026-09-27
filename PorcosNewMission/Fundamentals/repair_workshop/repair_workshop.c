#include "repair_workshop.h"





void add_repair(struct Repair **head, struct Repair *r) {

    if (head==NULL || r==NULL)
    {
        printf("Error : Invalid Parameter\n");
        return ;
    }
    
 /*
    if(*head==NULL)
    {
        r->next=NULL;
        *head=r;
        return ;
    }
    struct Repair* lst=*head;
    struct Repair* act=r;
    while(act->next!=NULL)
    {
        act=act->next;
    }
    act->next=lst;
    *head=r;*/
   //yeah tanq insertion at begin sema 
   r->next=*head;
   *head=r;



}
/*
int main(void)
{
struct Repair *head = NULL;
struct Repair *r = malloc(sizeof(struct Repair));
strcpy(r->client, "Porco Rosso");
strcpy(r->repair_type, "Changing motor");
strcpy(r->date, "17/06/1929");
r->cost = 45000.00;

add_repair(&head, r);
// head is now r
// r->next is now NULL
printf("%s\n",head->client);
return 0;
}
*/
struct Repair *rev(struct Repair *head)
{
    struct Repair *prev = NULL;
    struct Repair *curr = head;
    struct Repair *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}
struct Repair *load_repairs(const char *filename) {
    if(filename ==NULL)return NULL;

FILE* f=fopen(filename,"rb");
if(!f)return NULL;

struct Repair* head=NULL;
    while (1)
{
    struct Repair *r = malloc(sizeof(struct Repair));

    if (!r)
    {
        fclose(f);
        while (head != NULL)
        {
            struct Repair *suiv = head->next;
            free(head);
            head = suiv;
        }
        return NULL;
    }

    if (fread(r->client, sizeof(r->client), 1, f) != 1)
    {
        if (feof(f))
        {
            free(r);
            break;
        }

        free(r);
        fclose(f);

        while (head != NULL)
        {
            struct Repair *suiv = head->next;
            free(head);
            head = suiv;
        }
        return NULL;
    }

    if (fread(r->repair_type, sizeof(r->repair_type), 1, f) != 1
        || fread(r->date, sizeof(r->date), 1, f) != 1
        || fread(&r->cost, sizeof(r->cost), 1, f) != 1)
    {
        free(r);
        fclose(f);

        while (head != NULL)
        {
            struct Repair *suiv = head->next;
            free(head);
            head = suiv;
        }
        return NULL;
    }

    r->next = NULL;
    add_repair(&head, r);
}
fclose(f);
return rev(head);
}
/*
int main(void)
{
const char *filename = "repairs.bin";

struct Repair *head = load_repairs(filename);
// head now points to the first repair stored in repairs.bin

printf("%s - %s\n", head->next->client, head->next->next->client); // Curtis - Mamma Aiuto Gang
}





*/
int save_repairs(const char *filename, const struct Repair *head) {

if(filename==NULL)return 1;

FILE* f=fopen(filename,"wb");
if(!f)return 1;
const struct Repair* actuel=head;
while(actuel !=NULL)
{


   if(fwrite(actuel->client,sizeof(actuel->client),1,f)!=1
    || fwrite(actuel->repair_type,sizeof(actuel->repair_type),1,f)!=1
    || fwrite(actuel->date, sizeof(actuel->date), 1, f)!=1
    || fwrite(&actuel->cost, sizeof(actuel->cost), 1, f)!=1
) 
    {
        fclose(f);
        return 1;
    }



    actuel=actuel->next;
}
fclose(f);
return 0;


}
/*
struct Repair
{
  char client[32];
  char repair_type[64];
  char date[16];
  double cost;
  struct Repair *next;
};
*/
struct Repair *sort_repairs(struct Repair *head, int (*compare_fn)(const struct Repair *, const struct Repair *)) 
{
    if(head==NULL)return NULL;
    int switchh=1;

    while(switchh==1){
        switchh=0;
        struct Repair* lst=head;
        while(lst!=NULL && lst->next!=NULL)
        {
            

            if(compare_fn(lst,lst->next)==1)
            {
            /*switch entre les deux */
            struct Repair* lstnexto=lst->next;
            struct Repair* nlstnexto=lst->next->next;
            
            struct Repair tmp=*lst;/*A*/
            *lst=*lstnexto;/*B*/
            *lstnexto=tmp; 

            lst->next=lstnexto;
            lst->next->next=nlstnexto;
                switchh=1;
            }
        


            lst=lst->next;
        }
    }
    return head;
}
