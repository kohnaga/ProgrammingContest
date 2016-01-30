#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>


/*
 * 文字列検索のためのrolling-hash法
 * String中に含まれる全てのPatternの出現位置を返す
 * 参考書籍：「プログラミングコンテストチャレンジブック」
 *
 */

char String[1000][1000];
char Pattern[1000][1000];




/*
 * unsinged long longを用いることで、桁あふれの値が生じるが、これは mod (2<<64)と同じ効果とみなせる
 * Pの値としては、(2<<64)と素であり、かつ値の大きなものを選ぶ
 */
typedef unsigned long long ull;
#define P (1000000007)

ull pow[1000000];

/*
 * string:検索対象文字列
 * s_num:検索対象文字列の長さ
 * pattern:検索するパターン
 * p_num:検索するパターンの長さ
 */
void rolling_hash(char ** string, int h, int w,  char ** pattern, int r, int c)
{
    int i, j, k , l;
    ull target_hash = 0, pattern_hash = 0;
    
    
    /*
     * target hash値の再計算に用いられる値を予め求めておく
     */
    pow[0] = 1;
    for (i=0; i < h; i++) {
        for (j=0; j < w; j++) {
            pow[i+1]= pow[i]* P;
        }
    }
    
    /*
     * patternのハッシュ値と、stringの初期ハッシュ値を求める
     */
    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            pattern_hash = (pattern[i][j] + pattern_hash * P) ;
        }
    }
    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            target_hash = (string[i][j] + target_hash * P) ;
        }
    }
    
    
    for (i = 0; i + r <= h; i++) {
        
        
        for (k=i; k < r; k++) {
            for (l=0; l < c; l++) {
                target_hash = (string[k][l] + target_hash * P) ;
            }
        }
        
        
        
        for (j=0; j+c <= w; j++) {
            /*
             * hash値が一致すれば同じ文字列とみなせる
             */
            if (target_hash == pattern_hash) {
                printf("%d %d\n", i, j);
            }
            
            
            /*
             * target文字列が１文字後ろにずれるため、合わせてハッシュ値も再計算する
             */
            
            for (k=0; k < r ; k++) {
            target_hash = target_hash + pow[w*i +j + c] * string[i+k][j+c] - pow[w*i + j]*string[i+k][j] ;
            }
            
            
        }
        
    }
    
    return;
}


int main( ){
    
    int i, j, H, W, R,C;
    scanf("%d", &H);
    scanf("%d", &W);
    
    for (i = 0; i < H ; i++) {
        for (j = 0; j < W; j++) {
            scanf("%d", String[i][j]);
        }
    }
    
    scanf("%d", &R);
    scanf("%d", &C);
    
    for (i = 0; i < R ; i++) {
        for (j = 0; j < C; j++) {
            scanf("%d", Pattern[i][j]);
        }
    }
    
    rolling_hash(String, strlen(String), strlen(String[0]) Pattern, strlen(Pattern), strlen(Pattern[0]));
   
    
    return 0;
}