#include <iostream>

using namespace std;

/*
 * unsinged long longを用いることで、桁あふれの値が生じるが、これは mod (2<<64)と同じ効果とみなせる
 * Pの値としては、(2<<64)と素であり、かつ値の大きなものを選ぶ
 */
typedef unsigned long long ull;

#define P1 (63533)
#define P2 (100007)

#define MAX (1010)
char str[MAX][MAX];
char pat[MAX][MAX];
ull str_hash[MAX][MAX];
ull tmp[MAX][MAX];
int sh, sw, ph, pw;

void rolling_hash(int height, int width, char character[MAX][MAX])
{

    ull pow = 1;
    ull hash;
    
    for (int i=0; i < pw; i++){
        pow *= P1;
    }
    
    for (int i=0; i < height; i++) {
        hash = 0;
        for (int j = 0; j < pw; j++){
            hash = hash * P1 + character[i][j];
        }
        
        for (int j = 0; j + pw <= width; j++) {
            tmp[i][j] = hash;
            if (j + pw < width) {
                hash = hash * P1 + character[i][j + pw] - pow * character[i][j];
            }
        }
    }
    
    pow = 1;
    for (int i=0; i < ph; i++){
         pow *= P2;
    }
    
    for (int j=0; j + pw <= width; j++) {
        
        hash = 0;
        for (int i = 0; i < ph; i++){
            hash = hash * P2 + tmp[i][j];
        }
        
        for (int i = 0; i + ph <= height; i++) {
            str_hash[i][j] = hash;
            if(i + ph < height){
                hash = hash * P2 + tmp[i + ph][j] - pow * tmp[i][j];
            }
        }
    }
    
    return;
}

int main(){
    
    ull pat_hash;
    char c;
    
    cin >> sh >> sw;
    for(int i = 0; i < sh; i++){
        for (int j = 0; j < sw; j++) {
            cin >> c;
            str[i][j] = c;
        }
    }
    
    cin >> ph >> pw;
    for(int i = 0; i < ph; i++){
        for (int j = 0; j < pw; j++) {
            cin >> c;
            pat[i][j] = c;
        }
    }
    
    rolling_hash(ph, pw, pat);
    pat_hash = str_hash[0][0];
    rolling_hash(sh, sw, str);
    
    if (ph > sh || pw > sw) return 0;
    
    for(int i = 0; i <= sh; i++){
        for (int j = 0; j <= sw; j++) {
            if (pat_hash == str_hash[i][j]) {
                cout << i << " " << j <<endl;
            }
        }
    }
    
    return 0;
}