/**
 * Description: Vector code
 *
 * Time: $O(1)$
 * Memory: $O(1)$
 */

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

vec rotate90(vec v){ return{-v.yy, v.xx}; }
vec rotate270(vec v){ return{v.yy, -v.xx}; }
vec rotate(vec v, double th){
    double newX = v.xx*cos(th) + v.yy*sin(th);
    double newY = v.xx*sin(th) + v.yy*cos(th);
    return {newX, newY};
}

double angle(vec v) { return atan2(v.yy, v.xx); }
