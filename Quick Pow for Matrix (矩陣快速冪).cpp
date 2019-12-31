#include<cstring>
#include<iostream>
constexpr int N = 123;
constexpr int mod = 1e9 + 7;
using namespace std;
int n;
struct Matrix {
	long long mt[N][N];
	Matrix(){memset(mt, 0, sizeof(mt));}
	Matrix operator * (const Matrix &b) const {
		Matrix c;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				for(int k = 1; k <= n; k++)
					(c.mt[i][j] += mt[i][k] * b.mt[k][j] % mod) %= mod;
		return c;
	}
	Matrix operator *= (const Matrix &b){
		*this = *this * b;
		return *this;
	}
}a, e;
Matrix pow(Matrix a, long long b){
	Matrix s = e;
	while(b){
		if(b & 1) s = s * a;
		a *= a, b >>= 1;
	}
	return s;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	long long k; cin >> n >> k;
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= n; j++)
		cin >> a.mt[i][j];
	for(int i = 1; i <= n; i++) e.mt[i][i] = 1;
	
	return 0;
}