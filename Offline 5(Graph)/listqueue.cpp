#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    // TODO: Initialize current_size to 0
    front_node = rear_node = NULL;
    current_size = 0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    // TODO: Create a new node with the given item
    // TODO: Link the new node to the rear
    // TODO: Update the rear_node
    // TODO: Increment the current size
    if(empty()){
        front_node = rear_node = new Node(item);
        current_size = 1;
    }else{
        Node *n = new Node(item);
        rear_node->next = n;
        rear_node = n;
        current_size++;
    }
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Store the data from the front node
    // TODO: Update the front pointer to the next node
    // TODO: Update the rear pointer if the queue becomes empty
    // TODO: Delete the old front node
    // TODO: Decrement current_size
    // TODO: Return the stored data
    if(empty()){
        cout << "Queue is empty\n";
        return -1;
    }
    if(front_node==rear_node){
        int x = front_node->data;
        delete front_node;
        front_node = NULL;
        rear_node = NULL;
        current_size = 0;
        return x;
    }
    Node *n = front_node;
    front_node = front_node->next;
    int x = n->data;
    delete n;
    current_size--;
    return x;
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    // TODO: Reset front and rear pointer
    // TODO: Reset current_size to 0
    while(!empty()) dequeue();
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the front node without removing it
    if(empty()){
        cout << "Queue is empty\n";
        return -1;
    }
    return front_node->data;
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the back node without removing it
    if(empty()){
        cout << "Queue is empty\n";
        return -1;
    }
    return rear_node->data;
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr
    return (front_node == NULL);
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front
    string s = "<";
    if(empty()){
        s += '|';
        return s;
    }
    Node *n = front_node;
    while(n!=rear_node){
        s += (to_string(n->data)+", ");
        n = n->next;
    }
    s += (to_string(n->data)+'|');
    return s;
}
