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
	/*
	 * DSU: helps to answer queries in O(1) time usually on whether 2 nodes are in the same component or not;
	 * union(u, v):
	 * 1. find ultimate par of u and v = [pu, pv];
	 * find rank of pu and pv
	 * connect smaller rank to larger one
	 * */
	DisjointSet ds(7);
	ds.unionByRank(1, 2);
	ds.unionByRank(2, 3);
	ds.unionByRank(4, 7);
	ds.unionByRank(6, 2);
	ds.unionByRank(5, 6);
	cout << (ds.findUPar(3) == ds.findUPar(7) ? "Same\n" : "No\n");
	ds.unionByRank(3, 7);
	cout << (ds.findUPar(3) == ds.findUPar(7) ? "Same\n" : "No\n");
	return 0;
}
