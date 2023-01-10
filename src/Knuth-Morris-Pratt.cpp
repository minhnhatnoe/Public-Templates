// Try inputing:
// 2 ABB
// 2 ABA
#include <bits/stdc++.h>
using namespace std;

/// @brief Calculates the prefix function for a string
/// @param a The input string
/// @return The result of a's prefix function
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

// NOTE: Change this thing
/// @brief Calculates the automaton for a string of 'H' and 'T'
/// @param a The input string
/// @return An array representing the automaton for this string,
/// where result[i][j] is the length of the longest prefix matching
/// (a[0:i] + j)
vector<int[26]> kmp_automaton(const string &a){
    // Step 1: Prefix function
    vector<int> pf = prefix_function(a);

    // Step 2: Automaton, also the result
    vector<int[26]> result(a.size());
    for (int c=0; c<26; c++)
        result[0][c] = (a[0] == 'A' + c);

    for (int i=1; i<a.size(); i++){
        for (int c=0; c<26; c++){
            if (a[i] == 'A' + c) result[i][c] = i+1;
            else result[i][c] = result[pf[i-1]][c];
        }
    }

    // It is quite obvious that these two steps can be merged,
    // and is certain to yield better running time constant.
    // However, for the sake of readability, they are seperated.
    return result;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int char_no;
    cin >> char_no;
    string a; cin >> a;
    cout << "Prefix function:\n";
    for (int value: prefix_function(a)){
        cout << value << " ";
    }
    cout << "\n";
    cout << "Automaton:\n";
    cout << setw(4) << "CHAR" << setw(4) << "IDX";
    for (int i=0; i<char_no; i++){
        cout << setw(4) << char('A' + i);
    }
    cout << "\n";
    vector<int[26]> automaton = kmp_automaton(a);
    for (int i=0; i<a.size(); i++){
        cout << setw(4) << a[i] << setw(4) << i;
        for (int j=0; j<char_no; j++){
            cout << setw(4) << automaton[i][j];
        }
        cout << "\n";
    }
}
