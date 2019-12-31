#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int fail[1023];
void prepare(char *s, char *p){
    int k = fail[1] = 0;
    int lp = strlen(p + 1);
    for (int i = 1; i < lp; ++i){
        while (k > 0 && p[i + 1] != p[k + 1]) k = fail[k];
        if (p[i + 1] == p[k + 1]) ++k;
        fail[i + 1] = k;
    }
}
void KMP(char *s, char *p){  // Knuth - Morris - Pratt Algorithm
    int j = 0;
    int ls = strlen(s + 1), lp = strlen(p + 1);
    for (int i = 0; i < ls; ++i){
        while (j > 0 && s[i + 1] != p[j + 1]) j = fail[j];
        if (s[i + 1] == p[j + 1]) ++j;
        if (j == lp){
            printf("%d ", i + 1 - lp + 1);
            j = fail[j];
        }
    }
}
int main(){
    char s[1023], p[1023];
    scanf("%s%s", s + 1, p + 1);
}