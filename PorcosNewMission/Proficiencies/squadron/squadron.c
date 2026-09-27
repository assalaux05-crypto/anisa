#include "squadron.h"



/*

struct squadron
{
    struct seaplane *head;
    struct seaplane *tail;
    size_t size;
};
struct seaplane
{
    size_t tail_number;
    struct seaplane *front;
    struct seaplane *back;
};

*/
struct seaplane *create_seaplane(size_t tail_number)
{

    struct seaplane* box=malloc(sizeof(struct seaplane));
    if(!box)return NULL;
    box->front=NULL;
    box->back=NULL;
    box->tail_number=tail_number;
    return box;
}

struct squadron *create_squadron(void)
{
    struct squadron *box = malloc(sizeof(struct squadron));
    if (!box)
        return NULL;

    box->head = NULL;
    box->tail = NULL;
    box->size = 0;

    return box;
}

void free_squadron(struct squadron *s)
{
    if(s==NULL)return ;
    struct seaplane* lst=s->head;
    /*tete*/
    while(lst!=NULL)
    {
        struct seaplane* suiv=lst->back;
        free(lst);
        lst=suiv;
        
  
    }
    
    free(s);



}
/*
s->head=a
p=new avion 
s = carnt faut update aussi
*/
void squadron_prepend(struct squadron *s, struct seaplane *p)
{
    if (s == NULL || p == NULL)
        return;

    if (s->size == 0 || s->head == NULL)
    {
        p->front = NULL;
        p->back = NULL;
        s->head = p;
        s->tail = p;
    }
    else
    {
        p->front = NULL;
        p->back = s->head;       
        s->head->front = p;
        s->head=p;      
    }

    s->size++;
}


void squadron_append(struct squadron *s, struct seaplane *p)
{
    if (s == NULL || p == NULL)
        return;

    if (s->size == 0 || s->tail == NULL)
    {
        p->front = NULL;
        p->back = NULL;
        s->head = p;
        s->tail = p;
    }

/*

struct squadron
{
    struct seaplane *head;
    struct seaplane *tail;
    size_t size;
};
struct seaplane
{
    size_t tail_number;
    struct seaplane *front;
    struct seaplane *back;
};

*/
    else
    {
        p->front = s->tail;
        p->back = NULL;
        s->tail->back = p;
        s->tail = p;
    }

    s->size++;
}
/*

num flypast
{
    FRONT_FIRST,
    BACK_FIRST,
};
*/
void print_plane(const struct squadron *s, const struct seaplane *p)
{
    /*plan prmier avec []*/
    if (p == s->head || p == s->tail)
        printf("[%zu]", p->tail_number);
    else
        printf("%zu", p->tail_number);
}

void print_squadron(struct squadron *s, enum flypast m)
{
    if (s == NULL)
        return;
    /* fly past voir enum*/
    if (m == FRONT_FIRST)
        printf("l -> r, ");
    else
        printf("r -> l, ");

    /*vide*/
    if (s->size == 0)
    {
        printf("<Empty>\n");
        return;
    }
    /* g->d*/
    if (m == FRONT_FIRST)
    {
        struct seaplane *curr = s->head;/*A*/
        print_plane(s, curr);

        while (curr->back != NULL)
        {
            struct seaplane *next = curr->back;/*B*/
            if (next->front == curr)/* a-> <-b*/
                printf(" <-> ");
            else
                printf(" -> ");

            print_plane(s, next);
            curr = next;
        }
    }
    else
    {
        struct seaplane *curr = s->tail;/*c*/
        print_plane(s, curr);

        while (curr->front != NULL)
        {
            struct seaplane *prev = curr->front;/*b*/
            if (prev->back == curr)
                printf(" <-> ");
            else
                printf(" -> ");

            print_plane(s, prev);
            curr = prev;
        }
    }

    printf("\n");
}