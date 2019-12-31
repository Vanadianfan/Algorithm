#include<vector>
#include<cstdio>
#include<climits>
#include<iostream>
#include<algorithm>
using namespace std;
#define lch (p << 1)
#define rch (p << 1 | 1)
const int N = 2e5 + 23;
int n, m, root, tim;
inline void read(int &w){
	w = 0; char c = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) w = (w << 3) + (w << 1) + c - '0', c = getchar();
}
vector<int> subT[N];
int key[N], dep[N], size[N], f[N];
int PC[N], dfn[N], top[N], *poi[N];
struct SegmentTree{
	int l, r;
	long long sum, lazy;
	#define l(x) __ST[x].l
	#define r(x) __ST[x].r
	#define sum(x) __ST[x].sum
	#define lazy(x) __ST[x].lazy
}__ST[N << 2];
void prepare(int x, int k, int pre){
	size[x] = 1; f[x] = pre, dep[x] = k;
	vector<int>::iterator y = subT[x].begin();
	for(; y != subT[x].end(); y++){
		if(*y == pre) continue;
		prepare(*y, k + 1, x);
		size[x] += size[*y];
		if(size[*y] > size[PC[x]]) PC[x] = *y;
	}
}
void decompose(int x, int topf){
	dfn[x] = ++tim;
	top[x] = topf;
	poi[tim] = &key[x];
	if(PC[x] == 0) return;
	decompose(PC[x], topf);
	vector<int>::iterator y = subT[x].begin();
	for(; y != subT[x].end(); y++)
		if(*y != PC[x] && *y != f[x]) decompose(*y, *y);
}
int LCA(int x, int y){
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = f[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	return x;
}
void establish(int p, int l, int r){
	l(p) = l, r(p) = r;
	if(l == r){
		lazy(p) = 0;
		sum(p) = *poi[l];
		return;
	}
	int mid = (l + r) >> 1;
	establish(lch, l, mid);
	establish(rch, mid + 1, r);
	sum(p) = sum(lch) + sum(rch);
}
void below_spread(int p){
	if(lazy(p)){
		sum(lch) += (long long)(r(lch) - l(lch) + 1) * lazy(p);
		sum(rch) += (long long)(r(rch) - l(rch) + 1) * lazy(p);
		lazy(lch) += lazy(p);
		lazy(rch) += lazy(p);
		lazy(p) = 0;
	}
}
void modify(int p, int l, int r, int d){
	if(l <= l(p) && r >= r(p)){
		lazy(p) += (long long)d;
		sum(p) += (long long)(r(p) - l(p) + 1) * d;
		return;
	}
	below_spread(p);
	int mid = (l(p) + r(p)) >> 1;
	if(l <= mid) modify(lch, l, r, d);
	if(r >  mid) modify(rch, l, r, d);
	sum(p) = sum(lch) + sum(rch);
}
long long query(int p, int l, int r){
	if(l <= l(p) && r >= r(p)) return sum(p);
	below_spread(p);
	int mid = (l(p) + r(p)) >> 1;
	long long val = 0;
	if(l <= mid) val += query(lch, l, r);
	if(r >  mid) val += query(rch, l, r);
	return val;
}
long long statistic(int x, int y){
	long long val = 0;
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		val += query(1, dfn[top[x]], dfn[x]);
		x = f[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	return val += query(1, dfn[x], dfn[y]);
}
void add(int x, int y, int z){
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		modify(1, dfn[top[x]], dfn[x], z);
		x = f[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	modify(1, dfn[x], dfn[y], z);
}
int main(){
	size[0] = INT_MIN;
	scanf("%d%d", &n, &m); root = 1;
	for(int i = 1; i <= n; i++) read(key[i]);
	for(int i = 1; i < n; i++){
		int x, y; read(x), read(y);
		subT[x].emplace_back(y);
		subT[y].emplace_back(x);
	}
	prepare(root, 1, -1);
	decompose(root, root);
	establish(1, 1, n);
	for(; m; m--){
		int op, x, y, z; read(op), read(x);
		switch(op){
			case 1: read(y); read(z), add(x, y, z); break;
			case 2: read(y); printf("%lld\n", statistic(x, y)); break;
			case 3: read(z); modify(1, dfn[x], dfn[x] + size[x] - 1, z); break;
			case 4: printf("%lld\n", query(1, dfn[x], dfn[x] + size[x] - 1));
		}
	}
	return 0;
}