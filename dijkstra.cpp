#include <bits/stdc++.h>

using namespace std;
#define int long long

int32_t  main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N, M, src;
	cin >> N >> M >> src;
	vector<pair<int, int>> adj[N];

	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}

	// cannot be implemented for negative weights;
	vector<int> dist(N, INT_MAX);
	dist[src] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push({src, 0});

	while (q.size()) {
		int u = q.top().first;
		int d = q.top().second;
		q.pop();

		for (auto& v : adj[u]) {
			if (d + v.second < dist[v.first]) {
				dist[v.first] = dist[u] + v.second;
				q.push({v.first, dist[v.first]});
			}
		}
	}
	for (int i = 0; i < N; i++) {
		cout << dist[i] << ' ';
	}
	return 0;
}
