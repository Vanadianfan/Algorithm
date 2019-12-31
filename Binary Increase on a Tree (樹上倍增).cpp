#include <iostream>
#include <algorithm>
constexpr int N = 5e5 + 23;
int n, m, root, lg[N], f[N][39], dep[N];

struct Edge {
	int ver;
	Edge *Next;
};
Edge *tail, *null;
Edge *head[N], edge[N << 1];

Edge *NewEdge(int vertax){
	Edge *x = tail++;
	x->ver = vertax;
	return x;
}
void PointerPrepare(void){
	tail = edge;
	null = tail++;
	for (int i = 1; i <= n; ++i) head[i] = null;
}
inline void access(int x, int y){
	Edge *ww = NewEdge(y);
	ww->Next = head[x], head[x] = ww;
}

void BinaryPrepare(int x, int pre){
	f[x][0] = pre;
	dep[x] = dep[pre] + 1;
	for (int i = 1; i <= lg[dep[x]]; ++i) f[x][i] = f[f[x][i - 1]][i - 1];
	for (Edge *i = head[x]; i != null; i = i->Next)
		if (i->ver != pre) BinaryPrepare(i->ver, x);
}
int LCA(int x, int y){
	if (dep[x] < dep[y]) std::swap(x, y);
	while (dep[x] > dep[y]) x = f[x][lg[dep[x] - dep[y]] - 1];
	if (x == y) return x;
	for (int k = lg[dep[x]]; ~k; --k)
		if (f[x][k] != f[y][k]) x = f[x][k], y = f[y][k];
	return f[x][0];
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cin >> n >> m >> root;
	PointerPrepare();
	for (int i = 1, x, y; i < n; ++i){
		std::cin >> x >> y;
		access(x, y); access(y, x);
	}
	for (int i = 1; i <= n; ++i)
		lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
	BinaryPrepare(root, 0);
	for (int i = 1, x, y; i <= m; ++i){
		std::cin >> x >> y;
		std::cout << LCA(x, y) << "\n";
	}
	return 0;
}