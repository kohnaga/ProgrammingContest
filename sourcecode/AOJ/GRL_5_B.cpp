#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <numeric>

using namespace std;

#define NUM 10001


typedef struct EDGE{
    int from;
    int to;
    int cost;
}EDGE;

typedef struct STATUS{
    int cur_node;
    int total_cost;
}STATUS;

vector<EDGE> mtx[NUM];

int dis[NUM];

int get_height(int frm){
    
    int ans = 0;
    queue<STATUS> qu;
    bool checked[NUM];
    
    fill(checked, checked + NUM, false);
    
    STATUS in = {frm, 0};
    qu.push(in);
    
    while (!qu.empty()) {
        
        STATUS out = qu.front();
        qu.pop();
        
        int cur_node = out.cur_node;
        int cur_cost = out.total_cost;
        
        for (int i = 0; i < mtx[cur_node].size(); i++) {
            int next_node = mtx[cur_node][i].to;
            if (checked[next_node] == false) {
                int next_total_cost = cur_cost + mtx[cur_node][i].cost;
                ans = max(ans, next_total_cost);
                STATUS next = {next_node, next_total_cost};
                qu.push(next);
            }
        }
        checked[cur_node] = true;
    }
    
    return ans;
}

int main(){
    
    int n, frm, to, cost;
    
    cin >> n;
    
    for (int i = 0; i < n-1; i++) {
        cin >> frm >> to >> cost;
        
        EDGE tmp1 = {frm, to, cost};
        mtx[frm].push_back(tmp1);
        EDGE tmp2 = {to, frm, cost};
        mtx[to].push_back(tmp2);
    }
    
    for (int i = 0 ; i < n; i++) {
        dis[i] = get_height(i);
        cout << dis[i] << endl;
    }
    
    return 0;
}