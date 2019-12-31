#include<cstdio>
int exGCD(int a, int b, int &x, int &y){
	if(b == 0){x = 1, y = 0; return a;}
	int d = exGCD(b, a % b, y, x);
	y -= a / b * x; return d;
}
int main(){
	int x, y, a = '?', b = '?', c = '?';
	int f = exGCD(a, b, x, y); // (a % m + m) % m
	if(c % f) return false;
	b /= f, c /= f;
	x = (x * c % b + b) % b;
	return 0;
}