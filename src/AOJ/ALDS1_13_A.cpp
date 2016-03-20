#include <iostream>
#include <cstring>

using namespace std;

#define QUEEN 8
#define PUT 1
#define FREE 0

int canput[QUEEN][QUEEN];
bool row[QUEEN];
bool column[QUEEN];
bool diagonal1[2*QUEEN-1];  //右斜め下方向
bool diagonal2[2*QUEEN-1];  //左斜め下方向

void initialize(){
    
    for (int i = 0; i < QUEEN; i++) {
        for (int j = 0; j < QUEEN; j++) {
            canput[i][j] = FREE;
        }
    }
    for (int i=0; i < QUEEN; i++) {
        row[i] = column[i] = true;
    }
    
    for (int i=0; i < 2*QUEEN-1; i++) {
        diagonal1[i] = diagonal2[i] = true;
    }
    
}

void print(){
    
    for (int i = 0; i < QUEEN; i++) {
        for (int j = 0; j < QUEEN; j++) {
            if (canput[i][j] == PUT) {
                cout << "Q";
            }
            else{
                cout << ".";
            }
        }
        cout << endl;
    }
    return;
}

void backtrack(int y){
    
    if(y == QUEEN){
        print();
        return;
    }
    
    if (column[y] == false) {
        backtrack(y+1);
        return;
    }
    
    for (int x = 0; x < QUEEN; x++) {
        if (
            canput[y][x] != PUT
            &&
            row[x] == true
            &&
            diagonal1[QUEEN - 1 + x - y] == true
            &&
            diagonal2[x + y] == true
            )
        {
            row[x] = column[y] = diagonal1[QUEEN - 1 + x - y] = diagonal2[x + y] = false;
            canput[y][x] = PUT;
            backtrack(y+1);
            row[x] = column[y] = diagonal1[QUEEN - 1 + x - y] = diagonal2[x + y] = true;
            canput[y][x] = FREE;
        }
    }
    return;
    
}


int main(){
    
    int n, x, y;
    
    initialize();
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> y >> x;
        canput[y][x] = PUT;
        row[x] = false;
        column[y] = false;
        diagonal1[QUEEN - 1 + x - y] = false;
        diagonal2[x + y] = false;
    }
    
    backtrack(0);
    
    return 0;
}