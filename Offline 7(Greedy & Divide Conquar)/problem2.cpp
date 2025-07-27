#include<iostream>
using namespace std;

bool can_seat(int n,int b,int type[],int m){
    int count=0;
    int std_per_bench = n/b;
    for(int i=0;i<b;i++){
        for(int j=0;j<std_per_bench;j++){
            if(type[i*std_per_bench+j]==0){
                bool flag = true;
                if(j>0 && (type[i * std_per_bench+j-1]==2 || type[i * std_per_bench+j-1]==1)) flag = false;
                if(j<(std_per_bench-1) && type[i * std_per_bench+j+1]==2) flag = false;
                if(flag) count++;
            }
        }
    }
    if(count>=m){
        return true;
    }else{
        return false;
    }
}


int main(){
    int n,b;
    cout << "Give number of students and benches: ";
    cin >> n >> b;
    int type[n];
    cout << "Give the types of each seat: ";
    for(int i=0;i<n;i++){ 
        cin >> type[i];
    }
    int m; 
    cout << "Give the number of new students: ";
    cin >> m;
    if(can_seat(n,b,type,m)){
        cout << m << " new students can sit in the vacant seats\n";
    }else{
        cout << m  << " new students can't sit in the vacant seats\n";
    }
}