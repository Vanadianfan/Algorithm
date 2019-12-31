#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1000007, M = N;
int hd[N], Next[M], ver[M], d[N];
int n, m, tot, rt = 1, f[N][22], lg[N];
inline void access(int x, int y){
	ver[++tot] = y, 
	Next[tot] = hd[x], hd[x] = tot;
}
void establish(int x, int last){
	d[x] = d[last] + 1, f[x][0] = last;
	for (int j = 1; (1 << j) <= d[x]; ++j)
		f[x][j] = f[f[x][j - 1]][j - 1];
	for(int i = hd[x]; i; i = Next[i]){
		int y = ver[i];
		if(y != last) establish(y, x);
	}
}
inline int read(){
	int x = 0, w = 1; char ch = 0;
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1;ch = getchar();}
	while (ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
	return x * w;
}
int LCA(int x, int y){
	if(d[x] > d[y]) swap(x, y);
	while(d[x] < d[y]) y = f[y][lg[d[y] - d[x]] - 1];
	if(x == y) return x;
	for(int i = lg[d[x]] - 1; i >= 0; i--)
		if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}
int main(){
	cin >> n >> m >> rt;
	for(int i = 1; i <= n; i++)
		lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
	for(int i = 1; i < n; i++){
		int x = read(), y = read();
		access(x, y), access(y, x);
	}
	d[rt] = 1, f[rt][0] = 0;
	establish(rt, -1);
	for(int i = 1; i <= m; i++){
		int x = read(), y = read();
		printf("%d\n", LCA(x, y));
	}
	return 0;
}