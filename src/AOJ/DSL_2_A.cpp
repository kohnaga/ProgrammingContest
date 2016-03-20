#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <climits>

using namespace std;


#define NUM 100001
#define RMQ_NUM 500
#define RMQ_WIDTH 200

int data[NUM];
//幅200で最小値を格納しておく
int RMQ[RMQ_NUM];

int find(int left, int right){
    int left_idx = left / RMQ_WIDTH;
    int right_idx = right / RMQ_WIDTH;
    int ans = INT_MAX;
    
    if (left_idx == right_idx) {
        for (int i = left; i <= right; i++) {
            ans = min(ans, data[i]);
        }
        return ans;
    }
    
    for (int i = left; i < ( (left_idx + 1) * RMQ_WIDTH); i++) {
        ans = min(ans, data[i]);
    }
    for (int i = (right_idx * RMQ_WIDTH); i <= right ; i++) {
        ans = min(ans, data[i]);
    }
    
    for (int i = left_idx + 1; i < right_idx; i++) {
        ans = min(ans, RMQ[i]);
    }
    
    return ans;
}

void update(int idx, int val){
    int before = data[idx];
    data[idx] = val;
    int rmq_idx = idx/RMQ_WIDTH;
    
    //最小値を更新するケース
    if(RMQ[rmq_idx] == before){
        int val = INT_MAX;
        for (int i = 0; i <  RMQ_WIDTH; i++) {
            val = min(val, data[rmq_idx * RMQ_WIDTH + i]);
        }
        RMQ[rmq_idx] = val;
    }
    return;
}



int main(){
    
    int n,q, x, y, com;
    scanf("%d", &n);
    scanf("%d", &q);
    fill(data, data + NUM, INT_MAX);
    fill(RMQ, RMQ + RMQ_NUM, INT_MAX);
    
    for (int i = 0;i< q ; i++) {
        scanf("%d %d %d", &com, &x, &y);
        //update
        if (com == 0) {
            update(x, y);
        }
        //find
        else{
            cout << find(x, y) << endl;
        }
    }
    return 0;
}