#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#pragma warning (disable:4996)
int dx[] = { 1,0,-1,0 }, dy[] = { 0,1,0,-1 };
int n, shark_x, shark_y, shark_size;
int arr[20][20], result;
//1. 거리 , 2. 위쪽, 3. 왼쪽

class Fish {
public:
	int x, y, size;
	int dist;
};

bool compare(Fish a, Fish b) {
	if (a.dist == b.dist) {
		if (a.x == b.x) {
			return a.y < b.y;
		}
		return a.x < b.x;
	}
	return a.dist < b.dist;
}
int d[20][20];
void calc_dist() {
	queue<pair<int, int>> q;
	q.push({ shark_x,shark_y });
	d[shark_x][shark_y] = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (d[nx][ny] != 0) continue;
			if (arr[nx][ny] > shark_size) continue;
			q.push({ nx,ny });
			d[nx][ny] = d[x][y] + 1;
		}
	}
}
vector<Fish> v;
int cnt;
void sol() {
	while (1) {
		for (int i = 0; i < n; i++) {
			fill(d[i], d[i] + n, 0);
		}
		calc_dist();
		deque<Fish> temp;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if(arr[i][j] !=0 && arr[i][j]<shark_size && d[i][j]!=0){
					Fish fish;
					fish.dist = d[i][j] - 1;
					fish.x = i, fish.y = j;
					fish.size = arr[i][j];
					temp.push_back(fish);
				}
			}
		}
		if (temp.empty()) return;

		sort(temp.begin(), temp.end(), compare);
		Fish next = temp.front();
		arr[next.x][next.y] = 0;
		shark_x = next.x, shark_y = next.y;
		result += next.dist;
		cnt++;
		if (cnt == shark_size) {
			shark_size++;
			cnt = 0;
		}
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 9) {
				shark_x = i, shark_y = j;
			}
			else if (arr[i][j] != 0) {
				Fish fish;
				fish.x = i, fish.y = j, fish.size = arr[i][j];
				v.push_back(fish);
			}
		}
	}

	shark_size = 2;
	arr[shark_x][shark_y] = 0;
	sol();
	cout << result;
}