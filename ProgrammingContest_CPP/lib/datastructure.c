
/*
 * 単純なQUEUEの実装を以下に示す。
 */
#define MAX_LENGTH  (100)

typedef struct{
    int array[MAX_LENGTH];
    int first;
    int last;
}QUEUE;


void init(QUEUE*);
int enqueu(QUEUE*,int);
int dequeue(QUEUE*,int*);


void init(QUEUE* pQueue)
{
    int i;
    for(i = 0; i < MAX_LENGTH; i++){
        pQueue->array[i] = 0;
    }
    pQueue->first = 0;
    pQueue->last = 0;
}

int enqueue(QUEUE* pQueue,int value)
{
    if((pQueue->last + 1) % MAX_LENGTH == pQueue->first){
        return 0;
    }
    pQueue->array[pQueue->last] = value;
    pQueue->last = (pQueue->last + 1) % MAX_LENGTH;
    return 1;
}


int dequeue(QUEUE* pQueue,int* pValue)
{
    if(pQueue->first == pQueue->last)
    {
        return 0;
    }
    *pValue = pQueue->array[pQueue->first];
    pQueue->first = (pQueue->first+1) % MAX_LENGTH;
    return 1;
    
}


/*
 * 優先度つきキューの実装を以下に示す。
 * ここでは、maxヒープ構造を用いた実装を示している（他に、連想配列、ハッシュで表す方法もある）
 * 要素は1オリジンである
 */
#define PRIORITY_QUEUE_NUM 2000000
int heap[PRIORITY_QUEUE_NUM + 1];
int last_idx;


/*
 * heap中のある要素node_idxについて、この要素を根とするようなサブheapについて、大小関係が成り立つように要素を再構成する
 */
void maxHeapify(int node_idx){
    
    int tmp;
    int largest = node_idx;
    int left_child_idx = 2 * node_idx;
    int right_child_idx = 2 * node_idx + 1;
    
    
    if ( left_child_idx <= last_idx && heap[left_child_idx] > heap[node_idx]) {
        largest = left_child_idx;
    }else{
        largest = node_idx;
    }
    if ( right_child_idx <= last_idx && heap[right_child_idx] > heap[largest]) {
        largest = right_child_idx;
    }
    
    if (largest != node_idx) {
        tmp = heap[largest];
        heap[largest] = heap[node_idx];
        heap[node_idx] = tmp;
        
        maxHeapify(largest);
    }
}

/* heap中最後の要素について、親との大小関係を比較し、親の方が小さい場合には要素の交換を行う
 * 大小関係の条件が成り立つ限りにおいて、根まで繰り返し交換していく
 */
void heapIncreaseKey(int key){
    
    int i = last_idx;
    int tmp;
    
    while( i > 1 && heap[i/2] < heap[i]){
        tmp = heap[i];
        heap[i] = heap[i/2];
        heap[i/2] = tmp;
        i = i/2;
    }
    
}

/*
 * 優先度キュー（heap)に要素を追加する
 */
void enqueue(int key){
    last_idx++;
    heap[last_idx] = key;
    heapIncreaseKey(key);
}

/*
 * 優先度キュー（heap)から要素を取り出す。
 */
void dequeue(){
    
    /* heapの先頭要素を取り出す */
    printf("%d\n", heap[1]);
    heap[1] = heap[last_idx--];
    
    /* 先頭要素を取り出してしまったため、heapを再構成する */
    maxHeapify(1);
}

/*
 * キューが空かどうか調べる
*/
int isEmpty(){
    if (last_idx == 0) {
        return 0;
    }
    else{
        return 1;
    }
}