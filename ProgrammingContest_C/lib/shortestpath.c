/*
 * 以下、warshallfloyd法のプログラム
 * グラフの[ノードi] - [ノードj]の間の最短距離を求める関数
 * 入力として、weight[NODE_NUM][NODE_NUM]を用いる
 * 自身へのノードの距離（weight[i][i]）は0が入っている。
 * [ノードi] - [ノードj]の間が接続されていない場合、MAX_VALUEが格納される
*/

#define NODE_NUM 100
#define MAX_VALUE 10000000

int weight[NODE_NUM][NODE_NUM];

void WarshallFloyd(){
    int i,j,k;
    
    for (k=0;k < NODE_NUM; k++) {
        for (i=0; i < NODE_NUM; i++) {
            for (j=0; j < NODE_NUM; j++) {
                if (weight[i][j] > weight[i][k] + weight[k][j]) {
                    weight[i][j] = weight[i][k] + weight[k][j];
                }
            }
        }
    }
}

/*
 * 以下、ベルマンフォード法のプログラム
 * 辺のコストが非負の場合に有効なプログラム
 * MAX_E : 辺の数の最大値
 * MAX_V : 頂点の数の最大値
 * INF : 辺のコストが取りえない値
 */
#define MAX_E 10000
#define MAX_V 100
#define INF 100000000

typedef struct edge{
    int from;
    int to;
    int cost;
}edge;


edge es[MAX_E];

int distance[MAX_V];

void bellman_ford(int n, int s, int e) {
    int i, update;
    
    for (i = 0; i < MAX_V; i++) distance[i] = INF;
    distance[s] = 0;
    while (1) {
        update = 0;
        for (i = 0; i < e; i++) {
            edge e = es[i];
            if (distance[e.from] != INF && distance[e.to] > distance[e.from] + e.cost) {
                distance[e.to] = distance[e.from] + e.cost;
                update = 1;
            }
        }
        if (!update) break;
    }
}

/*
 * 以下、Dijkstra法
 */
#include <vector>
#include <queue>
#include <iostream>
#include <stdio.h>

using namespace std;

#define NODE_NUM 10000
#define INF 100000

typedef struct Node {
    //このノードのインデックス
    int idx;
    
    // このノードから伸びるエッジの情報
    vector<int> edges_to;    // 各エッジの接続先のノード番号
    vector<int> edges_cost;  // 各エッジのコスト
    
    // ダイクストラ法のためのデータ
    bool done;  // 確定ノードか否か
    int cost;   // このノードへの現時点で判明している最小コスト
}Node;

Node nodes[NODE_NUM];


struct NodeCompare
{
    bool operator()(const Node &t1, const Node &t2) const
    {
        //コストの昇順に取り出すための不等号。コストの降順の場合は、不等号を逆にする
        return t1.cost > t2.cost;
    }
};

void Dijkstra(int node_num, int start_node){
    
    // 初期化
    for (int i =0 ; i < node_num; i++) {
        nodes[i].done = false;
        nodes[i].cost = INF;
        nodes[i].idx = i;
    }

    //優先度つきキュー。小さい順に取り出す
    priority_queue<Node, vector<Node>, NodeCompare> q;
    
    // スタートノードのコストは0
    nodes[start_node].cost = 0;
    q.push(nodes[start_node]);
    
    // アルゴリズム実行
    while(!q.empty()){
        
        // 確定ノードを取り出す
        Node doneNode = q.top();
        q.pop();
        
        //一度確定したノードについては、２度と扱わない
        if (doneNode.done) continue;
        
        // 確定フラグを立てる
        nodes[doneNode.idx].done = true;
        
        // 接続先ノードの情報を更新する
        for(int i = 0; i < doneNode.edges_to.size(); i++){
            
            int to = doneNode.edges_to[i];
            int cost = doneNode.cost + doneNode.edges_cost[i];
            if( nodes[to].cost == INF || cost < nodes[to].cost){
                nodes[to].cost = cost;
                if(!nodes[to].done){
                    q.push(nodes[to]);
                }
            }
        }
    }
}