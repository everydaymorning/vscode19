#include <bits/stdc++.h>
using namespace std;
int r, c, m, cnt;
struct Shark {
	int x;
	int y;
	int s; // 속도
	int d; // 방향
	int z; // 크기
	int num; // 상어 번호
};
int dx[5] = { 0,-1,1,0,0 };
int dy[5] = { 0,0,0,1,-1 };
vector<Shark> shark;
vector<int> shark_loc[101][101];

bool cmp(int a, int b) {
	return shark[a].z > shark[b].z;
}
int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	cin >> r >> c >> m;
	for (int i = 0; i < m; i++) {
		int x, y, s, d, z;
		cin >> x >> y >> s >> d >> z;
		shark.push_back({ x,y,s,d,z,i });
		shark_loc[x][y].push_back(i);
	}

	for (int i = 1; i <= c; i++) {
		bool flag = false;

		for (int j = 0; j < shark.size(); j++) {
			if (shark[j].z != 0) { // 상어 크기가 0이 아니면 -> 살아있는 상어가 있다면
				flag = true;
				break; // 상어가 하나라도 있으면 flag를 true로 바꿔주고 탈출
			}
		}
		if (!flag) break; // 상어가 없다면 바로 탈출

		for (int j = 1; j <= r; j++) {
			if (shark_loc[j][i].size() > 0) { // 해당하는 상어의 위치에 상어가 있다면
				cnt += shark[shark_loc[j][i][0]].z; // 가장 크기가 큰 상어의 크기만큼 cnt 증가
				shark[shark_loc[j][i][0]].z = 0; // 해당 위치의 상어의 크기를 0으로 변경 -> 상어를 잡았다는 표시
				shark_loc[j][i].clear(); // 해당 위치의 상어는 이제 없음
				break;
			}
		}

		for (int j = 0; j < shark.size(); j++) {
			if (shark[j].z == 0) continue; // 죽은 상어면 continue
			int x = shark[j].x;
			int y = shark[j].y;
			shark_loc[x][y].clear(); // 상어를 이동시켜주기 위해 미리 해당 위치의 상어들을 지워줌
		}

		for (int j = 0; j < shark.size(); j++) {
			if (shark[j].z == 0) continue; // 죽은 상어면 continue
			int x = shark[j].x;
			int y = shark[j].y;
			int s = shark[j].s;
			int d = shark[j].d;

			if (d == 1 || d == 2) { // 방향이 북쪽이거나 남쪽이면
				int dis = (r - 1) * 2;  // 상어가 제자리로 돌아왔을 때 거리
				if (s >= dis) s = s % dis; // 상어의 속도가 dis보다 크거나 같으면 상어의 속도 연산

				for (int k = 0; k < s; k++) { // 상어의 속도만큼 이동
					int nx = x + dx[d];
					int ny = y + dy[d];
					if (nx < 1) { // 상어가 북쪽으로 가다가 범위를 벗어나면
						d = 2; // 방향을 남쪽으로 바꿔준다
						nx += 2; // 상어 x축 이동
					}
					else if (nx > r) { // 상어가 남쪽으로 가다가 범위를 벗어나면
						d = 1; // 방향을 북쪽으로 바꿔준다
						nx -= 2; // 상어 x축 이동
					}
					x = nx; // x 위치 업데이트
					y = ny;
				}
			}
			else {
				int dis = (c - 1) * 2; // 상어가 제자리로 왔을 때 거리
				if (s >= dis) s = s % dis;

				for (int k = 0; k < s; k++) {
					int nx = x + dx[d];
					int ny = y + dy[d];
					if (ny < 1) {
						d = 3;
						ny += 2;
					}
					else if (ny > c) {
						d = 4;
						ny -= 2;
					}
					x = nx;
					y = ny;
				}
			}

			shark[j].x = x; // 상어의 좌표 업데이트
			shark[j].y = y;
			shark[j].d = d; // 상어의 방향 업데이트
			shark_loc[x][y].push_back(j); // 해당하는 위치에 상어를 넣어줌
		}


		for (int j = 1; j <= r; j++) {
			for (int k = 1; k <= c; k++) {
				if (shark_loc[j][k].size() > 1) { // 해당 위치에 상어가 2마리 이상이면 
					sort(shark_loc[j][k].begin(), shark_loc[j][k].end(), cmp); // 상어의 크기를 내림차순으로 정렬
					int big_shark_idx = shark_loc[j][k][0]; // 가장 큰 상어의 번호
					for (int L = 1; L < shark_loc[j][k].size(); L++) { // 가장 큰 상어를 제외한 상어들
						shark[shark_loc[j][k][L]].z = 0; // 크기를 0으로 만들어줌 -> 상어 죽이기
						shark[shark_loc[j][k][L]].x = -1; // 좌표를 범위밖으로
						shark[shark_loc[j][k][L]].y = -1;
					}
					shark_loc[j][k].clear(); // 해당 위치의 상어들 제거
					shark_loc[j][k].push_back(shark[big_shark_idx].num); // 해당 위치에 가장 큰 상어의 번호를 넣어줌
				}
			}
		}
	}
	cout << cnt;
	return 0;
}