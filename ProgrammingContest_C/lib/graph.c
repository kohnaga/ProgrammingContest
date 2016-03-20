void maxHeapify(int *A, int N, int node_idx){
    
    int tmp;
    int largest = node_idx;
    int left_child_idx = 2 * node_idx + 1;
    int right_child_idx = 2 * node_idx + 2;
    
    // 左の子、自分、右の子で値が最大のノードを選ぶ
    if ( left_child_idx < N && A[left_child_idx] > A[node_idx]) {
        largest = left_child_idx;
    }else{
        largest = node_idx;
    }
    if ( right_child_idx < N && A[right_child_idx] > A[largest]) {
        largest = right_child_idx;
    }
    
    // 親node_idxより、子の方が値が大きい場合
    if (largest != node_idx) {
        tmp = A[largest];
        A[largest] = A[node_idx];
        A[node_idx] = tmp;
        
        // 再帰的に呼び出し
        maxHeapify(A, N, largest);
    }
}

/*
 * maxヒープを構成する関数。
 * minヒープを構成する場合は、maxHeapify関数の大小条件を変更する
 */
void buildMaxHeap(int *A, int N){
    int i;
    
    for (i = N/2; i >= 0; i--) {
        maxHeapify(A, N, i);
    }
}







/*
 * union-findの実装を以下に示す。
 */
#define ELEMENT_NUM 10000

typedef struct UF{
    int parent;
}UF;

UF uf[ELEMENT_NUM + 1];

/*
 * 自身のidxをparentとして初期値を設定する
 */
void initialize(int num){
    int i ;
    
    for (i=1; i <= num; i++) {
        uf[i].parent = i;
    }
}
/*
 * 自身が属するグループの根を返す
 */
int find(int a){

    if (a == uf[a].parent) {
        return a;
    }
    
    return uf[a].parent = find(uf[a].parent);
}

int isSame(int a, int b){
    
    if (find(a) == find(b)) {
        return 1;
    }
    else{
        return 0;
    }
}

void unite(int a, int b){
   a = find(a);
   b = find(b);
    
    if (a == b) {
        return;
    }
    
    uf[b].parent = a;
    
}


