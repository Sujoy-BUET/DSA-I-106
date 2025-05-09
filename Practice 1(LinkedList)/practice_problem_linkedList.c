#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

void append(struct Node** head, int value){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node)); // don't allocate for struct Node*
    temp->data = value;
    temp->next = NULL;
    if(*head == NULL){
        *head = temp;
        return;
    }
    struct Node *t = *head;
    while(t->next!=NULL){
        t = t->next;
    }
    t->next = temp;
    return;
}

void insert_node(struct Node* head, struct Node* position, int value){
    struct Node *new = (struct Node*)malloc(sizeof(struct Node));
    new->data = value;
    new->next = position->next;
    position->next = new;
    return;
}

// insert in a position(0 based index)
struct Node* insert_index(struct Node* head, int position, int value){ 
    struct Node *new=(struct Node*)malloc(sizeof(struct Node));
    new->data = value;
    new->next = NULL;
    if(position==0){
        head = new;
        return head;
    }
    struct Node *temp = head;
    for(int i=1;i<position;i++){
        temp=temp->next;
    }
    new->next = temp->next;
    temp->next = new;
    return head;
}

void print(struct Node* head){
    struct Node *temp = head;
    while(temp->next!=NULL){
        printf("%d -> ",temp->data);
        temp = temp->next;
    }
    printf("%d\n",temp->data);
}

int getPos(struct Node *head,int pos){
    struct Node *temp = head;
    for(int i=0;i<pos;i++){
        temp = temp->next;
    }
    return temp->data;
}

int listSize(struct Node *head){
    int sz = 0;
    struct Node *temp = head;
    while(temp!=NULL){
        temp = temp->next;
        sz++;
    }
    return sz;
}

struct Node* merge_sorted_lists(struct Node* head1, struct Node* head2){
    struct Node *head = (struct Node*)malloc(sizeof(struct Node*));
    head = NULL;
    struct Node *p1 = head1,*p2 = head2;
    int i=0,j=0;
    while(p1!=NULL && p2!=NULL){
        int num1 = p1->data,num2 = p2->data;
        if(num1<num2){
            append(&head,num1);
            p1 = p1->next;
        }else{
            append(&head,num2);
            p2 = p2->next;
        }
    }
    while(p1!=NULL){
        append(&head,p1->data);
        p1 = p1->next;
    }
    while(p2!=NULL){
        append(&head,p2->data);
        p2 = p2->next;
    }
    return head;
}
    
int main(){
    // taking 1st list
    struct Node *head1 = (struct Node*)malloc(sizeof(struct Node*));
    head1 = NULL;
    printf("Enter the size and elements of 1st list: ");
    int n1;
    scanf("%d",&n1);
    for(int i=0;i<n1;i++){
        int num;
        scanf("%d",&num);
        append(&head1,num);
    }
    // taking 2nd list
    struct Node *head2 = (struct Node*)malloc(sizeof(struct Node*));
    head2 = NULL;
    printf("Enter the size and elements of 2nd list: ");
    int n2;
    scanf("%d",&n2);
    for(int i=0;i<n2;i++){
        int num;
        scanf("%d",&num);
        append(&head2,num);
    }
    // merging 2 lists
    struct Node *merged = merge_sorted_lists(head1,head2);
    printf("Merged List: ");
    print(merged);
    int size = listSize(merged);
    printf("Middle element of merged list: ");
    if(size%2==0){
        printf("%d and %d\n",getPos(merged,size/2-1),getPos(merged,size/2));
    }else{
        printf("%d\n",getPos(merged,size/2));
    }
}