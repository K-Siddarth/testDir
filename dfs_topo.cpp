#include <bits/stdc++.h>

using namespace std;

void dfs(int start, vector<int> adj[], vector<int>& vis, stack<int>& ans) {
    // normal dfs
    vis[start] = 1;
    for (auto& v : adj[start]) {
        if (!vis[v]) {
            dfs(v, adj, vis, ans);
        } 
    }
    // pushing nodes in stack after dfs of all of its children nodes is complete
    ans.push(start);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    int V, E;
    cin >> E >> V;
    int a, b;
    vector<int> adj[V];
    vector<int> in(V, 0);
    for (int i = 0; i < E; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        in[b]++;
    }
    // mark the indegrees of nodes;
    int start = -1;
    for (int i = 0; i < V; i++) {
        if (in[i] == 0) {
            start = i;
            // find a node with in[i] == 0;
            break;
        }
    }
    if (start == -1) {
        // if all nodes have in[i] != 0;
        cout << "Graph is not DAG\n";
        return 0;
    }
    vector<int> vis(V, 0);
    stack<int> ans;
    // dfs on graph
    dfs(start, adj, vis, ans);
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            dfs(i, adj, vis, ans);
        }
    }
    while (!ans.empty()) {
        cout << ans.top() << ' ';
        ans.pop();
    }
    return 0;
}
