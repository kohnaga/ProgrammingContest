/*
 * 以下、warshallfloyd法のプログラム
 * グラフの[ノードi] - [ノードj]の間の最短距離を求める関数
 * 入力として、cost[NODE_NUM][NODE_NUM]を用いる
 * 自身へのノードの距離（cost[i][i]）は0が入っている。
 * [ノードi] - [ノードj]の間が接続されていない場合、INFが格納される
 */
#define NODE_NUM 101
#define INF INT_MAX
int cost[NODE_NUM][NODE_NUM];

/*
 * 負のループが発生している場合は、-1を返す
 * n:ノードの総数
 */
int WarshallFloyd(int n){
    
    for(int k=0; k < n; k++) {
        for(int i=0; i < n; i++) {
            for(int j=0; j < n; j++) {
                if(cost[i][k] != INF && cost[k][j] != INF)
                    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
            }
        }
    }
    
    //自身へのコストが0未満になるような場合、負のループが発生している
    for(int v = 0; v < n; v++){
        if(cost[v][v] < 0) return -1;
    }
    
    return 1;
}

/*
 * 以下、ベルマンフォード法のプログラム
 * 辺のコストが非負の場合に有効なプログラム
 * MAX_E : 辺の数の最大値
 * MAX_V : 頂点の数の最大値
 * INF : 辺のコストが取りえない値
 */
#define MAX_E 2001
#define MAX_V 1001
#define INF INT_MAX

typedef struct edge{
    int from;
    int to;
    int cost;
}edge;

edge es[MAX_E];
int cost[MAX_V];

/*
 * negativeループが存在する場合には-1を返す
 * n:ノードの総数
 * s:開始ノード
 * e:エッジの総数
 */
int BellmanFord(int n, int s, int e) {
    //jはnegative loopを検出するために用いられる
    int j = 0, update;
    
    //開始ノードのコストは0。その他のノードは無限大
    fill(cost, cost + MAX_V, INF);
    cost[s] = 0;
    
    while (1) {
        update = 0;
        for (int i = 0; i < e; i++) {
            edge e = es[i];
            if
            (
                cost[e.from] != INF
                &&
                cost[e.to] > cost[e.from] + e.cost
            )
            {
                cost[e.to] = cost[e.from] + e.cost;
                update = 1;
            }
        }
        
        // updateの更新がない場合には、これ以上cost値の更新はないため、処理を中断する
        if (!update) return 1;
        
        /*
         * jがnを超える場合（n回目のループ以降もcostの更新がある場合）は、
         * negative loopが存在する
         */
        if (j > n) return -1;
        j++;
    }
    return 1;
}

/*
 * 以下、Dijkstra法
 */
#define MAX_E 500001
#define MAX_V 100001
#define INF INT_MAX

struct edge {
    int to;
    int cost;
};
vector<edge> G[MAX_V];

/*
 * 第一引数:出発点から第二引数で表されるノードまでのcost
 * 第二引数:到着ノード
 */
typedef pair<int, int> P;

//出発ノードから各ノードへの最小costが格納される
int cost[MAX_V];

/*
* start:開始ノード
 */
void Dijkstra(int start) {
    
    //優先度付きキュー。cost昇順にソートされる
    priority_queue<P, vector<P>, greater<P> > que;
    
    //初期化
    fill(cost, cost + MAX_V, INF);
    cost[start] = 0;
    que.push(P(0, start));
    
    while(!que.empty()) {
        P p = que.top(); que.pop();
        
        //vは到着ノード
        int v = p.second;
        
        /*
         * 現在までに求められているvまでの最小値と、startからvまでのコストを比較する
         * この条件が成り立つ場合、vは既に訪問済みの確定ノードである
         */
        if (cost[v] < p.first) continue;
        
        /*
         * vから伸びる先のノードe.toについて、
         * 現在までに求められている最小値が更新可能であれば更新を行い、
         * 更新可能であれば、e.toからさらに先のノードを用いてcostを更新するため、
         * 優先度キューにノードe.toを格納する
         */
        for (int i = 0; i < G[v].size(); i++) {
            edge e = G[v][i];
            if (cost[e.to] > cost[v] + e.cost) {
                cost[e.to] = cost[v] + e.cost;
                que.push(P(cost[e.to], e.to));
            }
        }
    }
}

/*
 * 巡回セールスマン
 */
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