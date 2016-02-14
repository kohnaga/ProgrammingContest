#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;

ll power(ll x,ll n){
    if(!n) return 1;
    ll res = power(x * x % mod , n / 2);
    if(n & 1) res = res * x % mod;
    return res;
}

int main(){
    
    int m , n;
    long ans = 0;
    
    cin >> m >> n;
    
    ans = power(m, n);
    
    printf("%ld\n", ans);
    
    return 0;
}