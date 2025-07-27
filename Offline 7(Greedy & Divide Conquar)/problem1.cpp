#include<iostream>
#include<vector>
using namespace std;

bool is_possible(vector<int> &task,int k, int mx){
    int ct = 1,i=0,sz = task.size(),sum=0;
    while(i<sz){    
        if(sum+task[i]<=mx){
            sum += task[i];
            i++;
        }else{
            sum = 0;
            ct++;
        }
    }
    if(ct<=k) return true;
    else return false;
}

int main(){
    int n,k;
    cin >> n >> k;
    vector<int> task(n);
    int maxx = INT_MIN,sum = 0;
    
    for(int i=0;i<n;i++){
        cin >> task[i];
        maxx = max(maxx,task[i]);
        sum += task[i];
    }

    if(n<k){
        cout << -1 << "\n";
        return 0;
    }
    int low = maxx,high = sum;
    while(high-low>1){
        int mid = (low+high)/2;
        if(is_possible(task,k,mid)){
            high = mid;
        }else{
            low = mid+1;
        }
    }
    if(is_possible(task,k,low)){
        cout << low << '\n';
    }else{
        cout << high << '\n';
    }
    return 0;
}