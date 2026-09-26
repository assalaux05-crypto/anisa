#include "address_book.h"





/*
struct Contact
{
  char *name;
  struct Contact *next;
};
*/

void insert_contact(struct Contact **head, size_t index, char *name) {

    if(head==NULL  || name ==NULL)
    
    {   
        printf("Error : Invalid Parameter\n");
        return;
    } 
    struct Contact* box=malloc(sizeof(struct Contact));
    if(!box)
    {
        printf("Error : Memory Allocation Failure\n");
        return ;
    }
    box->name=name;
    box->next=NULL;
    struct Contact* lst=(*head);
    if (index==0 || lst==NULL)
    {
        
        box->next=lst;
        *head=box;
        return;

    }
    for(size_t i=0;i<index-1&& lst->next!=NULL ;i++)
    {
        lst=lst->next;
    }
   
        box->next=lst->next;
        lst->next=box;
    
    

}
void remove_contact(struct Contact **head, size_t index) {

    if (head==NULL || *head==NULL )
    {
        printf("Error : Invalid Parameter\n");
        return;
    }

        struct Contact* tete=*head;
        if (index==0)
        {
            
            *head=tete->next;
            free(tete->name);
            free(tete);
            return ;
        }
        struct Contact* el=*head;
        size_t len=0;
        while(el!=NULL)
        {
            el=el->next;
            len++;
        }
        if(index>=len)return ;
        
        
        struct Contact* lst=*head;
        struct Contact* supp;
        for(size_t i=0;i<index-1;i++)
        {
            lst=lst->next;
        }
        if (lst->next==NULL)return ;
        supp=lst->next;
        lst->next=supp->next;
        free(supp->name);
        free(supp);


}
/*
int main(void)
{
struct Contact *head = NULL;
char *name = malloc(5 * sizeof(char));
char *namee = malloc(6 * sizeof(char));
char *nameee = malloc(7 * sizeof(char));

strcpy(name, "Gina");
strcpy(namee, "Ginna");
strcpy(nameee, "Ginnaa");

insert_contact(&head, 0, name);
insert_contact(&head, 1, namee);
insert_contact(&head, 2, nameee);


size_t index = 0;

remove_contact(&head, index);
// head is now NULL, the contact "Gina" has been freed
while(head!=NULL)
{
printf("%s\n",head->name);
head=head->next;
}
}
*/
void print_book(struct Contact *head) {

    /*
        A b c 
        t l  (a , a)(b,c)(c,b->next=c) c=c boucle
    
    */
    if(head==NULL)
    { 
        printf("\n");
    }
    struct Contact* tortu=head;
    struct Contact* lievre=head;
    while(lievre!=NULL && lievre->next!=NULL)
    {
        tortu=tortu->next;
        lievre=lievre->next->next;
    }
    if (lievre== tortu)
    {
        printf("Error : Loop detected\n");
        return;
    }
    struct Contact* lst=head;
    while(lst->next!=NULL)
    {
        printf("%s -> ",lst->name);
        lst=lst->next;
    }
    printf("%s\n",lst->name);


}
/*
int main(void)
{

struct Contact *head = NULL;

char* gina = malloc(5 * sizeof(char));
char* curtis = malloc(7 * sizeof(char));
strcpy(gina, "Gina");
strcpy(curtis, "Curtis");

insert_contact(&head, 0, gina);
insert_contact(&head, 1, curtis);

print_book(head);
// prints: "Gina -> Curtis\n"



}
*/

void destroy_book(struct Contact *head) { 

    if(head==NULL)return ;
    struct Contact* t=head;
    struct Contact* l=head;
    while(l!=NULL && l->next!=NULL)
    {
        t=t->next;
        l=l->next->next;
    }
    if(l==t)
    {
        printf("Error : Loop detected\n");
    }
    struct Contact* lst=head;
    while(lst!=NULL)
    {
        struct Contact* suiv=lst->next;

        free(lst->name);
        free(lst);
        lst=suiv;
    }
    /*free(lst);*/

    head=NULL;
}
int main(void)
{
char* gina = malloc(5 * sizeof(char));
char* curtis = malloc(7 * sizeof(char));

strcpy(gina, "Gina");
strcpy(curtis, "Curtis");

struct Contact *head = NULL;
insert_contact(&head, 0, gina);
insert_contact(&head, 1, curtis);

destroy_book(head);
// every contact of the list has been freed
}