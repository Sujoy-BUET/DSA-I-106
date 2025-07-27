#include<bits/stdc++.h>
using namespace std;

int main(){ 
    string a,b;
    cout << "Sequence 1: ";
    getline(cin,a);
    cout << "Sequence 2: ";
    getline(cin,b);
    
    int match,mismatch,gap;
    cout << "Give match point: ";
    cin >> match;
    cout << "Give mismatch penalty: ";
    cin >> mismatch;
    cout << "Give gap penalty: ";
    cin >> gap;

    int n1 = a.length();
    int n2 = b.length();

    char direction[n1+1][n2+1];
    direction[0][0] = '0';
    for(int i = 1; i <= n1; i++) direction[i][0] = 'U';
    for(int j = 1; j <= n2; j++) direction[0][j] = 'L';

    int score[n1+1][n2+1];
    score[0][0] = 0;
    for(int i=1;i<=n1;i++) score[i][0] = score[i-1][0] + gap;   
    for(int j=1;j<=n2;j++) score[0][j] = score[0][j-1] + gap; 

    for(int i=1;i<=n1;i++){
        for(int j=1;j<=n2;j++){
            if(a[i-1]==b[j-1]){
                score[i][j] = score[i-1][j-1]+match;
                direction[i][j] = 'C';
            }else{
                score[i][j] = score[i-1][j-1]+mismatch;
                direction[i][j] = 'C';
            }
            if(score[i-1][j]+gap>score[i][j]){
                score[i][j] = score[i-1][j] + gap;
                direction[i][j] = 'U';
            }
            if(score[i][j-1]+gap > score[i][j]){
                score[i][j] = score[i][j-1]+gap;
                direction[i][j] = 'L';
            }
        }
    }

    string ans1,ans2;
    int i=n1,j=n2;
    while(i>0 || j>0){
        if(direction[i][j]=='C'){
            ans1.push_back(a[i-1]);
            ans2.push_back(b[j-1]);
            i--,j--;
        }else if(direction[i][j]=='L'){
            ans1.push_back('_');
            ans2.push_back(b[j-1]);
            j--;
        }else if(direction[i][j]=='U'){
            ans1.push_back(a[i-1]);
            ans2.push_back('_');
            i--;
        }
    }
    reverse(ans1.begin(),ans1.end());
    reverse(ans2.begin(),ans2.end());
    cout << endl << score[n1][n2] << "\n";
    cout << ans1 << "\n" << ans2 << "\n";
    return 0;
}