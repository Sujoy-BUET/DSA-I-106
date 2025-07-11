#include <stdio.h>
#include <stdlib.h>

struct linkedList;

typedef struct node
{
    int element;
    struct node* next;
    struct node* prev;
    struct linkedList* adjacencyList; 
} node;

typedef struct linkedList
{
    node *head;
    node *tail;
    node *curr;
} linkedList;

void init(linkedList* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->curr = NULL;
}

void free_list(linkedList* list)
{
    node *t = list->head;
    while(t!=list->tail){
        t = t->next;
        free(t->prev);
    }
    if(t!=NULL) free(t);
    list->head = list->tail = list->curr = NULL;
}

void print(linkedList* list)
{
    node *t=list->head;
    if(list->head==NULL) printf(" . ");
    while(t!=NULL){
        printf("%d ",t->element);
        t = t->next;
    }
    printf("\n");
}

void insert(int item, linkedList* list)
{
    node *p=(node *)malloc(sizeof(node)); 
    p->element = item;
    if(list->head==NULL){
        p->next = NULL;
        p->prev = NULL;
        list->head = p;
        list->curr = p;
        list->tail = p;
        print(list);
        return;
    }
    p->next = list->curr->next;
    p->prev = list->curr;
    if(list->curr->next!=NULL) list->curr->next->prev = p; 
    list->curr->next = p;
    if(list->curr==list->tail) list->tail = p;
    list->curr = p;
    print(list);
}

int delete_cur(linkedList* list)
{
    if(list->head==NULL){
        printf("List is empty\n");
        print(list);
        return -1;
    }else if(list->curr == list->head){
        int ans = list->head->element;
        list->head = list->head->next;
        if(list->head!=NULL){ 
            free(list->head->prev);
            list->head->prev = NULL;
        }
        print(list);
        return ans;
    }else if(list->curr==list->tail){
        int ans = list->tail->element;
        node *p = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->curr = list->tail;
        free(p);
        print(list);
        return ans;
    }else{
        int ans = list->curr->element;
        node *p = list->curr;
        list->curr->prev->next = list->curr->next;
        list->curr->next->prev = list->curr->prev;
        list->curr = list->curr->next;
        free(p);
        print(list);
        return ans;
    }
}

void append(int item, linkedList* list)
{
    node *p = (node *)malloc(sizeof(node));
    p->element = item;
    p->next = NULL;
    if(list->head==NULL){
        p->prev = NULL;
        list->head = list->tail = list->curr = p;
        //print(list);
        return;
    }
    p->prev = list->tail;
    list->tail->next = p;
    list->tail = p;
    //print(list);
}

int size(linkedList* list)
{
    int sz = 0;
    node *t = list->head;
    while(t!=NULL){
        sz++;
        t = t->next;
    }
    return sz;
}

void prev(int n, linkedList* list)
{
    while(n--){
        if(list->curr==list->head){ 
            print(list);
            return;
        }
        list->curr = list->curr->prev;
    }
    print(list);
}

void next(int n, linkedList* list)
{
    while(n--){
        if(list->curr==list->tail){
           print(list);
           return;
        }
        list->curr = list->curr->next;
    }
    print(list);
}

int is_present(int n, linkedList* list)
{
    node *t = list->head;
    while(t!=NULL){
        if(t->element==n) return 1;
        t = t->next;
    }
    return 0;
}

void clear(linkedList* list)
{
    free_list(list);
    print(list);
}

void delete_item(int item, linkedList* list)
{
    if(list->head==NULL) return;
    node *t = list->head;
    while(t!=NULL){
        if(t->element == item){
            if(t==list->head){
                list->head = t->next;
                if (list->head) list->head->prev = NULL;
                if (list->curr == t) list->curr = list->head;
            }else if(t==list->tail){
                t->prev->next = NULL;
                list->tail = list->tail->prev;
                if(list->curr==t){
                    list->curr = list->curr->prev;
                }
            }else{
                if(t==list->curr){
                    list->curr = list->curr->next;
                }
                t->prev->next = t->next;
                t->next->prev = t->prev;
            }
            free(t);
            //print(list);    
            return;
        }
        t = t->next;
    }
    //printf("%d not found\n",item);
}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    int list_size = size(list);
    if(ind1<0 || ind2<0 || ind1>=list_size || ind2>=list_size){
        printf("Invalid index\n");
        return;
    }
    node *p1,*p2;
    p1 = p2 = list->head;
    for(int i=0;i<ind1;i++){
        p1 = p1->next;
    }
    for(int i=0;i<ind2;i++){
        p2 = p2->next;
    }
    int temp = p1->element;
    p1->element = p2->element;
    p2->element = temp;
    print(list);
}

// you can define helper functions you need