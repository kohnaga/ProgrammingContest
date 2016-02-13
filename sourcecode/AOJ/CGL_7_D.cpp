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
typedef Segment Line;                               //直線
typedef struct Circle{Point c; double r;}Circle;    //円

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

//線分s(p1p2)に対する点pの射影
Point project(Segment s, Point p){
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / norm(base);
    return s.p1 + base * r;
}

//円と線分lの交点を求める
pair<Point, Point> getCrossPoints(Circle c, Line l){
    Vector pr = project(l, c.c);
    Vector e = (l.p2 - l.p1) / absolute(l.p2 - l.p1);
    double base = sqrt(c.r * c.r - norm(pr - c.c));
    return make_pair(pr + e * base, pr - e * base);
}

int main(){
    
    int cx, cy;
    double r;
    int q;
    int x1, y1, x2, y2;
    
    cin >> cx >> cy >> r >> q;
    
    Circle c = {Point(cx, cy), r};
    
    for (int i = 0; i < q; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        
        Line l = {Point(x1, y1), Point(x2, y2)};
        
        pair<Point, Point> ans = getCrossPoints(c, l);
        bool swap_flag = (ans.first.x == ans.second.x) ? ans.first.y > ans.second.y : (ans.first.x > ans.second.x);
        if(swap_flag) swap(ans.first, ans.second);
        
        printf("%.8lf %.8lf %.8lf %.8lf\n", ans.first.x, ans.first.y, ans.second.x, ans.second.y);
    }

    return 0;
}