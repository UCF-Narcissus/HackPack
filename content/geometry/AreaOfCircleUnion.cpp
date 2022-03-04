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

vec rotate90(vec v){ return{-v.yy, v.xx}; }
vec rotate270(vec v){ return{v.yy, -v.xx}; }
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

using cir = pair<vec, int>;

int circleInter(cir a, cir b, pair<vec, vec> & out) {
    double r1 = a.second, r2 = b.second;
	vec v = b.first - a.first;
	double d2 = mag2(v), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return 0;
	vec mid = a.first + v*p, per = rotate90(v) * sqrtl(fmax(0, h2) / d2);
	out = {mid + per, mid - per};
    if(abs(mag2(per)) <= 1e-12)
        return 1;
	return 2;
}

pair<vec, vec> getTangentPoints(cir c, vec p){
    int d2 = mag2(c.first-p);
    pair<vec, vec> tangents;
    circleInter({p, sqrt(d2-c.second*c.second)}, c, tangents);
    return tangents;
}

vector<vec> circleLineInter(cir c, seg l){
    vector<vec> out;
    vec ab = l.second - l.first;
    vec p = l.first + ab * dotProd(c.first-l.first, ab) * (1.0/mag2(ab));
    double s = crossProd(ab, c.first-l.first);
    double h2 = c.second*c.second - s*s/mag2(ab);
    if(h2 < 0) return out;
    if(h2 == 0){
        out.push_back(p);
        return out;
    }
    vec h = unit(ab) * sqrt(h2);
    out.push_back(p-h); out.push_back(p+h);
    return out;
}

double areaOfCircleUnion(vector<cir> c, int n){
    double area = 0;

    sort(c.begin(), c.end(), [](cir a, cir b)->bool{
        return a.first < b.first;
    });

    bool isUnique[n]; memset(isUnique, true, sizeof(isUnique));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            if(c[j].second + mag(c[j].first-c[i].first) < c[i].second)
                isUnique[j] = false;
        }
    }
    
    for(int i = 0; i < n; i++){
        if(isUnique[i]){
            vector<pair<double, double>> sweep;
            bool good = false;
            for(int j = 0; j < n; j++){
                if(i==j) continue;
                if(isUnique[j]){
                    pair<vec, vec> inters;
                    int cnt = circleInter(c[i], c[j], inters);
                    if(cnt < 2)
                        continue;
                    
                    good = true;

                    double ang1 = angle(inters.second-c[i].first);
                    double ang2 = angle(inters.first-c[i].first);
                    if(ang1 < -eps) ang1 += 2 * M_PI;
                    if(ang2 < -eps) ang2 += 2 * M_PI;

                    if(ang1-ang2 > eps){
                        sweep.push_back({0, ang2});
                        sweep.push_back({ang1, 2 * M_PI});
                    }
                    else
                        sweep.push_back({ang1, ang2});
                }
            }

            if(!good){
                area += M_PI * c[i].second * c[i].second;
                continue;
            }

            sort(sweep.begin(), sweep.end());
            int idx = 0, l = sweep.size();
            for(int j = 1; j < l; j++){
                if(sweep[idx].second-sweep[j].first > -eps)
                    sweep[idx].second = max(sweep[idx].second, sweep[j].second);
                else
                    sweep[++idx] = sweep[j];
            }

            if(idx == l-1) sweep.push_back({0, 0});
            sweep[++idx] = sweep[0];
            
            for(int j = 0; j < idx; j++){
                vec a = c[i].first + (make_pair(cos(sweep[j].second), sin(sweep[j].second)) * c[i].second);
                vec b = c[i].first + (make_pair(cos(sweep[j+1].first), sin(sweep[j+1].first)) * c[i].second);
                
                area += crossProd(a, b)/2.0;

                double th = sweep[j+1].first-sweep[j].second;
                if(th < -eps) th += 2 * M_PI;
                area += 0.5 * c[i].second * c[i].second * (th - sinl(th));
            }
        }
    }

    return area;
}