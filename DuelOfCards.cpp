//https://open.kattis.com/contests/nasouth24d1open/problems/duelofcards
//https://open.kattis.com/problems/duelofcards
//Sort the decks in increasing order
//The decks are A and B
//We want maximum # of wins for A and minimum # of wins for A
    //We just need a function maxWins(A, B) that computes maximum number of wins for the first parameter, then also compute maxWins(B,A)
//To determine maxWins(A,B)
    //We assign the cards in A and B into pairs and get rid of them from the deck
    //If the biggest card in B > biggest card in A, we pair it with the smallest card in A
        //Suppose instead we didn't do this for at least one card.
            //Suppose the biggest card in B was b_x, and the smallest card in A was a_y
            //Suppose B is paired with some a_w with a_w > a_y and a_y is paired with some b_z where b_z < b_x
            //Then, if we swap a_y with a_w, and the # of wins for A can either increase or stay the same
                //Thus, this strategy is optimal.
    //Otherwise, we pair the biggest card in A with the biggest card in B
        //Suppose the biggest card in A is a_x and biggest card in B is b_z
        //Suppose instead we paired a_x with some b_w where b_w < b_z and b_z with some a_y where a_y < a_x
            //Then again, if we swap b_w and b_z, the # of wins for A can either increase or stay the same
                //Thus this strategy is also optimal
#include <bits/stdc++.h>
using namespace std;


#define pb push_back
#define mp make_pair


typedef long long ll;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


template <typename T> vector<T> ndvec(size_t size, T initial_value) {
   return vector<T>(size, initial_value);
}
template <typename T, typename... U> auto ndvec(size_t head, U &&...u) {
   auto inner = ndvec<T>(u...);
   return vector<decltype(inner)>(head, inner);
}

template <typename T>
void printSet(set<T> s) {
    for (auto i : s) {
       cout << i << " ";
    }
    cout << "\n";
}

int maxWins(set<int> a, set<int> b) {
    int wins = 0;
    set<int> A = a;
    set<int> B = b;
    
    // cout << "a: ";
    // printSet(A);
    // cout << "b: ";
    // printSet(B);

    while (!A.empty()) {
        if (*B.rbegin() > *A.rbegin()) {
            B.erase(*B.rbegin());
            A.erase(*A.begin());
        }
        else {
            wins++;
            A.erase(*A.rbegin());
            B.erase(*B.rbegin());
        }
        // cout << "a: ";
        // printSet(A);
        // cout << "b: ";
        // printSet(B);
    }
    // cout << wins << endl;
    return wins;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N;
    cin >> N;
    set<int> B;
    for (int i = 1; i <= 2*N; i++) {
        B.insert(i);
    }
    set<int> A;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        B.erase(a);
        A.insert(a);
    }
    int m = N - maxWins(B, A);
    int M = maxWins(A, B);
    cout << m << " " << M;
}
