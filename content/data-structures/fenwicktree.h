/**
 * Description: Binary Indexed Tree to support logarithmic complexity on
 * point update and range query
 * Time: $ O(log(M)) $ update/query, $ O(nlog(n)) $ build
 * Memory: $ O(N) $
 */
#define lso(x) ((x) & -(x))
class bit {
    public:
        int n;
        vector<ll> ft;
        bit(int n) {
            this->n = n;
            ft.resize(n + 1);
            fill(ft.begin(), ft.end(), 0);
        }
        void update(int i, int val) {
            for (; i < (int) ft.size(); i += lso(i))
                ft[i] += val;
        }
        ll rsq(int i) {
            ll ret = 0;
            for (; i; i -= lso(i))
                ret += ft[i];
            return ret;
        }
        ll rsq(int i, int j) {
            return rsq(j) - rsq(i - 1);
        }
};
