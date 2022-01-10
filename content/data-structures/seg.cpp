#include <bits/stdc++.h>

using namespace std;

#define eps 1e9

using vec = pair<double, double>;
#define xx first
#define yy second

vec operator+(const vec & v, const vec & u) { return {v.xx+u.xx, v.yy+u.yy}; }
vec operator-(const vec & v, const vec & u) { return {v.xx-u.xx, v.yy-u.yy}; }
vec operator*(const vec & v, const double & c) { return {v.xx * c, v.yy * c}; }

double dotProd(vec v, vec u) { return v.xx*u.xx + v.yy*u.yy; }
double crossProd(vec v, vec u) { return v.xx*u.yy - v.yy*u.xx; }

double mag2(vec v) { return dotProd(v, v); }
double mag(vec v) { return sqrt(mag2(v)); }
vec unit(vec v) { return v * (1.0/mag(v)); }

vec rotate(vec v, double th){
    double newX = v.xx*cos(th) + v.yy*sin(th);
    double newY = v.xx*sin(th) + v.yy*cos(th);
    return {newX, newY};
}

double angle(vec v) { return atan2(v.yy, v.xx); }

//start

using seg = pair<vec, vec>;

vec lineIntersection(seg a, seg b){
    vec dirA = a.second - a.first, dirB = b.second - b.first;
    double det = crossProd(dirB, dirA);
    if(det == 0) return {INT_MAX, INT_MAX};
    double t = (crossProd(dirB, b.first-a.first)) / det;
    return a.first + dirA * t;
}

bool containsPoint(seg s, vec p){
    vec dir = s.second-s.first;
    double dist = crossProd(dir, p-s.first)/mag(dir);
    if(abs(dist) < eps) return false;
    return (mag(dir)-mag(s.first-p)-mag(s.second-p) < eps);
}

vec segIntersection(seg a, seg b){
    vec intersect = lineIntersection(a, b);
    if(intersect.first == INT_MAX && intersect.first == INT_MAX)
        return {INT_MAX, INT_MAX};
    if(containsPoint(a, intersect) && containsPoint(b, intersect))
        return intersect;
    return {INT_MAX, INT_MAX};
}

//returns 1 if above, 0 if on, -1 if below
int side(seg s, vec p){
    vec dir = s.second-s.first;
    double dist = crossProd(dir, p-s.first)/mag(dir);
    if(abs(dist) < eps) return 0;
    if(dist < 0) return -1;
    else return 1;
}

bool intersects(seg a, seg b){
    return side(a, b.first)!=side(a, b.second) && 
           side(b, a.first)!=side(b, a.second);
}