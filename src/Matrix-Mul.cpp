#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/// @brief Mutiplies two matrices
/// @param a First factor
/// @param b Second factor
/// @return The product of two matrices
vector<vector<ll>> operator*(const vector<vector<ll>> &a, const vector<vector<ll>> &b){
    vector<vector<ll>> x(a.size(), vector<ll> (b[0].size()));

    // Two matrices can only be multiplied when this is satisfied
    assert((a[0].size() == b.size()));
    for (int i=0; i<a.size(); i++)
        // Swapping k's and j's for loop
        // can result in much faster matrix multiplication,
        // while not sacrificing readability.
        for (int j=0; j<b[0].size(); j++)
            for (int k=0; k<b.size(); k++)
                x[i][j] += a[i][k] * b[k][j];
    return x;
}
/// @brief Returns identity matrix of size n, ie A such that V * A = V (V is a matrix of 1 * n)
/// @param n The needed size
/// @return The matrix
vector<vector<ll>> identity_matrix(int n){
    vector<vector<ll>> r(n, vector<ll> (n));
    for (int i=0; i<n; i++) r[i][i] = 1;
    return r;
}
/// @brief Perform V *= A^b. This is approximately x2 faster than performing V = V * (A^b)
/// @param v The resulting matrix
/// @param a The matrix to be exponentiated
/// @param b The exponent
void ternarybinpow(vector<vector<ll>> &v, vector<vector<ll>> a, ll b){
    for (; b; b >>= 1, a = a * a)
        if (b & 1) v = v * a;
    // Alternate implementation:
    // while (b != 0){
    //     if (b % 2)
    //         v = v * a;
    //     a = a * a;
    //     b /= 2;
    // }
    // But of course, the implementation used is shorter, and is also faster
}
/// @brief Calculates A^b in O(A.size()^3*lg(b))
/// @param a The matrix A
/// @param b The number b
/// @return Result of A^b
vector<vector<ll>> binpow(vector<vector<ll>> a, ll b){
    vector<vector<ll>> r = identity_matrix(a.size());
    ternarybinpow(r, a, b);
    return r;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<ll>> a(n, vector<ll> (n));
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> a[i][j];
    ll b; cin >> b;
    a = binpow(a, b);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cout << setw(5) << a[i][j] << " \n"[j==n-1];
}
