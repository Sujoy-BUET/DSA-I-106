#include "stack.h"
#include <iostream>
#include<climits>

// Constructor implementation
ListStack::ListStack() {
    // TODO: Initialize head to nullptr
    // TODO: Initialize current_size to 0
    head = nullptr;
    current_size = 0;
}

// Destructor implementation
ListStack::~ListStack() {
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method   
    clear();
}

// Push implementation
void ListStack::push(int item) {
    // TODO: Create a new node with the given item
    // TODO: Make the new node point to the current head
    // TODO: Update head to point to the new node
    // TODO: Increment current_size
    Node *h = new Node(item);
    h->next = head;
    head = h;
    current_size++;
}

// Pop implementation
int ListStack::pop() {
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Store the data from the head node
    // TODO: Update head to point to the next node
    // TODO: Delete the old head node
    // TODO: Decrement current_size
    // TODO: Return the stored data
    if(!empty()){
        Node *h = head;
        int data = head->data;
        head = head->next;
        delete h;
        current_size--;
        return data;
    }else{
        return INT_MIN;
    }
}

// Clear implementation
void ListStack::clear() {
    // TODO: Traverse the linked list, deleting each node
    // TODO: Reset head to nullptr
    // TODO: Reset current_size to 0
    Node *t = head;
    while(t!=nullptr){
        Node *prev = t;
        t = t->next;
        delete prev;
    }
    head = nullptr;
    current_size = 0;
}

// Size implementation
int ListStack::size() const {
    // TODO: Return the current size (current_size)
    return current_size;
}

// Top implementation
int ListStack::top() const {
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Return the data from the head node without removing it
    if(!empty()){
        return head->data;
    }else{
        return INT_MIN;
    }
}

// Empty implementation
bool ListStack::empty() const {
    // TODO: Return whether head is nullptr
    return head==nullptr;
}

// Print implementation
void ListStack::print() const {
    // Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    Node *t = head;
    std::cout << "|";
    while (t != nullptr) {
        std::cout << t->data;
        if (t->next != nullptr) {
            std::cout << ", ";
        }
        t = t->next;
    }
    std::cout << ">" << std::endl;
}