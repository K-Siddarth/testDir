#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // only works for directed graph;
    // if unidrected -> make edge bidirectional;
    // it is used for negative weight graphs / negaitive cycle graphs;
    
    // algo : if (no negaitive cycles);
    // relax all the edges n-1 times sequentially;
    //
    // relax : if(dist[u] + wt < dist[v]) dist[v] = dist[u] + wt;
    //
    int N, M; cin >> N >> M;
    int a, b, c;
    vector<vector<int>> edges;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }
    vector<pair<int, int>> adj[N];
    for (int i = 0; i < (int)edges.size(); i++) {
        a = edges[i][0];
        b = edges[i][1];
        c = edges[i][2];
        adj[a].push_back({b, c});
    }

    vector<int> dist(N, INT_MAX);
    dist[0] = 0;

    // relaxing the edges :
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < M; j++) {
            int u = edges[i][0];
            int wt = edges[i][2];
            int v = edges[i][1];
            if (dist[u] + wt < dist[v]) dist[v] = dist[u] + wt;
        }
    }
//     return dist
    // how to detect negative cycle
    // Nth iteration to check the cycle;

    for (int i = 0; i < (int)edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];

        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
            cout << "negative cycle" << endl;
            // return {-1};
        }
    }
    // return {dist};
    return 0;
}
