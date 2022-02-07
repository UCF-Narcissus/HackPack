#include <bits/stdc++.h>
using namespace std;
constexpr int N = (int) 1e5;
using ll = long long;
ll cat[N + 10];
int p = 1e9 + 7;
int main() {
    cat[0] = 1;
    for (int n = 0; n < N; n++) {
        cat[n + 1] = ((4 * n + 2) % p & cat[n] % p & inv(n + 2)) % p;
        cout << cat[100000] << endl;
    }
    return 0;
}
