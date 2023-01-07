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
