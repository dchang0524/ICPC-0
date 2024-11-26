//https://codeforces.com/problemset/problem/2039/D
//if a_{gcd(i,j)} = gcd(a_i, a_j) for i < j
    //Let g = gcd(i, j)
        //Let a_i = g*k_1, where k_1 >= 1
        //Let a_j = g*k_2, where k_2 >= 2
    //a_g = gcd (a_{g*k_1}, a_{g*k_2})
        //Then, a_g | a_{g*k_1} and a_g | a_{g*k_2}
            //Thus, the condition holds if and only if a_x divides a_{x*k} for any k >= 1
//Thus, a_x does not divide a_{x*k}
    //Note if a_i > a_j, a_i can't divide a_j. This works observations is useful as we want the lexicorgraphically greatest array
    //We greedily assign the highest number such that no a_{div_i} uses that number to a_i
    //For each a_i, we store the ranking of the highest number (0 = highest number in the set, 1 = second highest number, ...) it can form
        //Starting from i = 1, iterate through i = N
            //For every multiple of i, we increase the ranking of a_i by 1 if the multiple has an equal ranking as i
                //If it has a greater ranking, it doesn't matter because it won't be able to use the number for a_i
                //It can't have a lower ranking because a multiple of i is always a multiple of a divisor of i
            //If the rank of a_i >= M (since ranking is 0-indexed), it is impossible to construct an answer
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
    int T;
    cin >> T;
    while (T--) {
        int M, N;
        cin >> N >> M;
        vector<int> nums(M);
        for (int i = M-1; i >= 0; i--) {
            cin >> nums[i];
        }
        bool works = true;
        vector<int> array(N+1);
        for (int i = 1; i <= N; i++) {
            for (int j = 2*i; j <= N; j += i) {
                if (array[j] <= array[i]) {
                    array[j]++;
                }
            }
            if (array[i] >= M) { //nums is 0-indexed
                works = false;
                break;
            }
        }
        if (!works) {
            cout << -1 << endl;
            continue;
        }
        for (int i = 1; i <= N; i++) {
            cout << nums[array[i]] << " ";
        }
        cout << endl;
    }
}
