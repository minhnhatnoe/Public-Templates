#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct dsu{
    // p[i] < 0 => i la head cua mot tap hop co -p[i] phan tu
    // Dai khai la luu am size o thang head
    vector<int> p;
    dsu(int n): p(n, -1) {}
    int find(int v){
        return p[v] < 0 ? v : p[v] = find(p[v]);
    }
    void merge(int a, int b){
        a = find(a), b = find(b);
        if (a == b) return;
        if (-p[a] < -p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
    }
};
struct query{
    int l, r;
    int u, v;
    int idx;
};
struct edge{
    int u, v, w;
};
void testcase(){
    int n, m; cin >> n >> m;
    vector<edge> a(m);
    for (int i=0; i<m; i++){
        cin >> a[i].u >> a[i].v >> a[i].w;
        a[i].u--, a[i].v--;
    }
    sort(a.begin(), a.end(), [](const edge &x, const edge &y){
        return x.w < y.w;
    });
    int q; cin >> q;
    vector<query> c_step(q);
    vector<int> result(q);
    for (int i=0; i<q; i++){
        cin >> c_step[i].u >> c_step[i].v;
        c_step[i].u--, c_step[i].v--;
        c_step[i].idx = i;
        c_step[i].l = 1, c_step[i].r = 10000;
    }
    while (c_step.size()){
        vector<query> nxt_step;
        dsu graph(n);
        int aptr = 0;
        for (int lptr=0, rptr=0; lptr < c_step.size(); lptr = rptr){
            int l = c_step[lptr].l, r = c_step[lptr].r;
            int m = (l+r)>>1;
            // Add cac canh ma weight <= m
            while (aptr < a.size() && a[aptr].w <= m){
                graph.merge(a[aptr].u, a[aptr].v);
                aptr++;
            }
            // Loop qua cac query co cung khoang [l,r]. Do cac khoang disjoint nen
            // Neu gia tri l bang nhau thi gia tri r cung bang nhau
            vector<query> left, right;
            while (rptr < c_step.size() && l == c_step[rptr].l){
                query c = c_step[rptr];
                // u, v cung component
                if (graph.find(c.u) == graph.find(c.v)){
                    c.r = m;
                    if (c.l == c.r) result[c.idx] = c.l; // Query da hoan thanh
                    else left.push_back(c);
                }
                else{
                    c.l = m+1;
                    if (c.l == c.r) result[c.idx] = c.l;
                    else right.push_back(c);
                }
                rptr++;
            }
            nxt_step.insert(nxt_step.end(), left.begin(), left.end());
            nxt_step.insert(nxt_step.end(), right.begin(), right.end());
        }
        c_step = move(nxt_step); // Tuong duong viec swap hai mang
    }
    for (int i=0; i<result.size(); i++){
        cout << result[i] << "\n";
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    for (int i=1; i<=t; i++){
        cout << "Case " << i << ":\n";
        testcase();
    }
}
