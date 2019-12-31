#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
inline void read(int &w){
	w = 0; char c = 0; int f = 1;
	while(!isdigit(c)){if(c == '-') f = -f; c = getchar();}
	while(isdigit(c)) w = (w << 3) + (w << 1) + c - '0', c = getchar(); w *= f;
}
namespace Scapegoat_Tree{
	#define MAXN 100023
	const double law = 0.75;
	struct Node{
		bool exist;
		Node *lst, *rst;
		int key, size, cover;
		void InfoUpdate(void){
			size = lst->size + rst->size + (int)exist;
			cover = lst->cover + rst->cover + 1;
		}
		bool StatusJudge(void){
			return lst->cover > cover * law + 5 || rst->cover > cover * law + 5;
		}
	};
	class ScapegoatTree{
	protected:
		Node MemoryPoor[MAXN];
		Node *root, *tail, *null;
		Node *bin[MAXN]; int bin_top;
		Node *NewNode(int key){
			Node *x = bin_top ? bin[--bin_top] : tail++;
			x->key = key;
			x->exist = true;
			x->lst = x->rst = null;
			x->size = x->cover = 1;
			return x;
		}
		void Creep(Node *cur, vector<Node *> &v){
			if(cur == null) return;
			Creep(cur->lst, v);
			if(cur->exist) v.emplace_back(cur);
			else bin[bin_top++] = cur;
			Creep(cur->rst, v);
		}
		Node *Split(vector<Node *> &v, int l, int r){
			if(l >= r) return null;
			int mid = (l + r) >> 1;
			Node *cur = v[mid];
			cur->lst = Split(v, l, mid);
			cur->rst = Split(v, mid + 1, r);
			cur->InfoUpdate();
			return cur;
		}
		void Reestablish(Node *&cur){
			static vector<Node *> v; v.clear();
			Creep(cur, v); cur = Split(v, 0, v.size());
		}
		void PrintMidorder(Node *cur){
			if(cur == null) return;
			PrintMidorder(cur->lst);
			cout << cur->key << (char)32;
			PrintMidorder(cur->rst);
		}
		Node **Insert(Node *&cur, int val){
			if(cur == null){
				cur = NewNode(val);
				return &null;
			}
			++cur->size, ++cur->cover;
			Node **oca = Insert((val < cur->key ? cur->lst : cur->rst), val);
			if(cur->StatusJudge()) oca = &cur;
			return oca;
		}
		void Erase(Node *cur, int rank){
			cur->size--;
			int offset = cur->lst->size + cur->exist;
			if(cur->exist && rank == offset){
				cur->exist = false;
				return;
			}
			if(rank <= offset) Erase(cur->lst, rank);
			else Erase(cur->rst, rank - offset);
		}
	public:
		ScapegoatTree(void){
			tail = MemoryPoor;
			null = tail++;
			null->lst = null->rst = null;
			null->cover = null->size = null->key = 0;
			root = null, bin_top = 0;
		}
		void Insert(int val){
			Node **x = Insert(root, val);
			if(*x != null) Reestablish(*x);
		}
		void PrintMidorder(void){
			PrintMidorder(root);
			cout << endl;
		}
		int Calculate_Rank(int val){
			Node *cur = root;
			int sum = 1;
			while(cur != null){
				if(cur->key >= val) cur = cur->lst;
				else{
					sum += cur->lst->size + cur->exist;
					cur = cur->rst;
				}
			}
			return sum;
		}
		int Rank_Locate(int k){
			Node *cur = root;
			while(cur != null){
				if(cur->lst->size + 1 == k && cur->exist) return cur->key;
				if(cur->lst->size >= k) cur = cur->lst;
				else k -= cur->lst->size + cur->exist, cur = cur->rst;
			}
			return 0;
		}
		int Foreward(int val){
			return Rank_Locate(Calculate_Rank(val) - 1);
		}
		int Backward(int val){
			return Rank_Locate(Calculate_Rank(val + 1));
		}
		void Erase_via_Value(int val){
			Erase(root, Calculate_Rank(val));
			if(root->size < law * root->cover) Reestablish(root);
		}
		void Erase_via_Rank(int k){
			Erase(root, k);
			if(root->size < law * root->cover) Reestablish(root);
		}
	};
	#undef MAXN
}
using namespace Scapegoat_Tree;
ScapegoatTree __SG__T;
int main(){
	// ios::sync_with_stdio(false);
	int m; cin >> m;
	for(; m; m--){
		int op, x; // cin >> op >> x;
		read(op), read(x);
		switch(op){
			case 1: __SG__T.Insert(x); break;
			case 2: __SG__T.Erase_via_Value(x); break;
			case 3: printf("%d\n", __SG__T.Calculate_Rank(x)); break;
			case 4: printf("%d\n", __SG__T.Rank_Locate(x)); break;
			case 5: printf("%d\n", __SG__T.Foreward(x)); break;
			case 6: printf("%d\n", __SG__T.Backward(x));
		}
	}
	return 0;
}