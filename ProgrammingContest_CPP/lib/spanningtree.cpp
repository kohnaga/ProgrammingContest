/*
 * 以下、Prim法のプログラム（ナイーブな実装）
 * 確定済みの集合Xから最短距離のノードをXに加えていくことで最小全域木を求める
 */

#define NODE_NUM 10001
#define INF INT_MAX

//辺uvのコスト。存在しない場合はINFを格納
int cost[NODE_NUM][NODE_NUM];

//集合Xからの最小のコスト
int mincost[NODE_NUM];

//ノードiがXに含まれるかどうか
bool used[NODE_NUM];

/*
 * n:ノードの総数
 */
int Prim(int n){
    
    for (int i=0; i < n; i++){
        mincost[i] = INF;
        used[i] = false;
    }
    //初期ノード０のコストは０
    mincost[0] = 0;
    int res = 0;
    
    while (true) {
        int v = -1;
        
        //Xに属さないノードのうち、Xからの辺のコストが最小になるノードvを求める
        for (int u = 0; u < n; u++) {
            if (!used[u] && ( v == -1 || mincost[u] < mincost[v])) {
                v = u;
            }
        }
        
        // vが-1のままである場合、既に全てのノードがXに含まれている
        if (v == -1) break;
        
        //頂点vをXに追加
        used[v] = true;
        //辺のコストを加える
        res += mincost[v];
        //確定済みの集合Xからの最短距離について、ノードvから伸びる辺のコストで更新できる場合は更新を行う
        for (int u = 0; u < n; u++){
            mincost[u] = min(mincost[u], cost[v][u]);
        }
    }
    
    return res;
}

/*
 * 以下、Prim法のプログラム(優先度キューを用いた実装)
 * 確定済みの集合Xから最短距離のノードをXに加えていくことで最小全域木を求める
 */

#define MAX_E 10001
#define MAX_V 100001
#define INF INT_MAX

typedef struct edge {
    int from;
    int to;
    int cost;
}edge;

// costを比較する
struct cost_cmp {
    bool operator()(edge x, edge y) const {
        return (x.cost) > (y.cost);
    }
};

vector<edge> G[MAX_V];

//ノードiが既にXに含まれているかどうかを表すフラグ
bool used[MAX_V];

/*
 * start:開始ノード
 */
int Prim(int start) {
    
    int res = 0;
    edge e = {start, start, 0};
    
    //優先度付きキュー。cost昇順にソートされる
    priority_queue<edge, vector<edge>,cost_cmp> que;
    
    //初期化
    que.push(e);
    
    while(!que.empty()) {
        //優先度キューから、確定済み集合Xから最もコストの低い辺を選択する
        edge p = que.top(); que.pop();
        
        //vは次に確定済み集合Xに含むノード
        int v = p.to;
        
        /*
         * vが既に確定済みの集合Xに含まれている場合は、スキップする
         */
        if(used[v]) continue;
        
        //vを集合Xに含めるため確定済みフラグを立てる
        used[v] = true;
        
        res += p.cost;
        
        /*
         * vから伸びるエッジについて、エッジの先toが確定済みノードでない限り
         * 優先度キューにエッジを格納する
         */
        for (int i = 0; i < G[v].size(); i++) {
            int to = G[v][i].to;
            if (!used[to]) que.push(G[v][i]);
        }
    }
    return res;
}



/*
 * 以下、Kruskal法のプログラム(優先度キューを用いた実装)
 * 確定済みの集合Xから最短距離のノードをXに加えていくことで最小全域木を求める
 */

#define MAX_V 10001
#define MAX_E 100001
#define INF INT_MAX

typedef struct edge{
    int from;
    int to;
    int cost;
}edge;

edge es[MAX_E];

// costを比較する関数
bool cmp(const edge& e1, const edge& e2){
    return e1.cost < e2.cost;
}

/*
 * e:辺の総数
 * v:ノードの総数
 */
int Kruskal(int e, int v){
    
    int res = 0;
    
    //辺をコスト昇順にソート
    sort(es, es + e, cmp);
    
    //union-findの初期化
    initialize(v);
    
    for (int i = 0; i< e; i++) {
        edge e = es[i];
        //e.from/e.toがグループに属さないのであれば、同グループとする
        if (!isSame(e.from, e.to)) {
            unite(e.from, e.to);
            res += e.cost;
        }
    }
    
    return res;
}