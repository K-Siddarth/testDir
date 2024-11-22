#include <bits/stdc++.h>

using namespace std;

class DisjointSet {
	vector<int> rank, parent, size;
public:
	DisjointSet(int N) {
		rank.resize(N + 1, 0);
		size.resize(N + 1, 1);
		parent.resize(N+1);
		for (int i = 0; i <= N; i++) {
			parent[i] = i;
		}
	}

	int findUPar (int u) {
		if (u == parent[u]) {
			return u;
		}
		return parent[u] = findUPar(parent[u]);
	}

	void unionByRank (int u, int v) {
		int ulp_u = findUPar(u);
		int ulp_v = findUPar(v);

		if (ulp_u == ulp_v) {
			return; // this means that both are in the same set;
		}
		if (rank[ulp_u] < rank[ulp_v]) {
			parent[ulp_u] = ulp_v;
		} else if (rank[ulp_u] > rank[ulp_v]) {
			parent[ulp_v] = ulp_u;
		} else {
			parent[ulp_v] =ulp_u;
			rank[ulp_u]++;
		}
	}

	void unionBySize (int u, int v) {
		int ulp_u = findUPar(u);
		int ulp_v = findUPar(v);
		if (ulp_u == ulp_v) {
			return;
		}
		if (size[ulp_u] < size[ulp_v]) {
			parent[ulp_u] = ulp_v;
			size[ulp_v] += size[ulp_u];
		} else {
			parent[ulp_v] = ulp_u;
			size[ulp_u] += size[ulp_v];
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	/* algo: 
	 * 1. Sort all the edges according to weight
	 * then on iterating over the edges if both the nodes are in diff. compos => add it, else continue;
	 *
	 * */
	int V, M;
	vector<vector<int>> adj[M];
	vector<pair<int, pair<int, int>>> edges;
	
	DisjointSet ds(V);

	DisjointSet ds(V);
	vector<pair<int, pair<int, int>>> edges;
	
	for (int i = 0; i < V; i++) {
		for (auto it : adj[i]) {
			int u = i;
			int v = it[0];
			int wt = it[1];
			
			edges.push_back({wt, {u, v}});
		}
	}
	sort(edges.begin(), edges.end());
	
	int ans = 0; vector<vector<int>> mst;
	
	for (int i = 0; i < (int)edges.size(); i++) {
		int wt = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		
		if (ds.findUPar(u) != ds.findUPar(v)) {
			ans += wt;
			mst.push_back({u, v});
			ds.unionBySize (u, v);
		}
	}
	cout << "mst sum is : " << ans <<endl;
	cout << "mst is : \n";
	for (auto& it : mst) {
		cout << it[0] << ' ' << it[1] << endl;
	}
	return 0;
}
