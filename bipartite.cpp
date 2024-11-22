#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = (int)graph.size();
        vector<int> set(n, -1);

        auto bfs = [&] (int node) {
            queue<pair<int, int>> q;
            if (set[node] != -1) {
                return true;
            }
            q.push({node, 0});
            while (q.size()) {
                int N = q.front().first;
                int Lv = q.front().second;
                set[N] = (Lv)%2;
                q.pop();
                for (auto& v : graph[N]) {
                    if (set[v] == set[N]) {
                        return false;
                    }
                    if (set[v] == -1)
                        q.push({v, Lv+1});
                }
            }
            return true;
        };

        for (int i = 0; i < n; i++) {
            if (!bfs(i)) {
                return false;
            }
        }
        return true;
    }
};

void solve() {
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int tt = 1;
	// cin >> tt;
	while (tt--) {
		solve();
	}
	return 0;
}
