// Try inputing:
/*
3
1 4 2 -17.5
6 3 2 -22
5 3 7 -30.5
*/
// This solves for {1x + 4y + 2z - 17.5 = 0; 6x + 3y + 2z - 22 = 0; 5x + 3y + 7z - 30.5 = 0}
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

/// @brief Solves a system of linear equation, such as three equations of type ax + by + c = 0
/// @param a Each row represents an equation, with each cell the corresponding coefficient
/// @return Result of the equation system
vector<ld> gauss(vector<vector<ld>> &a){
    const ld EPS = 1e-9;
    for (int i=0; i<a.size(); i++){
        bool swapped = false;
        for (int j=i; j<a.size() && !swapped; j++){
            if (abs(a[j][i]) < EPS) continue;
            swap(a[i], a[j]);
            swapped = true;
        }
        if (!swapped) throw runtime_error("Zero or infinite solution exists.");
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
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<ld>> a(n, vector<ld> (n+1));
    for (int i=0; i<n; i++)
        for (int j=0; j<=n; j++)
            cin >> a[i][j];
    for (ld value: gauss(a))
        cout << setw(7) << value;
    cout << '\n';
}
