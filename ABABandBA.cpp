/*
The code uses the observations that there needs to be a | between any two adjacent A's and B's
Then using A's and B's given, we could compute at least how many AB + BA we need
Then 2 possible sequences are ABAB...A, BABA...B, which doens't matter, they can be partitioned into AB's and BA's without affecting the maximum number of AB/BA partitions
The other 2 sequences are ABAB..AB, BABA...BA, which does matter: 
    the presence of BA or AB respectively will lower the maximum amount of partitions by exactly 1. 
    Thus, it is better if we concentrate usage of BA or AB on sequences ABAB...AB or BABA...BA 
        in a few sequences, meaning we should concentrate them on larger sized sequences.
*/
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define mp make_pair
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int limA, limB, limAB, limBA; cin >> limA >> limB >> limAB >> limBA;
        vector<int> letCnt; //letter count
        vector<char> let; //letters (group adjacent letters)
        int A = 0, B = 0;
        int cur = 0;
        let.pb(s[0]);
        letCnt.pb(1);
        s[0] == 'A' ? A++ : B++;
        for (int i = 1; i < s.length(); i++) {
            s[i] == 'A' ? A++ : B++;
            if (s[i] == let[cur]) {
                letCnt[cur]++;
            } else {
                let.pb(s[i]);
                letCnt.pb(1);
                cur++;
            }
        }
        
        for (int i = 0; i < letCnt.size(); i++) {
            if (letCnt[i] > 2) {
                if (let[i] == 'A') {
                    A -= letCnt[i] - 2;
                    limA -= letCnt[i] - 2;
                    letCnt[i] = 2;
                } else {
                    B -= letCnt[i] - 2;
                    limB -= letCnt[i] - 2;
                    letCnt[i] = 2;
                }
            }
        }
        if (letCnt[0] == 2) {
            if (let[0] == 'A') {
                A--;
                limA--;
                letCnt[0]--;
            } else {
                B--;
                limB--;
                letCnt[0]--;
            }
        }
        if (letCnt[letCnt.size() - 1] == 2) {
            if (let[letCnt.size() - 1] == 'A') {
                A--;
                limA--;
            } else {
                B--;
                limB--;
            }
            letCnt[letCnt.size() - 1]--;
        }
        if (limB < 0 || limA < 0) {
            cout << "NO" << endl;
            continue;
        }

        int needed = max(0, max(A-limA, B-limB));
        int free = 0;
        multiset<int> seqAB;
        multiset<int> seqBA;
        char currSeq = let[0];
        int currLen = 1;
        for (int i = 1; i < letCnt.size(); i++) {
            if (letCnt[i] == 2 || i == letCnt.size()-1) {
                currLen++;
                if (let[i] == currSeq) {
                    free += (currLen-1)/2;
                } else {
                    if (currSeq == 'A') {
                        seqAB.insert(currLen);
                    } else {
                        seqBA.insert(currLen);
                    }
                }
                currLen = 0;
                currSeq = let[i];
            }
            currLen++;
        }

        if (needed > limAB + limBA) {
            cout << "NO" << endl;
            continue;
        }
        needed -= free;
        if (needed <= 0) {
            cout << "YES" << endl;
            continue;
        }
         
        //greedily use AB and BA
        auto minElem = seqAB.begin();
        while (minElem != seqAB.end()) {
            int len = *minElem;
            if (limAB >= len/2) {
                limAB -= len/2;
                needed -= len/2;
                minElem = seqAB.erase(minElem);
            } else {
                break;
            }
        }
        minElem = seqBA.begin();
        while (minElem != seqBA.end()) {
            int len = *minElem;
            if (limBA >= len/2) {
                limBA -= len/2;
                needed -= len/2;
                minElem = seqBA.erase(minElem);
            } else {
                break;
            }
        }
        
        minElem = seqAB.begin();
        while (minElem != seqAB.end()) {
            int have = ((*minElem)-1)/2;
            have -= limAB;
            needed -= limAB;
            needed -= min(have, limBA);
            limBA -= min(have, limBA);
            limAB = 0;
            minElem = seqAB.erase(minElem);
        }
 
        minElem = seqBA.begin();
        while (minElem != seqBA.end()) {
            int have = ((*minElem)-1)/2;
            have -= limBA;
            needed -= limBA;
            needed -= min(have, limAB);
            limAB -= min(have, limAB);
            limBA = 0;
            minElem = seqBA.erase(minElem);
        }
 
        if (needed <= 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}