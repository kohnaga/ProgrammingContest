/*
 * 文字列検索のKMP法
 * String中に含まれるPatternの出現位置を返す
 * !!最初の出現位置を返すと終了することに注意。続けて検索は行わない!!
 * 参考サイト：http://www.algolism.iinaa.net/80/83.htm#L3
 *
 */

char String[1000001];
char Pattern[10001];


/*
 * string:検索対象文字列
 * s_num:検索たいしょう文字列の長さ
 * pattern:検索するパターン
 * p_num:検索するパターンの長さ
 */
void KMP(char * string, int s_num, char * pattern, int p_num)
{
    int p1 = 1;
    int p2 = 0;
    
    /*
     * 検索対象文字列に含まれる文字の種類に応じて長さを変更する
     */
    int skip[256];

    skip[p1]=0;
    
    /*
     * Pattern文字列から、テーブルskipを作成する
     */
    while (p1 < p_num)
    {
        if(pattern[p1] == pattern[p2]){
            skip[++p1] = ++p2;
        }
        else if(p2 == 0){
           skip[++p1] = p2;
        }
        else{
           p2 = skip[p2];
        }
    }
    
    p1 = 0;
    p2 = 0;
    
    /*
     * テーブルskipを利用して、文字列検索を行う
     */
    while(p1 < s_num && p2 < p_num)
    {
        if(string[p1] == pattern[p2])
        {
            p1++;
            p2++;
        }else if(p2 == 0){
            p1++;
        }else{
            p2 = skip[p2];
        };
    }
    
    if(p2 == p_num){
        printf("%d\n", (p1 - p2));
    }
    
    return;
}


/******************************************************************************************/

/*
 * 文字列検索のBM法
 * String中に含まれるPatternの出現位置を全て返す
 * 参考サイト：http://tokyo-ct.net/usr/kosaka/for_students/jissen1/akiyojissen1/kougi17.html
 *
 */

char String[1000001];
char Pattern[10001];


/*
 * string:検索対象文字列
 * s_num:検索対象文字列の長さ
 * pattern:検索するパターン
 * p_num:検索するパターンの長さ
 */
void BM(char * string, int s_num, char * pattern, int p_num)
{
    int i,j;
    int p1 = 1;
    int p2 = 0;
    
    /*
     * stringの注目点(i)をずらすために、用いられるテーブル
     * 検索対象文字列に含まれる文字の種類に応じて長さを変更する
     */
    int skip[256];
    
    skip[p1]=0;
    
    /*
     * Pattern文字列から、テーブルskipを作成する
     * pattern文字列の最後の文字(i == p_num - 1)については、作成しないことに注意！！
     */
    for( i = 0; i < 256; i++ ){
        skip[i] = p_num;
    }
    for( i = 0; i < p_num - 1; i++ ){
        skip[pattern[i]] = p_num - i - 1;
    }
    
    p1 = 0;
    p2 = 0;
    
    /*
     * テーブルskipを利用して、文字列検索を行う
     */
    i = p_num - 1;
    while( i < s_num ) {
        
        j = p_num - 1;
        
        while( string[i] == pattern[j] ) {
            
            /* 全ての文字が一致た場合、一致した位置を返す */
            if (j == 0) {
                printf("%d\n", i);
                break;
            }
            /* string/patternの位置を１文字戻す*/
            i--;
            j--;
        }
        /* 
         * stringの注目点(i)を，不一致になった文字に応じた分量だけずらす
         * 配列skipのみをもとにiを更新すると，パターンが前に戻ってしまうことがあります
         * 不一致が起った文字がパターンの注目点よりも末尾寄りにあるときに，
         * このような 現象が発生します。
         * これを避けるために，このような場合には，パターンを現在の位置よりも
         * 1つだけずらすことにします。
         * 従って、skip[text[i]]とパターンを1つずらすための移動量（patn_len - j），
         * 移動量が多い方にテキストの注目点を移動します
         *
         * 例えば、下の例では注目点iの値dを元にiをskip[d](=1)のみずらすと、
         * 無限ループを起こしてしまう。
         * 従って、この場合は(patn_len - j）(=4)分ずらすようにする
         *
         *----------------------------------
         *           注目点j
         *             ↓
         * pattern: [a b c d e]
         * string : [* d c d e * * *]
         *             ↑
         *           注目点i
         *----------------------------------
         *
         */
        if
        (
           skip[string[i]] < (p_num - j)
        )
        {
            i += (p_num - j);
        }
        else
        {
            i += skip[string[i]];
        }
    }
    
    return;
}

/*
 * 文字列検索のためのrolling-hash法
 * String中に含まれる全てのPatternの出現位置を返す
 * 参考書籍：「プログラミングコンテストチャレンジブック」
 *
 */

char String[1000001];
char Pattern[10001];


/*
 * unsinged long longを用いることで、桁あふれの値が生じるが、これは mod (2<<64)と同じ効果とみなせる
 * Pの値としては、(2<<64)と素であり、かつ値の大きなものを選ぶ
 */
typedef unsigned long long ull;
#define P (1000000007)

/*
 * string:検索対象文字列
 * s_num:検索対象文字列の長さ
 * pattern:検索するパターン
 * p_num:検索するパターンの長さ
 */
void rolling_hash(char * string, int s_num, char * pattern, int p_num)
{
    int i;
    ull pow = 1, target_hash = 0, pattern_hash = 0;
    
    /*
     * target hash値の再計算に用いられる値を予め求めておく
     */
    for (i=0; i < p_num; i++) {
        pow *= P;
    }
    
    /*
     * patternのハッシュ値と、stringの初期ハッシュ値を求める
     */
    for (i=0; i < p_num; i++) {
        pattern_hash = (pattern[i] + pattern_hash * P) ;
    }
    for (i=0; i < p_num; i++) {
        target_hash = (string[i] + target_hash * P) ;
    }
    
    for (i = 0; i < s_num; i++) {
        /*
         * hash値が一致すれば同じ文字列とみなせる
         */
        if (target_hash == pattern_hash) {
            printf("%d\n", i);
        }
        /*
         * target文字列が１文字後ろにずれるため、合わせてハッシュ値も再計算する
         */
        target_hash = target_hash * P - pow * string[i] + string[i + p_num] ;
    }
    
    return;
}