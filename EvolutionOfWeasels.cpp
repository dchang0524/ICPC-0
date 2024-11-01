#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

string reduce(string s) {
    int numB = 0;
    for (int i  = s.size()-1; i>= 0; i--) {
        if (s[i] == 'B') {
            s.erase(i, 1);
            numB++;
        }
    }
    numB %= 2;
    if (numB > 0) {
        s += "B";
    }
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i+1<s.size(); i++) {
            if (s[i] == s[i+1]) {
                s.erase(i, 2);
                change = true;
                break;
            }
        }
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        string u, v;
        cin >> u >> v;
        //Problem: change u to v via adding/removing series of 'AA', 'BB', 'CC', 'ABAB', or 'BCBC' at any indices
        //all operations are reversible
            //if you reverse a sequence of operations, it will still be a valid sequence
        //consider the following operations
            //AB -> ABAA -> ABABBA -> BA, so BA -> ... -> AB is also always possible
            //BC -> BCBB -> BCBCCB -> CB, so CB -> ... -> BC is also always possible
            //Thus, you can freely move around the B's
        //+Notice that the parity of the number of A's must be same in u and v, and similarly for 'B' and 'C'
            //This is because operations don't change the parity of the number of occurences of a letter
            //So actually, if you had 'ACAC', this problem would be much simpler as you could also switch 'A' and 'C'.
        //For a string S, let r(S) be the reduced form of S.
            //Define the reduced form of S where all 'B's are moved to the end of S and all'AA's, 'BB''s, and 'CC's are removed from S until no more can be removed.
            //Notice that a string S has only 1 reduced form, and that no matter what operations we perform on S, the reduced form of S remains constant 
                //Only 1 reduced form because 'AA' 'BB' and 'CC' are non-overlapping
                //Reduced form remains constant because B's are moved to the back and any two consecutive characters can be erased.
            //If two strings s1 and s2 have the same reduced form, it is possible to convert s1 to s2.
                //Proof: s1 -> ... -> r(s1), s2 -> ... -> r(s2), r(s1) = r(s2). Since opertaions are reversible, s1 -> ... -> r(s1) = r(s2) -> ... -> s2
            //If two strings s1 and s2 could be switched into each other, r(s1) = r(s2) has to be true, as r(s1) and r(s2) remains invariant throughout operations.
            //Thus, we only have to check if r(u) = r(v). Thus can be done in O(|u|^2 + |v|^2) time
                //You can also do this in linear time by using a stack, but it's not necessary
        
        string r_u = reduce(u);
        string r_v = reduce(v);
        if (r_u == r_v) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}
