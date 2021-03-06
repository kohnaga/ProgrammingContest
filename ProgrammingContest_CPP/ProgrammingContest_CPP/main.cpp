#include <iostream>
#include <cstring>

using namespace std;

#define MAX_CITY_NUM 15
#define MAX 100000000

int D[MAX_CITY_NUM][MAX_CITY_NUM];          //都市間の距離を格納
int dp[MAX_CITY_NUM][1 << MAX_CITY_NUM];    //求めた距離をメモ化

/*
 * v:現在地の都市を表す変数
 * b:訪問済みの都市を表すビットフラグ
 * city_num:総都市数を表す変数
 * 外部から最初はtsp(0, 1, N)と呼ぶ
 */
int tsp(int v, int b, int city_num){
    int rtn = MAX;
    //全ての都市を訪問した
    if(b == (1 << city_num) - 1) return D[v][0];

    for (int i = 0; i < city_num; i++) {
        //未訪問の都市を訪問する
        if (!(b & (1 << i)))
        {
            int cost = dp[i][b | (1 << i)] != 0 ? dp[i][b | (1 << i)] : tsp(i, b | (1 << i), city_num);
            dp[i][b | (1 << i)] = cost;
            rtn = min( rtn, D[v][i] + cost);
        }
    }
    
    return rtn;
}



int main(){
    
    int V, E, frm, to, cost, ans;
    
    cin >> V >> E;
    
    //繋がっていない都市間は-1で初期化
    memset(D, -1, sizeof(D));
    for (int i = 0; i < E; i++){
        cin >> frm >> to >> cost;
        D[frm][to] = cost;
    }
    
    ans = tsp(0, 1, V);
    
    if (ans >= MAX) {
        cout << -1 << endl;
    }
    else{
        cout << ans << endl;
    }
    
    return 0;
}