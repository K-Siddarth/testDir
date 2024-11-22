#include <bits/stdc++.h>

using namespace std;

bool dfs(int i, vector<int>& vis, vector<int>& res, vector<vector<int>> adj) {
    vis[i] = 1;
    res[i] = 1;
    for (auto& v : adj[i]) {
        if (!vis[i]) {
            if (dfs(v, vis, res, adj)) {
                return true;
            }
        } else if (res[i]) {
            return true;
        }
    }
    res[i] = 0;
    return false;
}

bool has_cycle(vector<vector<int>>& adj) {
    int n = (int)adj.size();
    vector<int> vis(n, 0), rec_stak(n, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
