#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N = 1e7 + 23;
bool isprime[N];
int n, tot, phi[N], prime[N];
void SieveOfEuler(int n){
	memset(isprime + 2, true, sizeof(isprime));
	for(int i = 2; i <= n; i++){
		if(isprime[i]) prime[++tot] = i, phi[i] = i - 1;
		for(int j = 1; j <= tot && i * prime[j] <= n; j++){
			int p = prime[j]; isprime[i * p] = false;
			if(!(i % p)){phi[i * p] = phi[i] * p; break;}
			else phi[i * p] = phi[i] * phi[p];
		}
	}
}