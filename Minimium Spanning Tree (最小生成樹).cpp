#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1000, M = 3000;
int f[N], n, m, ans;
struct YWZ{
	int x, y, z;
	bool operator < (const YWZ &b) const{return z < b.z;}
}edge[M];
int root(int x){
	if(x == f[x]) return x;
	return f[x] = root(f[x]);
}
inline int read(void){
	int x = 0; char ch = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
	return x;
}
int main(){
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		int x = read(), y = read(), z = read();
		edge[i] = (YWZ){x, y, z};
	}
	for(int i = 1; i <= n; i++) f[i] = i;
	sort(edge + 1, edge + 1 + m);
	for(int i = 1; i <= m; i++){
		int rx = root(edge[i].x);
		int ry = root(edge[i].y);
		if(rx == ry) continue;
		f[rx] = ry, ans += edge[i].z;
	}
	cout << ans << endl;
	return 0;
}