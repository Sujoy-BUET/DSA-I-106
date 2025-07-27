#include<bits/stdc++.h>
using namespace std;

int main(){
    string a,b;
    cout << "First sequence: ";
    getline(cin,a);
    cout << "Second sequence: ";
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

    if(n1==0 or n2==0){
        cout << endl << endl << 0 << endl;
        return 0;
    }

    char direction[n1+1][n2+1];
    for(int i = 1; i <= n1; i++) direction[i][0] = 'U';
    for(int j = 1; j <= n2; j++) direction[0][j] = 'L';
    
    int score[n1+1][n2+1];
    for(int i=0;i<=n1;i++) score[i][0] = 0;
    for(int j=0;j<=n2;j++) score[0][j] = 0; 

    int max_score = INT_MIN,m=0,n=0;

    for(int i=1;i<=n1;i++){
        for(int j=1;j<=n2;j++){

            if(a[i-1]==b[j-1]){
                score[i][j] = max(score[i-1][j-1]+match,0);
                direction[i][j] = 'C';
            }else{ 
                score[i][j] = max(score[i-1][j-1]+mismatch,0);
                direction[i][j] = 'C';
            }
            if(score[i-1][j]+gap>score[i][j]){
                score[i][j] = max(score[i-1][j] + gap,0);
                direction[i][j] = 'U';
            }
            if(score[i][j-1]+gap > score[i][j]){
                score[i][j] = max(score[i][j-1]+gap,0);
                direction[i][j] = 'L';
            }

            if(score[i][j]>max_score){
                max_score = score[i][j];
                m = i;
                n = j;
            }
        } 
    }
   
    if(max_score==0){
        cout << "No match found" << '\n';
        return 0;
    }

    string ans1,ans2;
    int i = m,j = n;

    while(score[i][j]!=0){
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
    
    cout << ans1 << "\n" << ans2 << "\n";
    cout << max_score << "\n";
    return 0;
}