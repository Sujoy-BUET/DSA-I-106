#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *array;
    int curr_pos;
    int size;
    int capacity;
    int surprise_called;
} arrayList;

void init(arrayList* list)
{
    list->array = (int *)malloc(2*sizeof(int));
    list->curr_pos = -1;
    list->size = 0;
    list->capacity = 2;
    list->surprise_called = 1;
}

void free_list(arrayList* list)
{
    free(list->array);
}

void increase_capacity(arrayList* list)
{
    list->capacity = 2*list->capacity;
    int *ara = (int *)malloc(list->capacity*(sizeof(int)));
    for(int i=0;i<list->size;i++) ara[i] = list->array[i];
    free(list->array);
    list->array = ara;
    printf("Capacity increased from %d to %d\n",list->capacity/2,list->capacity);
}

void decrease_capacity(arrayList* list)
{
    int new_capacity = list->capacity / 2;
    int *new_array = (int *)malloc(new_capacity * sizeof(int));
    for(int i=0; i<list->size; i++) new_array[i] = list->array[i];
    free(list->array);
    list->array = new_array;
    printf("Capacity decreased from %d to %d\n", list->capacity, new_capacity);
    list->capacity = new_capacity;
}

void print(arrayList* list)
{
    printf("[");
    if(list->size==0){
        printf(" .");
    }
    for(int i=0;i<list->size;i++){
        printf(" %d",list->array[i]); 
        if(i==list->curr_pos) printf("|"); 
    }
    printf(" ]\n");
}

void insert(int item, arrayList* list)
{
    if(list->size!=0){ 
        for(int i = list->size-1;i>=list->curr_pos;i--){
            list->array[i+1] = list->array[i];
        }
    }
    list->curr_pos++;
    list->size++;
    if((list->size*2)>list->capacity) increase_capacity(list);
    list->array[list->curr_pos] = item;
    print(list);
}

int delete_cur(arrayList* list)
{
    // implement deletion of current index function
    if(list->size==0) return -1;
    list->size--;
    int ret = list->array[list->curr_pos];
    for(int i=list->curr_pos;i<list->size;i++){
        list->array[i] = list->array[i+1];
    }
    if(list->curr_pos>=list->size) list->curr_pos--; 
    if((list->size*4)<list->capacity){
        decrease_capacity(list);
    }
    print(list);
    return ret;
}

void append(int item, arrayList* list)
{
    if(list->size==0) list->curr_pos++;
    list->array[list->size] =  item;
    list->size++;
    if((list->size*2)>(list->capacity)){
        increase_capacity(list);
    }
    print(list);
}

int size(arrayList* list)
{
    return list->size;
}

void prev(int n, arrayList* list)
{
    // implement prev function
    while(n--){ 
        if(list->curr_pos==-1) return;
        list->curr_pos--;
    }
    print(list);
}

void next(int n, arrayList* list)
{
    while(n--){
        if(list->curr_pos==list->size){
            list->curr_pos = list->size-1;
            print(list);
            return;
        } 
        list->curr_pos++;
    }
    print(list);
}


int is_present(int n, arrayList* list)
{
    for(int i=0;i<list->size;i++){
        if(list->array[i]==n) return 1;
    }
    return 0;
}

void clear(arrayList* list)
{
    free(list->array);
    list->array = NULL;
    init(list);
    print(list);
}

void delete_item(int item, arrayList* list)
{
    for(int i=0;i<list->size;i++){
        if(list->array[i]==item){
            list->size--;
            for(int j=i;j<list->size;j++){
                list->array[j] = list->array[j+1];
            }
            if(list->curr_pos>=list->size) list->curr_pos--;
            print(list);
            return;
        }
    }
    printf("%d not found\n",item);
}

void swap_ind(int ind1, int ind2, arrayList* list)
{
    if(ind1<0 || ind2<0 || ind1>=list->size || ind2>=list->size){
        printf("Invalid index\n");
        return;
    }
    int temp = list->array[ind1];
    list->array[ind1] = list->array[ind2];
    list->array[ind2] = temp; 
    print(list);
}

void surprise_insert(int item,arrayList* list){
    if(list->surprise_called%2==1){
        insert(item,list);
    }else{
        append(item,list);
    }
    list->surprise_called++;
}

// you can define helper functions you need