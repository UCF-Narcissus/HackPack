/**
 * Description: Computes shortest paths from s
 * to any node reachable from s.
 * Pass in an adjacency list of pairs (node, weight)
 * and a starting node s.
 * Time: $O((|V| + |E|) \log{|V|})$
 */

constexpr int INF = (int) 1e9;
vector<int> dijkstra(
        vector<vector<ii>> adjlist, int s) {
    using ii = pair<int, int>;
    vector<int> dist(V, INF); dist[s] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(ii(0, s));
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adjlist[u])
            if (d + w < dist[v])
                pq.push(ii(dist[v] = d + w, v));
    }
    return dist;
}
