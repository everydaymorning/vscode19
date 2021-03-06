#include <bits/stdc++.h>
using namespace std;
int n, m, x, y, k;
int MAP[21][21];
vector<int> v;
int DICE[7];
int d1, d2, d3, d4, d5, d6;

int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,1,-1,0,0 };

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	cin >> n >> m >> x >> y >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int tmp;
		cin >> tmp;
		v.push_back(tmp);
	}

	for (int i = 0; i < k; i++) {
		d1 = DICE[1];
		d2 = DICE[2];
		d3 = DICE[3];
		d4 = DICE[4];
		d5 = DICE[5];
		d6 = DICE[6];
		int nx = x + dx[v[i]];
		int ny = y + dy[v[i]];
		if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
		switch (v[i]) {
		case 1:
			DICE[1] = d4;
			DICE[3] = d1;
			DICE[4] = d6;
			DICE[6] = d3;
			break;
		case 2:
			DICE[1] = d3;
			DICE[3] = d6;
			DICE[4] = d1;
			DICE[6] = d4;
			break;
		case 3:
			DICE[1] = d5;
			DICE[2] = d1;
			DICE[5] = d6;
			DICE[6] = d2;
			break;
		case 4:
			DICE[1] = d2;
			DICE[2] = d6;
			DICE[5] = d1;
			DICE[6] = d5;
			break;
		}
		if (MAP[nx][ny] != 0) {
			DICE[6] = MAP[nx][ny];
			MAP[nx][ny] = 0;
		}
		else {
			MAP[nx][ny] = DICE[6];

		}
		x = nx;
		y = ny;
		cout << DICE[1] << '\n';
	}
	return 0;

}