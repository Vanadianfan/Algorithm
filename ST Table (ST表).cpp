#include <iostream>
#include <algorithm>
using namespace std;
constexpr int N = 1e5 + 23, K = 39;
int n, m, lg[N], f[N][K];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, a; i <= n; i++) cin >> f[i][0];
    for (int i = 1; i <= n; ++i) lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    for (int j = 1; j < lg[n]; j++)
    for (int i = 1; i <= n - (1 << j) + 1; i++)
        f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    for (int i = 1, l, r; i <= m; i++){
        cin >> l >> r;
        int p = lg[r - l + 1] - 1;
        cout << max(f[l][p], f[r - (1 << p) + 1][p]) << "\n";
    }
    return 0;
}