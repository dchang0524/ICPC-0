#include <bits/stdc++.h>
// #include "debugPrints.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rep1(i, a, b) for(int i = a; i <= (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef unsigned long long ull;

const ll MOD = 998244353;
#define opp(c) ((c) == 'B' ? 'A' : 'B')
ll exp(ll x, ll n) {
    ll m = MOD;
    assert(n >= 0);
    x %= m;  // note: m * m must be less than 2^63 to avoid ll overflow
    ll res = 1;
    while (n > 0) {
        if (n % 2 == 1) { res = res * x % m; }
        x = x * x % m;
        n /= 2;
    }
    return res;
}


struct Node {
    char c;
    int size;
    ll dp;
    ll update;
    Node* nextA;
    Node* nextB;
    Node* parent;
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //can use trie instead of maps
    int N; cin >> N;
    ll curr = 0;
    Node rootA, rootB; //can't have the root be empty character for some reason
    rootA.c = 'A'; rootA.size = 0; rootA.dp = 0; rootA.nextA = nullptr; rootA.nextB = nullptr; rootA.parent = nullptr;
    rootB.c = 'B'; rootB.size = 0; rootB.dp = 0; rootB.nextA = nullptr; rootB.nextB = nullptr; rootB.parent = nullptr;

    auto createNode = [](char c, Node* parent) {
        Node* newNode = new Node();
        newNode->c = c;
        newNode->size = 0;
        newNode->dp = 0;
        newNode->nextA = nullptr;
        newNode->nextB = nullptr;
        newNode->parent = parent;
        if (c == 'A') {
            parent->nextA = newNode;
        } else {
            parent->nextB = newNode;
        }
        return newNode;
    };

    rep(i, 0, N) {
        string s; cin >> s;        
        // cout << "Inserting " << s << endl;
        //Find s in the Trie
        Node* currNode = (s[0] == 'A') ? &rootA : &rootB;
        rep(i, 1, sz(s)) {
            // cout << "visiting " << currNode->c << " from " << (currNode->parent == nullptr ? 'n' : currNode->parent->c) << endl;
            char nxt = s[i];
            if (nxt == 'A') {
                if (currNode->nextA == nullptr) {
                    createNode('B', currNode);
                    currNode = createNode('A', currNode);
                    
                } else {
                    currNode = currNode->nextA;
                }
            } else {
                if (currNode->nextB == nullptr) {
                    createNode('A', currNode);
                    currNode = createNode('B', currNode);
                } else {
                    currNode = currNode->nextB;
                }
            }
        }
        // cout << "visiting " << currNode->c << " from " << (currNode->parent == nullptr ? 0 : currNode->parent->c) << endl;

        //update the size and dp of the node from child to root
        currNode->update = exp(2, currNode->size);
        currNode->size++;
        Node* updateNode = currNode->parent;
        char lastChar = currNode->c;
        while (updateNode != nullptr) {
            updateNode->size++;
            if (lastChar == 'A') {
                ll oppBranch = updateNode->nextB->dp;
                ll newBranch = (updateNode->nextA->update - updateNode->nextA->dp + MOD) % MOD;
                updateNode->update = ((newBranch*oppBranch % MOD) + updateNode->dp) % MOD;
            } else {
                ll oppBranch = updateNode->nextA->dp;
                ll newBranch = (updateNode->nextB->update - updateNode->nextB->dp + MOD) % MOD;
                updateNode->update = ((newBranch*oppBranch % MOD) + updateNode->dp) % MOD;
            }
            lastChar = updateNode->c;
            updateNode = updateNode->parent;
        }
        updateNode = (s[0] == 'A') ? &rootA : &rootB;
        // cout << "Updating " << updateNode->c << " by " << updateNode->update << endl;
        updateNode->dp = (updateNode->dp + updateNode->update) % MOD;
        updateNode->update = 0;
        // cout << "New value " << updateNode->dp << endl; 
        rep(i, 1, sz(s)) {
            char nxt = s[i];
            if (nxt == 'A') {
                updateNode = updateNode->nextA;                
            } else {
                updateNode = updateNode->nextB;
            }
            // cout << "Updating " << updateNode->c << " by " << updateNode->update << endl;
            // cout << "New value " << updateNode->dp << endl; 
            updateNode->dp = (updateNode->dp + updateNode->update) % MOD;
            updateNode->update = 0;
        }
        cout << rootA.dp * rootB.dp % MOD << endl;
    }
}
