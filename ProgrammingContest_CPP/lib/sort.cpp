void BubbleSort(int array[], int N){
    
    int i, j, tmp;
    
    for(i = 0; i < N; i++){
        for(j = N-1; j > i; j--){
            if(array[j-1] > array[j]){
                tmp = array[j-1];
                array[j-1] = array[j];
                array[j] = tmp;
            }
        }
    }
    
    return;
}

void InsertionSort(int array[], int N){
    
    int i, j, v;
    
    for(i = 0; i < N; i++){
        
        v = array[i];
        j = i - 1;
        
        while(j >= 0 && array[j] > v){
            array[j+1] = array[j];
            j--;
        }
        
        array[j+1] = v;
    }
    return;
}

void SelectionSort(int array[], int N){
    
    int i, j, minj, tmp;
    
    for(i = 0; i < N; i++){
        minj = i;
        for(j = i; j < N; j++){
            minj = array[j] < array[minj] ? j : minj;
        }
        if(i != minj){
            tmp = array[minj];
            array[minj] = array[i];
            array[i] = tmp;
        }
    }
    return;
}

/*
 * This function is used for ShellSort.
 */
void InsertionSort_sub(int array[], int N, int g){
    int i,j,v;
    for(i = g; i < N; i++){
        v = array[i];
        j = i - g;
        while( j >= 0 && array[j] > v){
            array[j+g] = array[j];
            j = j - g;
        }
        array[j+g] = v;
    }
    return;
}

/*
 * The gap which is used for sorting is temporalily decided.
 */
void ShellSort(int array[], int N){
    
    int i;
    
    /*
     * array is partially sorted, according to G[i]. 
     */
    int m;
    int G[100];
    for( i = 0; i < 100; ++i ){
        if( i == 0 ) G[i] = N / 2 + 1;
        else G[i] = G[i-1] / 2 - 1;
        if( G[i] < 0 ){
            G[i-1] = 1;
            G[i] = 0;
            m = i;
            break;
        }
    }
    
    for(int i = 0; i < m; i++){
        InsertionSort_sub(array, N, G[i]);
    }
    
    return;
}

/*
 * merge sort
 */
#include <iostream>
#include <cstdio>
using namespace std;

#define MAX 200000
#define SENT 2000000000
typedef long long ll;

int L[MAX / 2 + 2];
int R[MAX / 2 + 2];

ll merge(int A[], int left, int mid, int right){
    
    int i,j,k;
    ll cmp = 0;
    int n1 = mid - left;
    int n2 = right - mid;
    for (i=0; i < n1; i++) L[i] = A[left + i];
    for (i=0; i < n2; i++) R[i] = A[mid + i];
    L[n1] = R[n2] = SENT;
    
    i=j=0;
    for (k = left; k < right; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        }else{
            A[k] = R[j++];
            cmp += n1 - i; //=mid + j - k - 1
        }
    }
    return cmp;
}
/*
 * *A int type array
 * leftは配列Aの最初の要素を指す
 * rightは配列Aの最後の要素+1を指す
 */
ll mergeSort(int A[], int left, int right){
    
    int mid;
    ll cmp = 0;
    
    if( left + 1 < right ) {
        mid = (left + right) / 2;
        cmp += mergeSort(A, left, mid);
        cmp += mergeSort(A, mid, right);
        cmp += merge(A, left, mid, right);
    }
    return cmp;
}

/*
 * *A int type array
 * leftは配列Aの最初の要素を指す
 * rightは配列Aの最後の要素を指す
 */
int partition(int *A, int left, int right){
    
    /*pivotとして一番右端の要素を選ぶ*/
    int pivot = A[right];
    int i = left - 1;
    int j;
    int tmp;
    
    for (j=left; j<right; j++) {
        if (A[j] <= pivot) {
            i = i+1;
            /* A[i] と A[j] を交換 */
            tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    
    /* A[i+1] と A[r] を交換 */
    tmp = A[i+1];
    A[i+1] = A[right];
    A[right] = tmp;
    
    return i+1;   
}

/*
 * *A int type array
 * leftは配列Aの最初の要素を指す
 * rightは配列Aの最後の要素を指す
 */
void quicksort(int * A, int left, int right){
    
    int q;
    if (left < right) {
        q = partition(A, left, right);
        quicksort(A, left, q-1);
        quicksort(A, q+1, right);
    }
    
} 

