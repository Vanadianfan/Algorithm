#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define lowbit(x) (x & -x)
const int N = 1027;
int n, m, e[N][N];
void Modify(int x, int y, int val){
    for(int i = x; i <= n; i += lowbit(i))
        for(int j = y; j <= m; j += lowbit(j))
			e[x][y] += val;
}
int ask(int x, int y){
	int ans = 0;
    for(int i = x; i; i -= lowbit(i))
        for(int j = y; j; j -= lowbit(j))
			ans += e[x][y];
	return ans;
}
inline int Query(int x1, int y1, int x2, int y2){// Defaut: x1 <= x2, y1 <= y2.
	return ask(x2, y2) - ask(x1 - 1, y2) - ask(x2, y1 - 1) + ask(x1 - 1, y1 - 1);
}