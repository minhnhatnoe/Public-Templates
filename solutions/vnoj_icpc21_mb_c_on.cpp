// The solution described at: https://en.wikipedia.org/wiki/Autocorrelation_%28words%29
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;
    while (q--){
        string a; cin >> a;
        vector<int> pf(a.size());
        for (int i=1; i<a.size(); i++){
            int ptr = pf[i-1];
            while (ptr && a[ptr] != a[i]) ptr = pf[ptr-1];
            pf[i] = ptr + (a[i] == a[ptr]);
        }
        ll result = 0;
        for (int ptr = a.size(); ptr; ptr = pf[ptr-1])
            result += 1LL<<ptr;
        cout << result << "\n";
    }
}
