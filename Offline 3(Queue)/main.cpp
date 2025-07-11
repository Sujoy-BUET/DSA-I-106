#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" << endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
    freopen("test_input_1.txt", "r", stdin); // Test Case 1
    // freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;
    vector<int> time(N+1,0);
    bool is_merged = false;
    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic

        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
        int q;
        cin >> q;
        cout << "Operation " << i;
        if(q==1){
            int id,t; cin >> id >> t;
            cout << " (Arrival " << id << ' ' << t << "):"; 
            if(is_merged){
                cout << '\n';
                Q->enqueue(id);
                time[id] = t;
            }else if(Q1->empty()){
                cout << '\n';
                Q1->enqueue(id);
                time[id] = t;
            }else if(Q2->empty()){
                cout << '\n';
                Q2->enqueue(id);
                time[id] = t;
            }else{
                int rd = randomQueue();
                if(rd==1){
                    Q1->enqueue(id);
                    time[id] = t;
                }else{
                    Q2->enqueue(id);
                    time[id] = t;
                }
            }
        }else if(q==2){
            int id,t; cin >> id >> t;
            cout << " (Leave " << id << ' ' << t << "):\n";
            bool found = false;
            if(!Q1->empty()){
                vector<int> v;
                while(!Q1->empty()){
                    v.push_back(Q1->front());
                    if(Q1->front()==id){
                        Q1->dequeue();
                        v.pop_back();
                        found =true;
                        break;
                    }
                    Q1->dequeue();
                }
                int n = v.size();
                for(int j=0;j<n;j++){
                    Q1->enqueue(v[j]);
                }
            }
            if(!found && !Q2->empty()){
                vector<int> v;
                while(!Q2->empty()){
                    v.push_back(Q2->front());
                    if(Q2->front()==id){
                        Q2->dequeue();
                        v.pop_back();
                        found = true;
                        break;
                    }
                    Q2->dequeue();
                }
                int n = v.size();
                for(int j=0;j<n;j++){
                    Q2->enqueue(v[j]);
                }
            }
            if(!found && !Q->empty()){
                vector<int> v;
                while(!Q->empty()){
                    v.push_back(Q->front());
                    if(Q->front()==id){
                        Q->dequeue();
                        v.pop_back();
                        break;
                    }
                    Q->dequeue();
                }
                int n = v.size();
                for(int j=0;j<n;j++){
                    Q->enqueue(v[j]);
                }
            }

        }else if(q==3){
            is_merged = true;
            cout << "(Merge):\n";
            while(!Q1->empty() && !Q2->empty()){
            int id1 = Q1->front();
            int id2 = Q2->front();
            
            if(time[id1] <= time[id2]){  
                Q->enqueue(id1);
                Q1->dequeue();
            }else{
                Q->enqueue(id2);
                Q2->dequeue();
            }
        }
        while(!Q1->empty()){
            Q->enqueue(Q1->front());
            Q1->dequeue();
        }
        while(!Q2->empty()){
            Q->enqueue(Q2->front());
            Q2->dequeue();
        }
        }else if(q==4){
            is_merged = false;
            cout << "(Split):\n";
            bool is_one = true;
            while(!Q->empty()){
                if(is_one){
                    Q1->enqueue(Q->front());
                    is_one = false;
                }else{
                    Q2->enqueue(Q->front());
                    is_one = true;
                }
                Q->dequeue();
            }
            
        }else if(q==5){
            cout << "(Departure): ";
            if(!Q->empty()){
                cout << '\n';
                Q->dequeue();
            }else{
                if(Q1->empty()){
                    cout << '\n';
                    Q2->dequeue();
                }else if(Q2->empty()){
                    cout << '\n';
                    Q1->dequeue();
                }else{
                    int j = randomQueue();
                    if(j==1){
                        Q1->dequeue();
                    }else{
                        Q2->dequeue();
                    }
                }
            }
        }else{
            cout << "Invalid operation\n";
        }
        cout << "Q1: " << Q1->toString() << '\n';
        cout << "Q2: " << Q2->toString() << '\n';
        cout << "Q : " << Q->toString() << '\n';
    }

    return 0;
}