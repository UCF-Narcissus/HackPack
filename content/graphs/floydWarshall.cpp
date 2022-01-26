/**
 * Description: FindAll-Pairs Shortest Paths (APSP)
 *
 * Time: $O(n^3)$
 * Memory: $O(n^2)$
 */

#define vv first
#define ww second
using edge = pair<int, int>;

void floydWarshall(vector<edge> g[], int n){
    int d[n][n];
    memset(d, INT_MAX, sizeof(d));
    for(int i = 0; i < n; i++) d[i][i] = 0;

    for(int i = 0; i < n; i++){
        for(edge e : g[i]){
            if(e.ww < d[i][e.vv])
                d[i][e.vv] = d[e.vv][i] = e.ww;
        }
    }

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

}
