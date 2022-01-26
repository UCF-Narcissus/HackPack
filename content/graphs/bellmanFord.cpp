/**
 * Description: Single Source Shortest Path (SSSP) 
 * Time: $O(V^3)$
 * Memory: $O(V^2)$
 */
#define vv first
#define ww second
using edge = pair<int, int>;

void bellmanFord(vector<edge> g[], int v, int s){
    int dist[v];
    memset(dist, 0, sizeof(0));

    for(int i = 0; i < v-1; i++)
        for(int u = 0; u < v; u++)
            for(edge e : g[u])
                if(dist[u] + e.ww < dist[e.vv])
                    dist[e.vv] = dist[u] + e.ww;
    
    //check for negative cycles
    for(int u = 0; u < v; u++){
        for(edge e : g[u]){
            if(dist[u]!=INT_MAX && dist[u] + e.ww < dist[e.vv]){
                //negative cycle reached
                return;
            }
        }
    }
}
