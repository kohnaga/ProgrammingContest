#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define NUM 3

typedef struct STATUS{
    int num;                    //何手目かを保持する変数
    int board[NUM * NUM];       //盤面の状態
    int x,y;                    //盤面上0の値を保持する座標
}STATUS;

bool checked[9*8*7*6*5*4*3*2*1];

/* 盤面の状態を番号に変換 */
int change_number( int *board )
{
    int work[NUM*NUM];
    static int fact_table[NUM*NUM] = {
        40320, 5040, 720, 120, 24, 6, 2, 1, 0,
    };
    int j, k, value = 0;
    memcpy( work, board, sizeof(int)*NUM*NUM );
    for( j = 0; j < NUM*NUM - 1; j++ ){
        value += fact_table[j] * work[j];
        for( k = j + 1; k < NUM*NUM; k++ ){
            if( work[j] < work[k] ) work[k]--;
        }
    }
    return value;
}


int search(STATUS in){
    
    int x = 0, y = 0;
    int chk_num,goal_num;
    
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    int goal[9] = {1,2,3,4,5,6,7,8,0};
    STATUS out;
    goal_num = change_number(goal);
    
    //盤面の状態を保存するためのキュー
    queue<STATUS> qu;
    qu.push(in);
    
    //キューが空になるまで続ける
    while (!qu.empty()) {
        
        in = qu.front();
        qu.pop();
        chk_num = change_number(in.board);
        if (goal_num == chk_num){
            return in.num;
        }
        else{
            checked[chk_num] = true;
        }
        for (int i = 0; i < 4; i++) {
            //盤面上0の値を保持する座標をx,yに読み込む
            x = in.x;
            y = in.y;
            if (x + dx[i] >=0 && x+dx[i] < NUM && y+dy[i] >=0 && y+dy[i] < NUM) {
                memcpy(&out, &in, sizeof(STATUS));
                swap(out.board[NUM*y + x], out.board[NUM*(y+dy[i]) + x + dx[i]] );
                
                chk_num = change_number(out.board);
                if (checked[chk_num] == true){
                    continue;
                }
                else{
                    out.num++;
                    out.x = x + dx[i];
                    out.y = y + dy[i];
                    qu.push(out);
                }
            }
        }
    }
    
    //盤面がgoalに到達しなかった場合は-1を返す
    return -1;
}


int main(){
    
    int val, ans;
    
    STATUS init;
    init.num = 0;
    
    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < NUM; j++) {
            cin >> val;
            init.board[i*NUM +j] = val;
            if (val == 0){
                init.x = j;
                init.y = i;
            }
        }
    }
    
    ans = search(init);
    
    cout << ans << endl;
    
    return 0;
}