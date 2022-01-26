/**
 * Description: Find a topsort of a directed graph
 * Time: $O(V + E)$
 * Memory: $O(V)$
 */
using namespace std;

#define vv first
#define ww second
using edge = pair<int, int>;

void topSortUtil(vector<edge> g[], int v, stack<int> s, bool seen[]){
    seen[v] = true;
    for(edge e : g[v])
        if(!seen[e.vv])
            topSortUtil(g, e.vv, s, seen);
    s.push(v);
}

vector<int> topSort(vector<edge> g[], int v){
    stack<int> out;
    bool seen[v];
    for(int i = 0; i < v; i++)
        if(!seen[i])
            topSortUtil(g, i, out, seen);
    vector<int> ts(v);
    for(int i = v-1; i >= 0; i--){
        ts[i] = out.top();
        out.pop();
    }
    return ts;
}
