#include<cstdio>
#include<vector>
#include<climits>
#include<cstring>
#include<iostream>
#include<algorithm>
const int N = 123, M = 350;
using namespace std;
int n, m;
bool used[M];
vector<int> MST[N];
int f[N], d[N][N];
template <class T>T MIN(const T &a, const T &b){
	return a < b ? a : b;
}
struct YWZ{
	int x, y, z;
	bool operator < (const YWZ &b) const{
		return z < b.z;
	}
}edge[M];
inline void read(int &x){
	x = 0; char c = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = (x << 3) + (x << 1) + c - '0', c = getchar();
}
inline void intialize(void){
	memset(d, 0, sizeof(d));
	memset(MST, 0, sizeof(MST));
	memset(used, false, sizeof(used));
	for(int i = 1; i <= n; i++)
		f[i] = i, MST[i].push_back(i);
}
int root(int x){
	if(f[x] == x) return x;
	return f[x] = root(f[x]);
}
int main(){
	cin >> n >> m;
	for(int i = 0; i < m; i++)
		read(edge[i].x), read(edge[i].y), read(edge[i].z);
	sort(edge, edge + m);
	intialize();
	int sum = 0, cosum = INT_MAX;
	for(int i = 0; i < m; i++){
		int x = root(edge[i].x);
		int y = root(edge[i].y);
		int &z = edge[i].z;
		if(x == y) continue;
		sum += z, used[i] = true, f[x] = y;
		for(int j = 0; j < MST[x].size(); j++)
			for(int k = 0; k < MST[y].size(); k++)
				d[MST[x][j]][MST[y][k]] = d[MST[y][k]][MST[x][j]] = z;
		for(int j = 0; j < MST[x].size(); j++)
			MST[y].push_back(MST[x][j]);
	}
	for(int i = 0; i < m; i++){
		if(used[i]) continue;
		int &x = edge[i].x, &y = edge[i].y, &z = edge[i].z;
		cosum = MIN(cosum, sum + z - d[x][y]);
	}
	printf("sum: %d\tcosum: %d", sum, cosum);
	return 0;
}