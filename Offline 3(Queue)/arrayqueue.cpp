#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity
    data = new int[initial_capacity];
    capacity = initial_capacity;
    front_idx =-1;
    rear_idx = -1;
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue
    if(size()==0){
        front_idx = rear_idx = 0;
        data[front_idx] = item;
    }else if(size()==capacity){
        resize(2*capacity);
        rear_idx = (rear_idx+1)%capacity;
        data[rear_idx] = item;
    }else{
        rear_idx = (rear_idx+1)%capacity;
        data[rear_idx] = item;
    }
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the front of the queue
    // TODO: Update front index
    // TODO: Return the dequeued element
    if(size()==0){
        cout << "Queue is empty" << '\n';
        return -1;
    }else{
        int x = data[front_idx];
        if(front_idx==rear_idx){
            front_idx = rear_idx = -1;
        }else{
            front_idx = (front_idx+1)%capacity;
        }
        int n = size();
        if(capacity>=4 && 4*n<capacity){
            resize(capacity/2);
        }
        return x;
    }
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    front_idx = rear_idx = -1;
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    if(front_idx==-1 && rear_idx==-1){
        return 0;
    }
    if(rear_idx>=front_idx) return (rear_idx-front_idx+1);
    return capacity-front_idx+rear_idx+1;
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it
    if(size()==0){
        cout << "Queue is empty\n";
        return -1;
    }else{
        return data[front_idx];
    }
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it
    if(size()==0){
        cout << "Queue is empty" << '\n';
        return -1;
    }else{
        return data[rear_idx];
    }
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    return (size()==0);
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
    string s = "<";
    if(size()==0){
        s+='|';
        return s;
    }
    int i = front_idx;
    while(i!=rear_idx){
        s+= (to_string(data[i])+", ");
        i = (i+1)%capacity;
    }
    s+= (to_string(data[rear_idx])+'|');
    return s;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    // TODO: Update front and rear indices
    int n = size();
    if(n==0){
        front_idx = rear_idx = -1;
        return;
    }
    int *data2 = new int[new_capacity];
    for(int i=0;i<n;i++){
        data2[i] = data[(front_idx+i)%capacity];
    }
    delete[] data;
    data = data2;
    front_idx = 0;
    rear_idx = n-1;
    capacity = new_capacity;
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}