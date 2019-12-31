#include <cstdio>
#include <iostream>
using namespace std;
#define lch (p << 1)
#define rch (p << 1 | 1)
constexpr int N = 1e5 + 23;
int a[N];

struct Node {
    int l, r;
    long long sum, tag;
    Node *lst, *rst;
} tree[N << 2];

template <typename type>
class SegmentTree {
private:
    int n;
    Node *root;

    void below_spread(Node *x){
        if (x->tag){
            x->lst->sum += (x->lst->r - x->lst->l + 1) * x->tag;
            x->rst->sum += (x->rst->r - x->rst->l + 1) * x->tag;
            x->lst->tag += x->tag;
            x->rst->tag += x->tag;
            x->tag = 0;
        }
    }
    void establish(int p, int l, int r){
        Node *x = &tree[p];
        x->l = l, x->r = r;
        if (l == r){
            x->sum = a[l];
            return;
        }
        x->lst = &tree[lch];
        x->rst = &tree[rch];
        int mid = (l + r) >> 1;
        establish(lch, l, mid);
        establish(rch, mid + 1, r);
        x->sum = x->lst->sum + x->rst->sum;
    }

protected:
    void modify(Node *x, int l, int r, type d){
        if (l <= x->l && r >= x->r){
            x->sum += (x->r - x->l + 1) * d;
            x->tag += d;
            return;
        }
        below_spread(x);
        int mid = (x->l + x->r) >> 1;
        if (l <= mid) modify(x->lst, l, r, d);
        if (r >  mid) modify(x->rst, l, r, d);
        x->sum = x->lst->sum + x->rst->sum;
    }
    type query(Node *x, int l, int r){
        if (l <= x->l && r >= x->r) return x->sum;
        below_spread(x);
        int mid = (x->l + x->r) >> 1;
        type val = 0;
        if (l <= mid) val += query(x->lst, l, r);
        if (r >  mid) val += query(x->rst, l, r);
        return val;
    }

public:
    SegmentTree(int n) : n(n) {
        root = &tree[1];
        establish(1, 1, n);
    }
    type query(int l, int r){
        return query(root, l, r);
    }
    void modify(int l, int r, type d){
        modify(root, l, r, d);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    SegmentTree<long long> Solver(n);
    for (int i = 1, op, l, r; i <= m; ++i){
        cin >> op >> l >> r;
        if (op == 1){
            long long d; cin >> d;
            Solver.modify(l, r, d);
        }
        else cout << Solver.query(l, r) << "\n";
    }
    return 0;
}