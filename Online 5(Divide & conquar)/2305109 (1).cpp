#include<vector>
#include<stdlib.h>
#include<iostream>
using namespace std;

int find_max_diff(vector<int> &v,int left,int right){
    if(left>=right) return -1;
    int mid = left+(right-left)/2;
    int l = find_max_diff(v,left,mid);
    int r = find_max_diff(v,mid+1,right);
    int minn = INT_MAX,maxx = INT_MIN;
    for(int i= left;i<=mid;i++){
        minn = min(minn,v[i]);
    }
    for(int j=mid+1;j<=right;j++){
        maxx = max(maxx,v[j]);
    }
    int ans = max(r,l);
    ans = max(ans,maxx-minn);
    return ans;
}

int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin >> v[i];
    }
    cout << find_max_diff(v,0,n-1) << "\n";
}