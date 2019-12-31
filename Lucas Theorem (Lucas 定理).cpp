#include <bits/stdc++.h>
using namespace std;

template <typename type>
class Combination {
 private:
    static constexpr size_t N = 1e5 + 23;

 protected:
    type fct[N], inv[N], fctinv[N];

    void prepare(type n, type P){
        fctinv[0] = fctinv[1] = 1;
        fct[0] = inv[1] = fct[1] = 1;
        for (int i = 2; i <= n; ++i){
            fct[i] = 1ll * fct[i - 1] * i % P;
            inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
            fctinv[i] = 1ll * fctinv[i - 1] * inv[i] % P;
        }
    }

    type combine(type n, type m, type P){
        if (m == 0 || n == m) return 1;
        return 1ll * fct[n] * fctinv[m] % P * fctinv[n - m] % P;
    }

    void display(type n, type P){
        cerr << "Process succeeded." << endl;
        for (int i = 0; i <= n; i++){
            for (int j = 0; j <= i; j++)
                cout << combine(i, j, P) << (char)32;
            cout << endl;
        }
    }

 public:
    ~Combination(){}
};

template <typename type>
class LucasTheorem : public Combination<type> {
 private:
    type P, n, m, val;

 protected:
    type Lucas(type n, type m){
        if (m == 0) return 1;
        return 1ll * this->combine(n % P, m % P, P) * Lucas(n / P, m / P) % P;
    }

 public:
    LucasTheorem(type n, type m, type P) : n(n), m(m), P(P) { }

    ~LucasTheorem(void){}

    void solve(void){
        this->prepare(P - 1, P);
        // this->display(P - 1, P);
        val = Lucas(n, m);
    }

    void reset(type new_n, type new_m, type new_P){
        n = new_n, m = new_m, P = new_P;
        solve();
    }

    type answer(void){return val;}
};

LucasTheorem<int> p(0, 0, 1);

int main(){
    return 0;
}