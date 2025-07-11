#include "stack.h"
#include "queue.h"
#include<iostream>
using namespace std;

bool isPlaindrome(Queue *q){
    int n = q->size();
    if(n==1) return true;
    Stack *st=new ListStack();
    for(int i=0;i<n/2;i++){
        st->push(q->dequeue());
    }
    if(n%2==1) q->dequeue();
    while(!st->empty()){
        int x = st->pop();
        if(x!=q->dequeue()) return false;
    }
    return true;
}

int main(){
    Queue *q=new ListQueue;
    cout << "Enter the number of elements in the queue: ";
    int n; cin >> n;
    while(n--){
        int x; cin >> x;
        q->enqueue(x);
    }
    if(isPlaindrome(q)){
        cout << "Queue is palindrome!\n";
    }else{
        cout << "Queue isn't palindrome!\n";
    }

}