#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s1, s2, av;
vector<array<vector<int>, 26>> g;

vector<int> prefix(const string &a){
    vector<int> pf(a.size());
    for (int i=1; i<pf.size(); i++){
        int ptr = pf[i-1];
        while (ptr && a[ptr] != a[i]) ptr = pf[ptr-1];
        pf[i] = ptr + (a[ptr] == a[i]);
    }
    return pf;
}
vector<array<int, 26>> kmp_auto(const string &a){
    vector<int> pf = prefix(a);
    vector<array<int, 26>> result(a.size());
    result[0][a[0] - 'A'] = 1;
    for (int i=1; i<a.size(); i++){
        int prev = pf[i-1];
        result[i] = result[prev];
        result[i][a[i] - 'A'] = i+1;
    }
    return result;
}
vector<array<vector<int>, 26>> reverse_graph(const vector<array<int, 26>> &a){
    vector<array<vector<int>, 26>> g(a.size()+1);
    for (int i=0; i<a.size(); i++){
        for (int c=0; c<26; c++){
            g[a[i][c]][c].push_back(i);
        }
    }
    return g;
}
vector<vector<vector<int>>> dp;
int f(int ptr1, int ptr2, int ptrv){
    int& value = dp[ptr1][ptr2][ptrv];
    if (value != -1) return value;
    if (ptr1) value = max(value, f(ptr1-1, ptr2, ptrv));
    if (ptr2) value = max(value, f(ptr1, ptr2-1, ptrv));
    if (ptr1 && ptr2 && s1[ptr1-1] == s2[ptr2-1]){
        for (int prev_ptr: g[ptrv][s1[ptr1-1] - 'A']){
            value = max(value, f(ptr1-1, ptr2-1, prev_ptr) + 1);
        }
    }
    if (value == -1) value = INT_MIN;
    return value;
}
bool out = false;
void trace(int ptr1, int ptr2, int ptrv){
    int value = f(ptr1, ptr2, ptrv);
    if (ptr1 && f(ptr1-1, ptr2, ptrv) == value){
        trace(ptr1-1, ptr2, ptrv);
        return;
    }
    if (ptr2 && f(ptr1, ptr2-1, ptrv) == value){
        trace(ptr1, ptr2-1, ptrv);
        return;
    }
    if (ptr1 && ptr2 && s1[ptr1-1] == s2[ptr2-1]){
        for (int prev_ptr: g[ptrv][s1[ptr1-1] - 'A']){
            if (f(ptr1-1, ptr2-1, prev_ptr) + 1 == value){
                trace(ptr1-1, ptr2-1, prev_ptr);
                cout << s1[ptr1-1];
                out = true;
                return;
            }
        }
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> s1 >> s2 >> av;
    g = reverse_graph(kmp_auto(av));
    dp.assign(s1.size()+1, vector<vector<int>> (s2.size()+1, vector<int> (av.size()+1, -1)));
    dp[0][0][0] = 0;
    pair<int, int> result(INT_MIN, -1);
    for (int i=0; i<av.size(); i++){
        result = max(result, make_pair(f(s1.size(), s2.size(), i), i));
    }
    trace(s1.size(), s2.size(), result.second);
    if (!out){
        cout << "0";
    }
    cout << '\n';
}
