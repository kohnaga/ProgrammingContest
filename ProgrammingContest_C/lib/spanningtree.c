
#define NODE_NUM 100
/*
 * 自分自身のノードへの距離 or 繋がっていないノード間の距離には、MAX_VALUEを格納しておく
 */
#define MAX_VALUE 10000000

int weight[NODE_NUM][NODE_NUM];
int visited[NODE_NUM];
int low_cost[NODE_NUM];
int predecessor[NODE_NUM];


/*
 * グラフのノードvertex_idxを開始点として、最小全域木を求めるPrim法
 * グラフ中のノードの総数はvertex_num
 * 隣接行列weightを入力として最小全域木を構成する
 * 配列predecessorに、各ノードの最隣接ノードのidxが格納される
 */
void Prim(int vertex_idx, int vertex_num){
    
    int i, j;
    
    /*
     * minに,　既に構成済みの全域木から最小のコストで拡張可能な次のノードへの距離/重みを、
     * kに,　既に構成済みの全域木から最小のコストで拡張可能な次のノードのidxを、それぞれ格納する
     */
    int k, min;
    
    /*
     * ノードvertex_idxが開始ノードであるため、フラグを立てておく
     */
    visited[vertex_idx] = 1;
    
    /*
     * 最初に、開始ノードvertex_idxからグラフ中の各ノードへの距離/重みをlow_cost配列に格納する
     */
    for (i = 0; i < vertex_num ; i++) {
        low_cost[i] = weight[vertex_idx][i];
    }
    
    /*
     * predecessor配列には、最小全域木が構成された場合の、各ノードからの最近接ノードのidxを格納される
     * 初期値として、vertex_idxを格納する
     */
    for (i = 0; i < vertex_num ; i++) {
        predecessor[i] = vertex_idx;
    }
    
    
    for (i = 1; i< vertex_num; i++) {
        min = low_cost[vertex_idx];
        k = vertex_idx;
        
        /*
         * minに,　既に構成済みの全域木から最小のコストで拡張可能な次のノードへの距離/重みを、
         * kに,　既に構成済みの全域木から最小のコストで拡張可能な次のノードのidxを、それぞれ格納する
         */
        for (j = 0; j < vertex_num; j++) {
            if (!visited[j] && min > low_cost[j]) {
                min = low_cost[j];
                k = j;
            }
        }
        
        /*
         * ノードkの値を次に全域木に組み込むため、組み込み済みのフラグを立てておく
         */
        visited[k] = 1;
    
        /*
         * 新たに加えられたノードkからの距離/重みに寄って、low_cost配列が更新可能な場合は、更新を行う
         * また、併せてpredecessor配列も更新を行う
         */
        for (j = 1; j < vertex_num; j++) {
            if (!visited[j]  && low_cost[j] > weight[k][j]) {
                low_cost[j] = weight[k][j];
                predecessor[j] = k;
            }
        }
    }
}


/*
 * 最小全域木を求めるための、Kruskal法
 * コストの低いEDGEを優先度キューから取り出し、追加可能かどうかをunion-findのisSame関数で同じグループかどうかを判定し、同じであれば追加することで、最小全域木を構成していく
*/

typedef struct EDGE{
    int frm;
    int to;
    int weight;
}EDGE;

int Kruskal(){
    EDGE A;
    int ans = 0;
    int tmp;
	
	/*
	* isEmpty()は優先度つきキューに値が格納されているかどうかを調べる関数
	* dequeue()は優先度つきキューからからEDGE構造体のインスタンスを取り出す関数
	* isSame(from, to)はunion-findのインスタンスにおいて、同じルートであるかどうかを調べる関数
	* unite()は別グループのunion-findをマージするための関数
	*/
    while ( isEmpty() ) {
        A = dequeue();
        if ( !isSame(A.frm, A.to) ){
            unite(A.frm, A.to);
            ans = A.weight;
        }
    }
    
    return ans;
}