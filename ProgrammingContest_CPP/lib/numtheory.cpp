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


/*
 * If true, return not 0. If not true(=false), return 0.
 */
int isPrime(int num){
    if(num == 2) return 1;
    if(num == 3) return 1;
    if(num == 4) return 0;
    if(num == 5) return 1;
    
    for (int i = 2; i*i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

/*
 * Return the n-th fibonacchi number
 */
int fib(int n){
   
    int ans = 0;
    int fib_1, fib_2;
    fib_1 = 1;
    fib_2 = 1;
    
    if(n == 0 || n == 1){
        return 1;
    }
    
    for(int i = 2; i <= n; i++){
        ans = fib_1 + fib_2;
        fib_2 = fib_1;
        fib_1 = ans;
    }
    
    return ans;
}


/*
 * Return the n-th power of x
 */
typedef long long ll;
const ll mod = 1000000007;

ll power(ll x,ll n){
    if(!n) return 1;
    ll res = power(x * x % mod , n / 2);
    if(n & 1) res = res * x % mod;
    return res;
}

ll minfactor(ll n){
    ll i;
    
    if (isPrime(n)) return n;
    
    for (i = 2; i <= n ; i++) {
        if(n % i == 0) break;
    }
    return i;
}

/*
 eulerphi
 与えられた自然数 n に対してオイラーのφ関数の値 φ(n) を求める。
 */
long eulerphi(long n)
{
    long phi = n;
    long m;
    long m0 = 0;
    
    // n が 0 か負数の場合値は定義されないが便宜的に 0 を返す
    if (n < 1) return(0);
    
    // φ(1) = 1 とする
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