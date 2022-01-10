#include <bits/stdc++.h>

using namespace std;

#define vv first
#define ww second
using edge = pair<int, int>;

void djikstras(vector<edge> g[], int v, int s){
    priority_queue<edge, vector<edge>, greater<edge>> pq;
    vector<int> dist(v, INT_MAX);

    dist[s] = 0;
    pq.push(make_pair(0,s));

    while(!pq.empty()){
        if(pq.top().first > dist[pq.top().first])
            continue;

        int u = pq.top().second;
        pq.pop();

        for(edge e : g[u]){
            if(dist[e.vv] > dist[u] + e.ww){
                dist[e.vv] = dist[u] + e.ww;
                pq.push(make_pair(dist[e.vv], e.vv));
            }
        }
    }
}