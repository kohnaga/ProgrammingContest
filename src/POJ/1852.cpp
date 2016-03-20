#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;



int solution(vector<int> &A, int l) {
    
    sort(A.begin(), A.end());
    int N = A.size();
    int ans = 0;
    
    for(int i = 0; i < N; i++){
        ans = max(ans, min(A[i], l - A[i]));
    }
    cout << ans << " ";
    
    ans = 0;
    
    for(int i = 0; i < N; i++){
        ans = max(ans, max(A[i], l - A[i]));
    }
    cout << ans << endl;
    
    return ans;
    
}


int main(){
    
    int c, l, ant_n, pos;
    scanf("%d", &c);
    
    
    for (int i = 0;i< c ; i++) {
        scanf("%d %d", &l, &ant_n);
        vector<int> ant_array;
        for (int j = 0; j< ant_n; j++) {
            scanf("%d", &pos);
            ant_array.push_back(pos);
        }
        solution(ant_array, l);
    }
    return 0;
}