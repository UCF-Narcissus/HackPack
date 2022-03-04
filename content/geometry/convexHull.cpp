/**
 * Description: Monotone Chaining for Convex Hull
 * Time: $O(n \log{n})$
 * Memory: $O(n)$
 */

vector<point> convexHull(vector<point> p, int n){
    vector<point> hull(2*n);
    sort(p.begin(), p.end());
    if(n == 1) 
        return p;

    int k = 0;
    for(int i = 0; i < n; i++){
        while(k >= 2 && cross(hull[k-1] - hull[k-2], p[i] - hull[k-2]) <= 0)
            k--;
        hull[k++] = p[i];
    }

    for(int i = n-1, t = k+1; i > 0; i--){
        while(k >= t && cross(hull[k-1] - hull[k-2], p[i-1] - hull[k-2]) <= 0)
            k--;
        hull[k++] = p[i-1];
    }

    hull.resize(k-1);

    return hull;
}
