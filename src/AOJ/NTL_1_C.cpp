#include <iostream>

using namespace std;

/*
 * great common divider
 */
int gcd(int x, int y){
    int tmp;
    
    if(y == 0) return x;
    
    if(x < y){
        tmp = y;
        y = x;
        x = tmp;
    }
    
    return gcd(y, x%y);
    
}

/*
 * lowest common multiplyer
 */
int lcm(int x, int y){
    if(x == 0 || y == 0) return 0;
    
    return x*y / gcd(x, y);
}

int main(){
    
    int n, ans = 1;
    int A[10];
    cin >> n;
    
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) ans = lcm(ans, A[i]);
    
    cout << ans << endl;
    
    return 0;
}