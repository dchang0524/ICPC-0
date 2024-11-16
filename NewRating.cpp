//https://codeforces.com/contest/2029/problem/C
#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

int inf = 1000000;
int N;
vector<int> ratings;
vector<int> pref;

template <typename T>
void printVector(vector<T> v) {
   for (int i = 0; i<v.size(); i++) {
       cout << v[i] << " ";
   }
   cout << "\n";
}

template <typename T>
void print2DVector(vector<vector<T>> v) {
   for (int i = 0; i < v.size(); i++) {
       for (int j = 0; j<v[i].size(); j++) {
           cout << v[i][j] << " ";
       }
       cout << "\n";
   }
}



int last_true(int lo, int hi, function<bool(int)> f) {
   // if none of the values in the range work, return lo - 1
   lo--;
   while (lo < hi) {
       // find the middle of the current range (rounding up)
       int mid = lo + (hi - lo + 1) / 2;
       if (f(mid)) {
           // if mid works, then all numbers smaller than mid also work
           lo = mid;
       } else {
           // if mid does not work, greater values would not work either
           hi = mid - 1;
       }
   }
   return lo;
}

bool check(int k) {
    vector<int> suff(N+2);
    suff[N+1] = k;
    for (int i = N; i>= 1; i--) {
        if (ratings[i] >= suff[i+1]) {
            suff[i] = max(suff[i+1] - 1, 1); 
            //if ratings[i] = suff[i+1], suff[i+1] could be ratings[i] or ratings[i] - 1, but make sure it doesnt go below 1
                //however, if there exists pref[j] with j < i such that pref[j] >= ratings[i] - 1, so we choose ratings[i] -1
        }
        else if (ratings[i] < suff[i+1]) {
            suff[i] = suff[i+1] + 1;
        }
    }
    suff[0] = inf; //since we must have at least 1 skip
    suff[1] = inf;
    //printVector(pref);
    // cout << "k: " << k << "\n";
    // printVector(suff);

    //we could use the l r precomputation here to reduce a log n factor, but it is not necessary so I will just use a treeset
    multiset<int> ms;
    //must skip at least one contest
    for (int i = 0; i < N; i++) {
        ms.insert(pref[i]);
    }

    for (int i  = N+1; i >= 2; i--) {
        // cout << "suff[i]: " << suff[i] << "\n";
        // for (const auto& value : ms) {
        //     std::cout << value << " ";
        // }
        // std::cout << std::endl;
        auto it = ms.lower_bound(suff[i]);
        if (it != ms.end()) {
            return true;
        }
        it = ms.find(pref[i-2]);
        ms.erase(it);
    }
    return false;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //let the array be [a_1, a_2, ..., a_n]
    //let f_i(x) be the result of running x through [a_i, a_{i+1}, ..., a_n] without skipping
    //First, notice f_n(x+1) >= f_n(x), and by applying induction, f_i(x+1) >= f_i(x) for all i = 1, ..., n
    //Using the previous fact, if a_i >= x, f_{i}(x) >= f_{i+1}(x), equality acheived when a_i = x or a_{i+1} = x
    //Consider we start skipping at index l, and our current value is x. 
        //We would stop skipping when we reach a value in the array that is greater than x.
        //we could store all the l's for each r's in O(n log n)
    //Note f_i{x} = f_{i+1}(x+1) if x > a_i, f_{i+1}(x) if x = a_i, and f_{i+1}(x-1) if x < a_i

    //We kind of need a way to go backwards, which is really hard to do unless you know a specific value -> motivates binary search
    //We can binary search on the answer, 
        //check() returns true if it is possible to construct an answer >= k
        //it is possible to construct an answer >= k if
            //there exists an indexes i,j (with i < j) such that when running through the array in reversed order (with reversed operations)
                //pref[i] >= suff[j], as f_j(x+1) >= f_j(x)
                    //pref[i] represents the value when you run 0 through the first i elements
                    //suff[j] represents the value when you run k through the last j elements in reverse order and reversed operations
    int T;
    cin >> T;
    bool dpSol = true;
    while (!dpSol && T--) {
        cin >> N;
        ratings.clear();
        pref.clear();
        ratings.push_back(0);
        for (int i = 0; i < N; i++) {
            int a;
            cin >> a;
            ratings.push_back(a);
        }
        pref.push_back(0);
        for (int i = 1; i <= N; i++) {
            if (ratings[i] > pref[i-1]) {
                pref.push_back(pref[i-1] + 1);
            }
            else if (ratings[i] == pref[i-1]) {
                pref.push_back(pref[i-1]);
            }
            else {
                pref.push_back(pref[i-1] - 1);
            }
        }
        
        // cout << "T: " << T << "\n";
        // printVector(ratings);
        // printVector(pref);
        // cout << "\n";

        int ans = last_true(1, N, check);
        cout << ans << "\n";        
        //cout << "\n";
    }
    while (dpSol && T--) {
        //Another way to solve this is noticing the recursive nature of the function, and seeing if we can use dp
        //There are 3 states: not skipping, in the process of skipping, or finished skipping
        //dp[i][0] = score after processing a_i without ever having skipped
        //dp[i][1] = max score afer skipping a_i and possibly having skipped indexes before i
        //dp[i][2] = max score after skipping at least one index
        //dp[i][0] is just the prefix array
        //dp[i][1] = max(dp[i-1][0], dp[i-1][1])
        //dp[i][2] = max(dp[i-1][1]+x, dp[i-1][2]+x), where x is adjusted based on performing an operation at index i
        cin >> N;
        vector<vector<int>> dp(N+1, vector<int>(3));
        ratings.clear();
        ratings.push_back(0);
        for (int i = 0; i < N; i++) {
            int r;
            cin >> r;
            ratings.push_back(r);
        }
        for (int i =  1; i <= N; i++) {
            if (dp[i-1][0] < ratings[i]) {
                dp[i][0] = dp[i-1][0] + 1;
            }
            else if (dp[i-1][0] == ratings[i]) {
                dp[i][0] = dp[i-1][0];
            }
            else {
                dp[i][0] = dp[i-1][0] - 1;
            }
        }

        for (int i = 1; i <= N; i++) {
            dp[i][1] = max(dp[i-1][0], dp[i-1][1]);
        }
        dp[0][2] = -inf;
        dp[1][2] = -inf; //you must skip at least one element
        for (int i = 2; i <= N; i++) {
            int a = -inf;
            if (dp[i-1][2] != -inf) {
                if (dp[i-1][2] < ratings[i]) {
                a = 1;
                }
                else if (dp[i-1][2] == ratings[i]) {
                    a = 0;
                }
                else {
                    a = -1;
                }
            }

            int b;
            if (dp[i-1][1] < ratings[i]) {
                b = 1;
            }
            else if (dp[i-1][1] == ratings[i]) {
                b = 0;
            }
            else {
                b = -1;
            }

            dp[i][2] = max(dp[i-1][2] + a, dp[i-1][1] + b);
        }

        //print2DVector(dp);
        cout << max(dp[N][2], dp[N][1]) << "\n";
    }

}
