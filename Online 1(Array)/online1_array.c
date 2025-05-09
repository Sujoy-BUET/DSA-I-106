#include<stdio.h>
const int inf = 1e9+7;

int max(int a,int b){
    if(a>b) return a;
    return b;
}

int main(){
    int n;
    scanf("%d",&n);
    int ara[n];
    for(int i=0;i<n;i++) scanf("%d",&ara[i]);
    int maxx[n];
    for(int i=n-1;i>=0;i--) maxx[i] = -inf;
    maxx[n-1] = ara[n-1];
    for(int i=n-2;i>=0;i--){
        maxx[i]= max(maxx[i+1],ara[i]);
    } 
    for(int i=0;i<n;i++){
        if(ara[i]>=maxx[i]){
            printf("%d ",ara[i]);
        }
    }
}
