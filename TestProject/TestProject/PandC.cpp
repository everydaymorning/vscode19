#include <bits/stdc++.h>
using namespace std;
int n;
int arr[6];
bool check[6];
vector<int> v;
void dfs_p(int s) {
	if (s == n) {
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << '\n';
		return;
	}

	for (int i = 0; i < n; i++) {
		if (check[i]) continue;
		check[i] = true;
		v.push_back(arr[i]);
		dfs_p(s + 1);
		v.pop_back();
		check[i] = false;
	}
}

void dfs_c(int idx, int s) {
	if (s == 3) {
		for (int i = 0; i < n; i++) {
			if (check[i]) {
				cout << arr[i] << " ";
			}
		}
		cout << '\n';
		return;
	}

	for (int i = idx; i < n; i++) {
		if (check[i]) continue;
		check[i] = true;
		dfs_c(i, s + 1);
		check[i] = false;
	}
}
int main() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	dfs_p(0);

	memset(check, false, sizeof(check));

	dfs_c(0, 0);
	return 0;
}