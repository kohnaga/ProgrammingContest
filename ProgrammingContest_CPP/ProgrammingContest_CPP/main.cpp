#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;



int solution(vector<int> &A) {
    
    sort(A.begin(), A.end());
    int N = A.size();
    int ans = 0;
    
    for(int i = 0; i < N-2; i++){
        for(int k = i+2; k < N; k++){
            for(int j = i +1; j < k; j++){
                if(A[i] + A[j] > A[k]){
                    ans += 1;
                }
            }
        }
    }
    
    return ans;
    
}


int main(){

    vector<int> array;
    array.push_back(3);
    array.push_back(3);
    array.push_back(5);
    array.push_back(6);
    
    
    cout << solution(array) << endl;

    
    return 0;
}