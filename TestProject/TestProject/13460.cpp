#include <bits/stdc++.h>
using namespace std;
int n, m;
int cnt;
bool check[11][11][11][11];
char MAP[11][11];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

int red_x, red_y, blue_x, blue_y, es_x, es_y;
queue<pair<int, int>> red_q, blue_q;

void bfs() {
	red_q.push({ red_x, red_y });
	blue_q.push({ blue_x, blue_y });
	check[red_x][red_y][blue_x][blue_y] = true;

	while (!red_q.empty()) {
		int q_size = red_q.size();

		while (q_size--) {
			auto red_cur = red_q.front();
			auto blue_cur = blue_q.front();
			red_x = red_cur.first;
			red_y = red_cur.second;
			blue_x = blue_cur.first;
			blue_y = blue_cur.second;
			red_q.pop(); blue_q.pop();

			if (cnt > 10) break;

			if (red_x == es_x && red_y == es_y) {
				cout << cnt;
				return;
			}
			for (int dir = 0; dir < 4; dir++) {
				int red_nx = red_x + dx[dir];
				int red_ny = red_y + dy[dir];
				int blue_nx = blue_x + dx[dir];
				int blue_ny = blue_y + dy[dir];

				while (1) {
					if (MAP[red_nx][red_ny] == '#') {
						red_nx -= dx[dir];
						red_ny -= dy[dir];
						break;
					}
					if (MAP[red_nx][red_ny] == 'O') break;
					red_nx += dx[dir]; red_ny += dy[dir];
				}

				while (1) {
					if (MAP[blue_nx][blue_ny] == '#') {
						blue_nx -= dx[dir];
						blue_ny -= dy[dir];
						break;
					}
					if (MAP[blue_nx][blue_ny] == 'O') break;
					blue_nx += dx[dir]; blue_ny += dy[dir];
				}

				if (blue_nx == es_x && blue_ny == es_y) continue;
				
				if (red_nx == blue_nx && red_ny == blue_ny) {
					switch (dir) {
					case 0: red_x > blue_x ? red_nx++ : blue_nx++; break;
					case 1: red_x < blue_x ? red_nx-- : blue_nx--; break;
					case 2: red_y > blue_y ? red_ny++ : blue_ny++; break;
					case 3: red_y < blue_y ? red_ny-- : blue_ny--; break;
					}
				}

				if (check[red_nx][red_ny][blue_nx][blue_ny]) continue;
				red_q.push({ red_nx, red_ny });
				blue_q.push({ blue_nx, blue_ny });
				check[red_nx][red_ny][blue_nx][blue_ny] = true;
			}
		}
		cnt++;
		
	}
	cout << "-1";
}
int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'R') {
				red_x = i;
				red_y = j;
			}
			if (MAP[i][j] == 'B') {
				blue_x = i;
				blue_y = j;
			}
			if (MAP[i][j] == 'O') {
				es_x = i;
				es_y = j;
			}
		}
	}

	bfs();
	return 0;
}