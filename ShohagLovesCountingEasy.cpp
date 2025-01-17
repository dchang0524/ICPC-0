//https://codeforces.com/problemset/problem/2039/F1
//Note f(i+1) is a multiple of f(i)
    //The maximum elements of (N-(i+1)+1) segments with length i+1
        //Notice that they are still maximum elements of a lot of the segments with length i
        //It can be shown that there is at most one segment of length i that doesn't contain any of the maximum elements in the segments of length i+1
            //Thus, f(i) = gcd(f(i+1), k) where k is the maximum element in that segment
            //This k must be unique from the other maximum elements, otherwise the gcd wouldn't change from f(i)
//Consider the biggest element in the array
    //It must be unique and at the very front or very back of the array
        //Otherwise, f(N) = f(N-1).
    //Thus the array can be partitioned to [m, A] or [A, m] where A is the remaining array and m is the maximum element
    //If we recursively perform this analysis, considering the next biggest element, we can get that A a good subarray
        //A could be empty
        //Not all good subarrays work, but if A must be good in order for [m, A] or [A, m] to be good
        //All elements in the array must be distinct
    //Using this property we found, we could find all sorted (in decreasing order) good subarrays, and then multiply the answer by 2^{k}, where k is the length of each sorted good subarray
        //This can make our sequences much simpler, as then only the elements of the sequence matter
//Try some dp methods, as this seems very recursive
    //e.g adding a number to the front/back of a sequence
//Consider we have a sequence, and we try to add an element at the end of the sequence
    //The element we add must be smaller than the current end of the sequence, and the gcd(current gcd, element added) < current gcd
        //Thus, only the element at the end of the sequence and the current gcd matters
//Let dp[i][j] represent the number of sequences ending with i with current gcd g
    //Notice j | i.
    //dp[i][j] = sum_{k = i, ..., M}(sum_{gcd(g,i) = j, g <= M}(dp[k][g]))
        //Notice that rather the ending element of the sequence doesn't matter
            //We just have to add all sequences that have gcd = g that has ending element greater than i+1
                //We can do this by just simplifying our dp array into dp[i] = sequences that have gcd i and processing each ending element in decreasing order
//Let dp[i] represent the sequences that have gcd i
    //We do a knapsack-like approach, where we process the case when M is our ending element, then M-1, and so on
    //If our current ending element is k
        //new_dp[i] = sum{gcd(g, k) = i, g <= M}(dp[g])
            //We use the fact that i | g and i | k to speed up our operations
            //We also don't have to worry about using i twice as this would lead to an invalid sequence
                //dp[i] = sum{gcd(g, k) = i, g <= M}(dp[g]), instead of creating new array called new_dp
                    //This is still too slow
                        //Instead of involving multiples, let's try to express everything in terms of divisors
                        //This would lead to overcounting, but we can also correct overcounting
        //We use complementary counting to optimize our transitions
            //Consider dp[i], where i | k
            //Consider sum{x: i | x, i <= M}(dp[x])
                //This includes all the cases in dp[i]
                //This includes additional cases where gcd(x, k) = y*i, where y = gcd(x/i, k/i), which means y | x
                    //This can also be overcounted as:
                    //sum{z: y*i | z, z <= M}(dp[z])
                    //This motivates the PIE
                    //This also motivates a second array: dp1[i] = sum{x: i | x}(dp[x])
            //dp[i] = 2 * sum{p}(pow(-1, |p|) * dp1[f(p)*i]). If (i ==k), add 1 to dp[i] to start a new sequence of length 1
                //p denotes the bitmask of a subset of the set of distinct primes that divide k/i
                    //|p| denotes the number of 1s in the bitmask (i.e: the size of the subset)
                    //f(p) denotes the product of the primes in denoted by the bitmask
                        //if p = 0, f(p) = 1
                //You can also update dp1 by checking the divisors of i

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MOD = 998244353;    
const int maxM = 1e5;

int add(int a, int b){
	a += b;
	if(a > MOD) 
        a -= MOD;
	if(a < 0) 
        a += MOD;
	return a;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    vector<vector<int>> divisors(maxM+1);
    vector<vector<int>> primes(maxM+1);
    for (int i = 1; i <= maxM; i++) {
        for (int j = i; j <= maxM; j += i) {
            divisors[j].pb(i); 
            if (divisors[i].size() == 2) { //works because all of i is populated
                primes[j].pb(i);
            }
        }
    }

    while (T--) {
        int M; cin >> M;
        vector<int> dp(M+1);
        vector<int> dp1(M+1);
        for (int m = M; m >= 1; m--) {
            for (const int i : divisors[m]) {
                int curr = 0;
                for (int p = 0; p < 1 << primes[m/i].size(); p++) {
                    int mult = 1;
                    int n = 0;
                    for (int b = 0; b < primes[m/i].size(); b++) {
                        if (p & (1 << b)) {
                            mult *= primes[m/i][b];
                            n++;
                        }
                    }
                    int temp = add(dp1[i*mult], dp1[i*mult]);
                    int sign = n & 1 ? -1 : 1;
                    curr = add(curr, sign*temp);
                }
                int temp = add(dp[i], dp[i]);
                curr = add(curr, -1*temp);
                if (i == m) {
                    curr = add(curr, 1);
                }
                dp[i] = add(dp[i], curr);
                for (const int d : divisors[i]) {
                    dp1[d] = add(dp1[d], curr);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i <= M; i++) {
            ans = add(dp[i], ans);
        }
        cout << ans << endl;
    }
}
