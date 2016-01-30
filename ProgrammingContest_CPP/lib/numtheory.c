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