#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

class Heap{
public:
    vector<int> v;
    int max_size;
    int current_size = 0;
    
    int parent(int i){
        return (i - 1) / 2;
    }
    int left(int i){
        return 2 * i + 1;
    }
    int right(int i){
        return 2 * i + 2;
    }
    void max_heapify(int i){
        int l = left(i);
        int r = right(i);
        int largest = i;
        if(l<current_size && v[l]>v[largest]){
            largest = l;
        }
        if(r<current_size && v[r]>v[largest]){
            largest = r;
        }
        if(largest != i){
            swap(v[i], v[largest]);
            max_heapify(largest);
        }
    }
    Heap(int max_size) : v(max_size) {
        this->max_size = max_size;
    }
    Heap(const vector<int>& numbers) : v(numbers) {
        this->max_size = numbers.size();
        this->current_size = numbers.size();
    }
    void build_max_heap(){
        for(int i = (current_size / 2) - 1; i >= 0; i--){
            max_heapify(i);
        }
    }
    void insert(int number){
        if(current_size<max_size){
            v[current_size++] = number;
            int i = current_size - 1;
            while(i>0){
                int p = parent(i);
                if(v[p]<v[i]){
                    swap(v[p], v[i]);
                    i = p;
                } else {
                    break;
                }
            }
        }
    }
    int size() {
        return current_size;
    }  
    int getMax() {
        if(current_size > 0) {
            return v[0];
        }
        throw runtime_error("Heap is empty");
    }
    void deleteKey(){
        if(current_size == 0){
            throw runtime_error("Heap is empty");
        }
        v[0] = v[current_size - 1];
        current_size--;
        max_heapify(0);
    }
    void heapsort(vector<int> &numbers){};
};

void heapsort(vector<int> & numbers){
    Heap temp(numbers);
    temp.build_max_heap();
    int n = numbers.size();
    for(int i=0;i<n-1;i++){
        swap(temp.v[0],temp.v[temp.current_size-1]);
        temp.current_size--;
        temp.max_heapify(0);
    }
    numbers = temp.v;
    reverse(numbers.begin(),numbers.end());
}
