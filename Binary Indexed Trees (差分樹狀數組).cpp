#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N = 5e5 + 23;
#define lowbit(x) (x & -x)
int n, m, pre, cur, e[N], epd[N];
void modify(int x, int val){
	for(int v = x; x <= n; x += lowbit(x))
		e[x] += val, epd[x] += val * v;
}
int SpotQuery(int x){
	int ans = 0;
	for(; x; x -= lowbit(x))
		ans += e[x];
	return ans;
}
inline void SpotModify(int x, int val){
	modify(x, val);
	modify(x + 1, -1 * val);
	/* an UNPLEASANT trial... 
	int v = x, k = x + lowbit(x);
	e[x] += val, epd[x] += x *val;
	for(x += 1; x != k; x += lowbit(x))
		e[x] -= val, epd[x] -= val * (v + 1);
	for(x = k; x <= n; x += lowbit(x))
		epd[x] -= val; */
}
inline void IntervalModify(int l, int r, int val){
	modify(l, val);
	modify(r + 1, -1 * val);
}
int ask(int x){
	int ans = 0;
	for(int v = x + 1; x; x -= lowbit(x))
		ans += v * e[x] - epd[x];
	return ans;
}
inline int IntervalQuery(int l, int r){
	return ask(r) - ask(l - 1);
}
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		scanf("%d", &cur);
		modify(i, cur - pre);
		pre = cur;
	}
}