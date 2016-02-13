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
//ベクトルa,bの内績
double dot(Vector a, Vector b){
    return a.x * b.x + a.y * b.y;
}

//線分s(p1p2)に対する点pの射影
Point project(Segment s, Point p){
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / norm(base);
    return s.p1 + base * r;
}


int main(){
    
    int x0, y0, x1, y1, x2, y2;
    
    int q;
    
    cin >> x0 >> y0 >> x1 >> y1;
    cin >> q;
    
    Segment s = {Point(x0, y0), Point(x1, y1)};
    
    for (int i = 0; i < q; i++) {
        cin >> x2 >> y2;
        Point p2 = Point(x2, y2);
        
        Point ans = project(s, p2);
        
        printf("%.8lf %.8lf\n", ans.x, ans.y);
    }
    
    
    return 0;
}