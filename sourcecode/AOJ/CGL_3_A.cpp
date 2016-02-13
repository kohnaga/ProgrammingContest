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
//ベクトルa,bの外積
double cross(Vector a, Vector b){
    return a.x * b.y - a.y * b.x;
}


//参考サイト：http://imagingsolution.net/math/calc_n_point_area/
int main(){
    
    int n;
    double ans = 0.0;
    double area = 0.0, s = 0.0, t = 0.0;
    
    cin >> n;
    
    Vector *q = new Vector[n];
    
    for (int i = 0; i < n; i++) {
        cin >> q[i].x;
        cin >> q[i].y;
    }
    
    for (int i = 0; i < n; i++) {
        if ( ( area = cross(q[i], q[(i+1)%n]) ) > EPS) {
            s += fabs(area) / 2.0;
        }
        else{
            t += fabs(area) / 2.0;
        }
    }
    ans = fabs(s-t);
    
    printf("%.1lf\n", ans);

    return 0;
}