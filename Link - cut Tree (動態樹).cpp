#include<cstdio>
#include<iostream>
using namespace std;
inline void read(int &w){
	w = 0; char c = 0; bool f = false;
	while(!isdigit(c)){if(c == '-') f = true; c = getchar();}
	while(isdigit(c)) w = (w << 3) + (w << 1) + c - '0', c = getchar();
	if(f) w = -w;
}
namespace LINK_CUT_TREE{
	const int MAXN = 3e5 + 23;
	struct Node{
		int key, prf;
		bool reverse;
		Node *lst, *rst, *pre;
		bool isLsubT(){return this == this->pre->lst;}
		void InfoUpdate(){this->prf = lst->prf + rst->prf + this->key;}
		void BelowSpread(){
			if(this->reverse){
				swap(lst, rst);
				this->lst->reverse ^= 1;
				this->rst->reverse ^= 1;
				this->reverse = false;
			}
		}
	};
	class Link_cut_Tree{
	protected:
		Node MemoryPool[MAXN];
		Node *tail, *null;
		void NewNode(int key){
			Node *x = tail++;
			x->reverse = false;
			x->prf = x->key = key;
			x->pre = x->lst = x->rst = null;
		}
		bool isRoot(Node *x){
			if(x->pre == null) return true;
			return x->pre->lst != x && x->pre->rst != x;
		}
		void Rotate(Node *x){
			Node *y = x->pre, *z = y->pre;
			int k = x->isLsubT();
			if(!isRoot(y)){
				if(y->isLsubT()) z->lst = x;
				else z->rst = x;
			}
			x->pre = z;
			if(k) y->lst = x->rst, x->rst->pre = y;
			else y->rst = x->lst, x->lst->pre = y;
			if(k) x->rst = y; else x->lst = y;
			y->pre = x; y->InfoUpdate();
		}
		void Splay(Node *x){
			static Node *stk[MAXN];
			int top = 1; stk[top] = x;	
			while(!isRoot(stk[top])) stk[top + 1] = stk[top]->pre, ++top;		
			while(top) stk[top--]->BelowSpread();
			while(!isRoot(x)){
				Node *y = x->pre;
				if(!isRoot(y))
					Rotate(x->isLsubT() == y->isLsubT() ? y : x);
				Rotate(x);
			}
			x->InfoUpdate();
		}
		void access(Node *cur){
			Node *last = null;
			while(cur != null){
				Splay(cur);
				cur->rst = last;
				cur->InfoUpdate();
				last = cur, cur = cur->pre;
			}
		}
		void MakeRoot(Node *x){
			access(x);
			Splay(x);
			x->reverse ^= 1;
		}
		Node *FindRoot(Node *cur){
			access(cur);
			Splay(cur);
			while(cur->BelowSpread(), cur->lst != null)
				cur = cur->lst;
			Splay(cur);
			return cur;
		}
		void link(Node *x, Node *y){
			if(FindRoot(x) == FindRoot(y)) return;
			MakeRoot(y);
			y->pre = x;
		}
		void cut(Node *x, Node *y){
			MakeRoot(x);
			access(y);
			Splay(y);
			if(y->lst == x)
				y->lst = x->pre = null;
		}
		int query(Node *x, Node *y){
			MakeRoot(x);
			access(y);
			Splay(y);
			return y->prf;
		}
		void update(Node *x, int val){
			Splay(x);
			x->key = val;
			x->InfoUpdate();
		}
	public:
		Link_cut_Tree(){
			null = tail = MemoryPool;
			NewNode(0);
		}
		void INITIALISE(int key){NewNode(key);}
		void LINK(int x, int y){link(MemoryPool + x, MemoryPool + y);}
		void CUT(int x, int y){cut(MemoryPool + x, MemoryPool + y);}
		int QUERY(int x, int y){return query(MemoryPool + x, MemoryPool + y);}
		void UPDATE(int x, int y){update(MemoryPool + x, y);}
	};
}
using namespace LINK_CUT_TREE;
Link_cut_Tree __LC_T;
int main(){
	int n, m; cin >> n >> m;
	for(int i = 1; i <= n; i++){
		int key; read(key);
		__LC_T.INITIALISE(key);
	}
	while(m--){
		int op, x, y;
		read(op), read(x), read(y);
		switch(op){
			case 0: printf("%d\n", __LC_T.QUERY(x, y)); break;
			case 1: __LC_T.LINK(x, y); break;
			case 2: __LC_T.CUT(x, y); break;
			case 3: __LC_T.UPDATE(x, y);
		}
	}
	return 0;
}