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
//直線sと点pの距離
double getDistanceLP(Line l, Point p){
    return abs(cross(l.p2 - l.p1, p - l.p1) / absolute(l.p2 - l.p1));
}

//線分s(p1p2)と点pの距離dを求める
//以下の３パターンで場合分け
//１：ベクトルp2-p1と、ベクトルp-p1がなす角度が90度より大きい場合（または-90度よりも小さい場合）、dは点pと点p1との距離
//２：ベクトルp1-p2と、ベクトルp-p2がなす角度が90度より大きい場合（または-90度よりも小さい場合）、dは点pと点p2との距離
//３：それ以外の位置にある場合、dは点pと直線p1p2の距離
double getDistanceSP(Segment s, Point p){
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return absolute(p - s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return absolute(p - s.p2);
    return getDistanceLP(s, p);
}


//３点p0, p1, p2について、ベクトルp0p1に対して点p2の位置を返す
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;
int ccw(Point p0, Point p1, Point p2){
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if(cross(a, b) > EPS) return COUNTER_CLOCKWISE;
    if(cross(a, b) < -EPS) return CLOCKWISE;
    if(dot(a, b) < -EPS) return ONLINE_BACK;
    if(norm(a) < norm(b)) return ONLINE_FRONT;
    return ON_SEGMENT;
}

//線分S1(p1p2)と線分s2(p2p3)の交差判定を行う
bool intersect(Point p1, Point p2, Point p3, Point p4){
    return  ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0
            &&
            ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0;
}
bool intersect(Segment s1, Segment s2){
    return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

//線分s1と線分s2の距離
//以下の４つの距離の中で最短のものになる
//１：線分s1と線分s2の始点s2.p1の距離
//２：線分s1と線分s2の終点s2.p2の距離
//３：線分s2と線分s1の始点s1.p1の距離
//４：線分s2と線分s1の終点s1.p2の距離
double getDistance(Segment s1, Segment s2){
    if ( intersect(s1, s2) ) return 0.0;
    return min(
               min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
               min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2))
               );
}

int main(){
    
    int x0, y0, x1, y1, x2, y2, x3, y3;
    
    int q;
    
    cin >> q;
    
    for (int i = 0; i < q; i++) {
        cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        
        Point p0 = Point(x0, y0);
        Point p1 = Point(x1, y1);
        Point p2 = Point(x2, y2);
        Point p3 = Point(x3, y3);
        
        Segment s1 = {p0, p1};
        Segment s2 = {p2, p3};
        
        double ans = getDistance(s1, s2);
        
        printf("%.8lf\n", ans);
    }

    return 0;
}