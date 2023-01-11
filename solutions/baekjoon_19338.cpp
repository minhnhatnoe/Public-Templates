#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

/// @brief Mutiplies two matrices
/// @param a First factor
/// @param b Second factor
/// @return The product of two matrices
vector<vector<ld>> operator*(const vector<vector<ld>> &a, const vector<vector<ld>> &b){
    vector<vector<ld>> x(a.size(), vector<ld> (b[0].size()));

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

/// @brief Calculate the automaton for a string of 'H' and 'T'
/// @param a The input string
/// @return An array representing the automaton for this string,
/// where result[i][j] is the length of the longest prefix matching
/// (a[0:i] + j)
vector<int[2]> kmp_automaton(const string &a){
    // Step 1: Prefix function
    vector<int> pf(a.size());
    pf[0] = 0;
    for (int i=1; i<a.size(); i++){
        int ptr = pf[i-1];
        while (ptr != 0 && a[ptr] != a[i]) ptr = pf[ptr-1];
        pf[i] = ptr + (a[ptr] == a[i]);
    }

    // Step 2: Automaton, also the result
    vector<int[2]> result(a.size());
    result[0][0] = a[0] == 'H';
    result[0][1] = a[0] == 'T';
    for (int i=1; i<a.size(); i++){
        if (a[i] == 'H') result[i][0] = i+1;
        else result[i][0] = result[pf[i-1]][0];

        if (a[i] == 'T') result[i][1] = i+1;
        else result[i][1] = result[pf[i-1]][1];
    }

    // It is quite obvious that these two steps can be merged,
    // and is certain to yield better constant.
    // However, for the sake of readability, these two steps are seperated.
    return result;
}

// The two strings in the statement
string a, b;
// The automatons for a and b
vector<int[2]> aauto, bauto;

// Number of reachable nodes of (aptr, bptr)
int active_count = 0;
// node_index[aptr][bptr]: Index of node representing a[0:aptr][0:bptr]
vector<vector<int>> node_index;

// Builds node_index
void dfs(int aptr, int bptr){
    if (aptr == a.size() || bptr == b.size()) return;
    if (node_index[aptr][bptr] != -1) return;
    node_index[aptr][bptr] = active_count++;
    dfs(aauto[aptr][0], bauto[bptr][0]);
    dfs(aauto[aptr][1], bauto[bptr][1]);
}

/// @brief Build the transition matrix from aauto and bauto
/// @return An a.size() * b.size() matrix
vector<vector<ld>> transition_matrix(){
    vector<vector<ld>> result(active_count, vector<ld> (active_count));
    for (int i=0; i<a.size(); i++){
        for (int j=0; j<b.size(); j++){
            // a[node_index(i, j)] -> a[node_index(transition(i), transition(j))]
            int current = node_index[i][j];
            if (current == -1) continue;

            int transition_zero = node_index[aauto[i][0]][bauto[j][0]];
            if (transition_zero != -1)
                result[current][transition_zero] += 0.5;

            int transition_one = node_index[aauto[i][1]][bauto[j][1]];
            if (transition_one != -1)
                result[current][transition_one] += 0.5;
        }
    }

    int awon = node_index[a.size()][0];
    result[awon][awon] += 1;

    int bwon = node_index[0][b.size()];
    result[bwon][bwon] += 1;

    int tied = node_index[a.size()][b.size()];
    result[tied][tied] += 1;

    return result;
}
signed main(){
    // Faster IO with minimal footprint
    cin.tie(0)->sync_with_stdio(0);

    cin >> a >> b;
    aauto = kmp_automaton(a);
    bauto = kmp_automaton(b);

    node_index.assign(a.size()+1, vector<int> (b.size()+1, -1));

    // Index the "regular nodes"
    // ie. nodes where the state of the game is yet to be determined
    dfs(0, 0);

    // Node representing the state at which Alice has won
    for (int i=0; i<b.size(); i++)
        node_index[a.size()][i] = active_count;
    active_count++;

    // Node representing the state at which Bob has won
    for (int i=0; i<a.size(); i++)
        node_index[i][b.size()] = active_count;
    active_count++;

    // Node representing the state at which the game has ended with a tie
    node_index[a.size()][b.size()] = active_count++;

    // Build the transition matrix, representing possible moves
    vector<vector<ld>> transition = transition_matrix();

    // Exponentiate the transition matrix.
    // Let the number of operations be l,
    // the transition matrix represents a game gone through
    // 2^n turns. With a sufficiently large l, the probability
    // of the game having not ended after 2^l steps is negligible.'
    // This is because the problem only requires precision of 1e-8
    for (int i=0; i<60; i++)
        transition = transition * transition;

    vector<vector<ld>> result(1, vector<ld> (active_count));
    // The game starts with matching prefixes of length zero.
    // Thus, the probability of the game being at node_index[0][0] is 100%
    int starting_state = node_index[0][0];
    result[0][starting_state] = 1;

    // The distribution of the game's state after 2^l steps
    result = result * transition;

    cout << fixed << setprecision(20);

    int awon = node_index[a.size()][0];
    cout << result[0][awon] << "\n";

    int bwon = node_index[0][b.size()];
    cout << result[0][bwon] << "\n";

    int tied = node_index[a.size()][b.size()];
    cout << result[0][tied] << "\n";
}
