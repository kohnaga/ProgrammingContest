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
typedef vector<Point> Polygon;                      //多角形
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

//線分s(p1p2)に対する点pの射影
Point project(Segment s, Point p){
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / norm(base);
    return s.p1 + base * r;
}

//線分s(p1p2)を対称軸とした点pの対象点
Point reflect(Segment s, Point p){
    return p + (project(s, p) - p) * 2.0;
}

//点a,点b間の距離
double getDistance(Point a, Point b){
    return absolute(a - b);
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
    return intersect(s1.p1, s1.p2, s2.p1, s2.p1);
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

//線分s1と線分s2の交点を求める
Point getCrossPoint(Segment s1, Segment s2){
    Vector base = s2.p2 - s2.p1;
    double d1 = abs(cross(base, s1.p1 - s2.p1));
    double d2 = abs(cross(base, s1.p2 - s2.p1));
    double t = d1 / (d1 + d2);
    return s1.p1 + (s1.p2 - s1.p1) * t;
}

//円と線分lの交点を求める
pair<Point, Point> getCrossPoints(Circle c, Line l){
    Vector pr = project(l, c.c);
    Vector e = (l.p2 - l.p1) / absolute(l.p2 - l.p1);
    double base = sqrt(c.r * c.r - norm(pr - c.c));
    return make_pair(pr + e * base, pr - e * base);
}

//円c1と円c2の交点を求める
Vector polar(double a, double r){
    //長さa,角度rのpointを求める
    return Point(cos(r) * a, sin(r) * a);
}
pair<Point, Point> getCrossPoints(Circle c1, Circle c2){
    Vector v = c2.c - c1.c;
    double d = absolute(v);
    double a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d) );
    double t = atan2(v.y, v.x);
    return make_pair(c1.c + polar(c1.r, t+a), c1.c + polar(c1.r, t-a));
}