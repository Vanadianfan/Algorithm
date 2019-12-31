#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 100023
#define trial (val < cur->key ? cur->lst : cur->rst)

template <typename type>
class SplayTree {
private:
    type pINF, nINF;  // positive infinity, negative infinity.
    struct Node {
        type key;
        size_t weight, size;
        Node *lst, *rst, *pre;
        bool isLsubT(){ return this == this->pre->lst; }
        void InfoUpdate(){this->size = lst->size + rst->size + this->weight;}
    };
    Node MemoryPool[MAXN];
    Node *root, *tail, *null;
    Node *bin[MAXN]; int bin_top;
    Node *NewNode(type key){
        Node *x = bin_top ? bin[--bin_top] : tail++;
        x->key = key;
        x->weight = x->size = 1;
        x->pre = x->lst = x->rst = null;
        return x;
    }
    void PointerPrepare(void){
        tail = MemoryPool;
        null = tail++;
        null->weight = null->size = 0;
        null->lst = null->rst = null;
        root = null, bin_top = 0;
    }

    void Midorder(Node *cur){
        if (cur == null) return;
        if (cur->key == nINF || cur->key == pINF) return;
        Midorder(cur->lst);
        for(int i = 0; i < cur->weight; ++i)
            cout << cur->key << endl;
        Midorder(cur->rst);
    }
    void Clear(Node *x){
        if (x == null) return;
        Clear(x->lst);
        Clear(x->rst);
        bin[bin_top++] = x;
    }

protected:
    void Rotate(Node *x){
        Node *y = x->pre, *z = y->pre;
        bool k = x->isLsubT();
        if (y->isLsubT()) z->lst = x; else z->rst = x;
        x->pre = z;
        if (k) y->lst = x->rst, x->rst->pre = y;
        else y->rst = x->lst, x->lst->pre = y;
        if (k) x->rst = y; else x->lst = y;
        y->pre = x; y->InfoUpdate();
    }
    void Splay(Node *x, Node *ter){
        while (x->pre != ter){
            Node *y = x->pre;
            if (y->pre != ter)
                Rotate(x->isLsubT() == y->isLsubT() ? y : x);
            Rotate(x);
        }
        x->InfoUpdate();
        if (ter == null) root = x;
    }
    void Search(type val){
        if (root == null) return;
        Node *cur = root;
        while (val != cur->key){
            Node *Next = trial;
            if (Next == null) break;
            cur = Next;
        }
        Splay(cur, null);
    }

public:
    SplayTree(void){  // default to int or long long int.
        PointerPrepare();
        memset(&pINF, 0x3f, sizeof(pINF));
        memset(&nINF, -0x3f, sizeof(nINF));
        Insert(pINF), Insert(nINF);
    }
    SplayTree(type _MIN, type _MAX) : pINF(_MAX), nINF(_MIN) {  // for other type, custom limits.
        PointerPrepare();
        Insert(pINF), Insert(nINF);
    }

    size_t size(void){
        return root->size - 2;
    }
    void Clear(void){
        Clear(root); root = null;
        Insert(nINF), Insert(pINF);
    }
    void OrderDisplay(void){
        Midorder(root);
        cout << endl;
    }

    size_t CalculateRank(type val){
        Search(val);
        return root->lst->size;
    }
    Node *RankLocate(size_t k){
        ++k;
        Node *cur = root;
        while (true){
            if (k <= cur->lst->size) cur = cur->lst;
            else if (k > cur->lst->size + cur->weight){
                k -= cur->lst->size + cur->weight;
                cur = cur->rst;
            }
            else return cur;
        }
    }

    Node *ForewardNode(type val){
        Search(val);
        if (root->key < val) return root;
        Node *cur = root->lst;
        while (cur->rst != null) cur = cur->rst;
        return cur;
    }
    type ForewardValue(type val){
        Search(val);
        if (root->key < val) return root->key;
        Node *cur = root->lst;
        while (cur->rst != null) cur = cur->rst;
        return cur->key;
    }
    Node *BackwardNode(type val){
        Search(val);
        if (root->key > val) return root;
        Node *cur = root->rst;
        while (cur->lst != null) cur = cur->lst;
        return cur;
    }
    type BackwardValue(type val){
        Search(val);
        if (root->key > val) return root->key;
        Node *cur = root->rst;
        while (cur->lst != null) cur = cur->lst;
        return cur->key;
    }

    void Insert(type val){
        Node *cur = root, *f = null;
        while (cur != null && val != cur->key)
            f = cur, cur = trial;
        if (cur != null) ++cur->weight;
        else {
            cur = NewNode(val);
            if (f != null){
                val > f->key ? f->rst : f->lst = cur;
                cur->pre = f;
            }
        }
        Splay(cur, null);
    }
    void EraseViaValue(type val){
        Node *lst = ForewardNode(val);
        Node *nxt = BackwardNode(val);
        Splay(lst, null), Splay(nxt, lst);
        Node *cur = nxt->lst;
        if (cur->weight > 1) --cur->weight, Splay(cur, null);
        else Clear(nxt->lst), nxt->lst = null;
    }
};

#undef MAXN
#undef trial

SplayTree<int> SPT;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m; cin >> m;
    for (; m; --m){
        int op, x; cin >> op >> x;
        if (op == 1) SPT.Insert(x);
        if (op == 2) SPT.EraseViaValue(x);
        if (op == 3) cout << SPT.CalculateRank(x) << "\n";
        if (op == 4) cout << SPT.RankLocate(x)->key << "\n";
        if (op == 5) cout << SPT.ForewardValue(x) << "\n";
        if (op == 6) cout << SPT.BackwardValue(x) << "\n";
        // SPT.OrderDisplay();
    }
    return 0;
}