#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N = 2e5 + 23;
#define lowbit(x) (x & -x)
int n, m, e[N], sum[N];
void SpotModify(int x, int val){
	for(; x <= n; x += lowbit(x))
		e[x] += val;
}
int SpotQuery(int x){
	int ans = e[x], k = x - lowbit(x);
	for(x -= 1; x != k; x -= lowbit(x))
		ans -= e[x];
	return ans;
}
int ask(int x){
	int ans = 0;
	for(; x; x -= lowbit(x))
		ans += e[x];
	return ans;
}
inline int IntervalQuery(int l, int r){
	return ask(r) - ask(l - 1);
}
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		scanf("%d", sum + i);
		sum[i] += sum[i - 1];
		e[i] = sum[i] - sum[i - lowbit(i)];
	}
}