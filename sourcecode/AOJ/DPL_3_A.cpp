#include <iostream>
#include <cstdio>
using namespace std;

#define MAX 1400

int dp[MAX + 1][MAX + 1];
int A[MAX + 1][MAX + 1];

int main(){
    
    int H, W, ans = 0;
    
    cin >> H >> W;
    
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W ; j++) {
            cin >> A[i][j];
        }
    }
    
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W ; j++) {
            if (A[i][j] == 1) dp[i][j] = 0;
            else{
                if (i-1 >= 0 && j-1 >= 0 && dp[i][j-1] > 0 && dp[i-1][j] > 0) {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                }
                else{
                    dp[i][j] = 1;
                }
            }
        }
    }
    
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W ; j++) {
            ans = max(ans, dp[i][j] * dp[i][j]);
        }
    }
    cout << ans << endl;
    
    return 0;
}