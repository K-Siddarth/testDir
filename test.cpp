#include <bits/stdc++.h>

using namespace std;

int solve(vector<vector<int>>& grid) {
	//maxAreaOfIsland
	map<pair<int, int>, int> vis;
	int ans = 0;
	for (int i = 0; i < (int)grid.size(); i++) {
		for (int j = 0; j < (int)grid[0].size(); j++) {
			if (grid[i][j] && !vis[{i, j}]) {
				dfs(i, j, vis, grid, 1, ans);
			}
		}
	}
	return ans;
}

int di[] = {-1, 0, 1, 0};
int dj[] = {0, 1, 0, -1};

void dfs(int i, int j, map<pair<int, int>>& vis, vector<vector<int>>& grid, int& ans, int curr) {
	vis[{i, j}] = 1;
	ans = max(ans, curr);
	for (int k = 0; k < 4; k++) {
		int ni = i + di[k];
		int nj = j + dj[k];
		if (ni >= 0 && ni < (int)grid.size() && nj >= 0 && nj < (int)grid[0].size() && !vis[{ni, nj}] && grid[ni][nj] == 1) {
			dfs(ni, nj, vis, grid, ans, curr + 1);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	return 0;
}
