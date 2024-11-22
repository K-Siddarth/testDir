#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	freopen("input.txt", "r", stdin);
	int V, E;
	cin >> V >> E;
	vector<int> adj[V];
	int a, b;
	vector<int> in(V, 0);
	for (int i = 0; i < E; i++) {
		cin >> a >> b;
		adj[b].push_back(a);
		in[a]++;
	}
	queue<int> q;
	for (int i = 0; i < V; i++) {
		cout << i << ": " << in[i] << endl;
		if (in[i] == 0) {
			q.push(i);
		}
	}
	vector<int> ans;
	while (q.size()){
		int top = q.front();
		q.pop();
		ans.push_back(top);
		for (auto& v : adj[top]) {
			in[v]--;
			if (in[v] == 0) {
				q.push(v);
			}
		}
	}
	for (auto& it : ans) {
		cout << it << ' ';
	}
	cout << endl;
	return 0;
}
