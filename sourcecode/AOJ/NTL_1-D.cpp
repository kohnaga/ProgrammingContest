#include <iostream>

using namespace std;

typedef long long ll;

ll isPrime(ll num){
    if(num == 2) return 1;
    if(num == 3) return 1;
    if(num == 4) return 0;
    if(num == 5) return 1;
    
    for (ll i = 2; i*i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

ll minfactor(ll n){
    ll i;
    
    if (isPrime(n)) return n;
    
    for (i = 2; i <= n ; i++) {
        if(n % i == 0) break;
    }
    return i;
}


long eulerphi(long n)
{
    long phi = n;
    long m;
    long m0 = 0;
    
    if (n < 1) return(0);
    
    if (n == 1) return(1);
    
    do {
        m = minfactor(n);
        n /= m;
        
        if (m0 != m){
            phi = phi * (m-1) / m;
            m0 = m;
        }
    } while (n != 1);
    
    return(phi);
}


int main(){
    
    ll n, ans = 0;
    
    cin >> n;
    
    ans = eulerphi(n);
    
    cout << ans << endl;
    
    return 0;
}