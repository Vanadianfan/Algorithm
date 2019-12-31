#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
struct node{
	int count;
	node *next[26];
}*root;
node *build(){
	node *k = new node;
	k->count = 0;
	memset(k->next, 0, sizeof(k->next));
	return k;
}
void insert(char *s){
	node *r = root;
	char *word = s;
	while(*word){
		int id = *word - 'a';
		if(r->next[id] == NULL)
			r->next[id] = build();
		r = r->next[id];
		r->count++;
		word++;
	}
}
int search(char *s){
	node *r = root;
	char *word = s;
	while(*word){
		int id = *word - 'a';
		r = r->next[id];
		if (r == NULL) return 0;
		word++;
	}
	return r->count;
}
int main(){
	int n;
	char host[1023];
	root = build();
	scanf("%s%d", host, &n);
	for(int i=0; i<n; i++){
		char s[1023];
		scanf("%s",s);
		insert(s);
	}
	printf("%d\n", search(host));
	return 0;
}