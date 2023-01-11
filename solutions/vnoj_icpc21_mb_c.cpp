#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
vector<ld> gauss(vector<vector<ld>> &a){
    const ld EPS = 1e-9;
    for (int i=0; i<a.size(); i++){
        bool swapped = false;
        for (int j=i; j<a.size() && !swapped; j++){
            if (abs(a[j][i]) < EPS) continue;
            swap(a[i], a[j]);
            swapped = true;
        }
        assert((swapped));
        assert((abs(a[i][i]) >= EPS));
        for (int j=0; j<a.size(); j++){
            if (i == j) continue;
            if (abs(a[j][i]) < EPS) continue;
            long double coef = a[j][i] / a[i][i];
            for (int k=i; k<a[0].size(); k++){
                a[j][k] -= a[i][k] * coef;
            }
        }
    }
    vector<ld> result(a.size());
    for (int i=0; i<a.size(); i++){
        result[i] = -a[i].back()/a[i][i];
    }
    return result;
}
vector<int> prefix_function(const string &a){
    vector<int> pf(a.size());
    pf[0] = 0;
    for (int i=1; i<a.size(); i++){
        int ptr = pf[i-1];
        while (ptr != 0 && a[ptr] != a[i]) ptr = pf[ptr-1];
        pf[i] = ptr + (a[ptr] == a[i]);
    }
    return pf;
}
vector<int[2]> kmp_automaton(const string &a){
    vector<int> pf = prefix_function(a);
    vector<int[2]> result(a.size());
    for (int c=0; c<2; c++)
        result[0][c] = (a[0] == '0' + c);

    for (int i=1; i<a.size(); i++){
        for (int c=0; c<2; c++){
            if (a[i] == '0' + c) result[i][c] = i+1;
            else result[i][c] = result[pf[i-1]][c];
        }
    }
    return result;
}
long double solve(string &a){
    vector<int[2]> aauto = kmp_automaton(a);
    vector<vector<ld>> g(a.size()+1, vector<ld> (a.size()+2));
    for (int i=0; i<a.size(); i++){
        g[i][aauto[i][0]] += -1;
        g[i][aauto[i][1]] += -1;

        g[i][i] += 2;
        g[i][a.size()+1] += -2;
    }
    g[a.size()][a.size()] = 1;
    return gauss(g)[0];
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    cout << setprecision(10);
    while (t--){
        string a; cin >> a;
        cout << solve(a) << "\n";
    }
}
