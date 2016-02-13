#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <climits>

using namespace std;

#define EPS (1e-10)
#define equals(a, b) (fabs((a) - (b)) < EPS)

//点
class Point {
public:
    double x, y;
    
    Point (double x = 0, double y = 0):x(x), y(y){}
    Point operator + (Point p){return Point(x + p.x, y + p.y);}
    Point operator - (Point p){return Point(x - p.x, y - p.y);}
    Point operator * (double a){return Point(a * x, a * y);}
    Point operator / (double a){return Point(x / a, y / a);}
    
    double norm(){return x*x + y*y;};
    double absolute(){return sqrt(norm());};
    
    bool operator < (const Point &p) const{
        return x != p.x ? x < p.x : y < p.y;
    }
    
    bool operator == (const Point &p) const{
        return equals(x, p.x) && equals(y, p.y);
    }
    
};
typedef Point Vector;                               //ベクトル
typedef struct Segment{Point p1, p2;}Segment;       //線分
//ベクトルaのノルム
double norm(Vector a){
    return a.x * a.x + a.y * a.y;
}
//ベクトルaの大きさ
double absolute(Vector a){
    return sqrt(norm(a));
}

//ベクトルa,bの内績
double dot(Vector a, Vector b){
    return a.x * b.x + a.y * b.y;
}
//ベクトルa,bの外積
double cross(Vector a, Vector b){
    return a.x * b.y - a.y * b.x;
}

//ベクトルaとbの直行判定
//aとbが直行の場合は、内績が0になる
bool isOrthogonal(Vector a, Vector b){
    return equals(dot(a,b), 0.0);
}

//ベクトルaとbの平行判定
//aとbが直行の場合は、外積が0になる
bool isParallel(Vector a , Vector b){
    return equals(cross(a,b), 0.0);
}

int main(){
    
    int x0, y0, x1, y1, x2, y2, x3, y3;
    
    int q;
    
    cin >> q;
    
    for (int i = 0; i < q; i++) {
        cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        Vector a = Point(x1, y1) - Point(x0, y0);
        Vector b = Point(x3, y3) - Point(x2, y2);
        
        if(isParallel(a, b)) cout << 2 << endl;
        else if(isOrthogonal(a, b)) cout << 1 << endl;
        else cout << 0 << endl;
    }


    return 0;
}