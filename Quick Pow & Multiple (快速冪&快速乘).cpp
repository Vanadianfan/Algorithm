#include<cstdio>
#include<iostream>
using namespace std;
long long pow(long long a, long long b, long long mod){
	long long s = 1; a %= mod;
	while(b != 0){
		if(b & 1) s = s * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return s;
}
long long multiple(long long a, long long b, long long mod){
	long long s = 0; a %= mod;
	while(b != 0){
		if(b & 1) s = (s + a) % mod;
		s = (s << 1) % mod, b >>= 1;
	}
	return s;
}
inline long long qmul(long long a, long long b, long long mod){
	a = (a % mod + mod) % mod;
	b = (b % mod + mod) % mod;
	long long c = a * (long double)b / mod;
	long long ans = a * b - c * mod;
	if(ans < 0) ans += mod;
	else if(ans >= mod) ans -= mod;
	return ans;
}
int main(){
	long long a, b, c;
	cin >> a >> b >> c; // Only when b != 0
	cout << "pow: " << pow(a, b, c) << endl;
	cout << "mul: " << multiple(a, b, c) << endl;
	cout << "qml: " << qmul(a, b, c) << endl;
	return 0;
}