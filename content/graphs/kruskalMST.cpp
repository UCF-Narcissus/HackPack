#include <bits/stdc++.h>

using namespace std;

#define vv first
#define ww second
using edge = tuple<int, int, int>;

struct disjoint_set{
    int n;
    int *par, *height;

    disjoint_set(int nn){
        n = nn;
        par = new int[n];
        memset(par, -1, sizeof(par));
        height = new int[n];
        memset(height, 1, sizeof(height));
    }

    int parent(int i){
        return par[i] == -1 ? i : (par[i] = parent(par[i]));
    }

    void unionize(int a, int b){
        a = parent(a);
        b = parent(b);

        if(a==b) return;
        if(height[a] == height[b])
            height[a]++;

        if(height[a] >= height[b])
            par[b] = a;
        else par[a] = b;
    }
};

vector<edge> kruskalMST(vector<edge> edges, int n){
    sort(edges.begin(), edges.end(), [&](edge & a, edge & b) -> bool { return get<2>(a) < get<2>(b); });
    disjoint_set ds(n);

    int tot = 0;
    vector<edge> out;
    for(edge e : edges){
        if(ds.parent(get<0>(e)) != ds.parent(get<1>(e))){
            tot += get<2>(e);
            out.push_back(e);
            ds.unionize(get<0>(e), get<1>(e));
        }
    }

    return out;
}