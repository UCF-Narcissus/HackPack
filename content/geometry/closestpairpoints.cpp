struct vec{
    ld x, y; int id;
    explicit vec(ld x=0, ld y=0, int id=0) : x(x), y(y), id(id){}
    bool operator< (vec o){
        return id < o.id;
    }
};

int n;
vector<vec> a, t; ld mindist;
pair<int, int> best;

void updClosest(const vec& a, const vec& b){
    ld dx = a.x - b.x, dy = a.y - b.y;
    ld dist = sqrtl(dx*dx + dy*dy);
    if(dist < mindist){
        mindist = dist;
        best = {a.id, b.id};
    }
}

bool cmpX(const vec& a, const vec& b){
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cmpY(const vec& a, const vec& b){
    return a.y < b.y;
}

void solve(int l, int r){
    if(r-l <= 3){
        for(int i = l; i < r; i++){
            for(int j = i+1; j < r; j++){
                updClosest(a[i], a[j]);
            }
        }
        sort(a.begin()+l, a.begin()+r, cmpY);
        return;
    }

    int m = (l+r)/2;
    int midx = a[m].x;
    solve(l, m);
    solve(m, r);    

    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, t.begin(), cmpY);
    copy(t.begin(), t.begin() + (r-l), a.begin() + l);

    int tSz = 0;
    for(int i = l; i < r; i++){
        if(abs(a[i].x-midx) < mindist){
            for(int j = tSz - 1; j >= 0 && a[i].y - t[j].y < mindist; j--){
                updClosest(a[i], t[j]);
            }
            t[tSz++] = a[i];    
        }
    }
}

void clstPts(){
    t = vector<vec>(n);
    sort(a.begin(), a.end(), cmpX);
    mindist = 1e20;
    solve(0, n);
    sort(a.begin(), a.end());
}
