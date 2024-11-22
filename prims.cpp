#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
/*
 * Spanning tree: a graph with N nodes and N-1 edges, where all nodes are reachable from one another
 * MST: Spanning tree with minimum sum of edge weights;
 * */
	int M; 
	int V;
	vector<pair<int, int>> adj[M];
	
	// algo :
	vector<int> vis(V, 0);
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
	pq.push({0, 0, -1}); // wt, node, parent;
	vector<vector<int>> mst;
	int sum = 0;

	while (pq.size()) {
		vector<int> top = pq.top();
		pq.pop();
		int wt = top[0];
		int u = top[1];
		int u_par = top[2];
		if (vis[u]) {
			continue;
		}
		vis[u] = 1;
		mst.push_back({u_par, u});
		sum += wt;
		for (pair<int, int> it : adj[u]) {
			int v = it.first;
			int edWt = it.second;
			if (!vis[v]) {
				pq.push({edWt, v, u});
			}
		}
	}

	cout << "min sum of weights is : " << sum << endl;
	cout << "Tree is: ";
	for (auto& it : mst) {
		cout << it[0] << ' ' << it[1] << endl;
	}
	return 0;
}
