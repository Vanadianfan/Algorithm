#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 100010, M = 1000010;
vector<int> fore[N];
int n, m, tot, tms, top, scc;
int hd[N], ver[M], Next[M];
int stack[N], ins[N], c[N], dfn[N], low[N];
inline void access(int x, int y){
	ver[++tot] = y, 
	Next[tot] = hd[x], hd[x] = tot;
}
inline int read(void){
	char c = 0; int f = 1, x = 0;
	while(!isdigit(c)){if(c == '-') f = -f; c = getchar();}
	while(isdigit(c)) x = ((x + (x << 2)) << 1) + (c ^ 48), c = getchar();
	x *= f;
}
void tarjan(int x){
	dfn[x] = low[x] = ++tms;
	stack[++top] = x, ins[x] = 1;
	for(int i = hd[x]; i; i = Next[i]){
		int y = ver[i];
		if(!dfn[y]) tarjan(y), low[x] = min(low[x], low[y]);
		else if(ins[y]) low[x] = min(low[x], dfn[y]);
	}
	if(dfn[x] == low[x]){
		scc++; int y;
		do{
			y = stack[top--], ins[y] = 0;
			c[y] = scc, fore[scc].push_back(y);
		}while(x != y);
	}
}
int main(){
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int x = read(), y = read();
		access(x, y);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= scc; i++){
		for(auto j : fore[i])
			cout << j << (char)32;
		cout << endl;
	}
	return 0;
}