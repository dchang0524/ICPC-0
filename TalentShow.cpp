#include <bits/stdc++.h>

//https://usaco.org/index.php?page=viewproblem2&cpid=839
using namespace std;
typedef long long ll;

int N, W;
vector<int> weights;
vector<int> talents;

bool check(int num) {
    //the actual ratio is num/1000
    //cout << "checking 1000*ratio = " << num << "\n";
    // vector<pair<ll, int>> curr(N);
    // for (int i = 0; i<N; i++) {
    //     curr[i].first = 1000LL*cows[i].second - num*cows[i].first; //value of coins
    //     curr[i].second = cows[i].first; //weight of coins
    // }
    //sort(curr.begin(), curr.end());

    //we can't just greedy because 
        //Say cow1 = <v1, w1> with v1 < 0 and weight w1
        //Say cow2 = <v2>,w2> with v2 < v1 < 0 and height w2
        //Say runningValue - v1 > 0 and runningValue - v2 > 0 but runningValue-v1-v2 < 0, 
            //and that runningWeight + w1 < W but runningWeight + w2 >= W
    // int running = 0;
    // int weight = 0;
    // for (int i = N-1; i>=0 && weight<W; i--) {
    //     running += curr[i].first;
    //     weight += curr[i].second;
    // }
    // if (running >= 0) {
    //     return true;
    // }
    // return false;


    //we use knapsack
    //dp[x] = max value we can obtain while weight = x
    //although we can't greedy, we can add all cows with values > 0
    //if x>=W, we don't care
        //so dp[W] is actually max value we can obtain while weight >= W
    vector<ll> dp(W+1);
    ll unreachable = -1000000000000000000LL;
    //cout << unreachable << "\n";

    for (int i = 1; i<W+1; i++) {
        dp[i] = unreachable;
    }
    for (int i = 0; i < N; i++) {
        for (int x = W; x>= 0; x--) {
            ll value = 1000*talents[i] - (ll)num*weights[i];
            int newX = min(W, x+weights[i]);
            if (dp[x] != unreachable) {
                dp[newX] = max(dp[newX], dp[x]+value);
            }
        }
    }

    // cout << "dp[]\n";
    // for (int i = 0; i < W+1; i++) {
    //     cout << dp[i] << " ";
    // }
    // cout << "\n";

    if (dp[W] >= 0) {
        //cout << "works\n";
        return true;
    }
    //cout << "doesn't work\n";
    return false;
}

int last_true(int lo, int hi, function<bool(int)> f) {
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

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    // cin >> N >> W;
    ifstream fin("talent.in");
    ofstream fout("talent.out");
    fin >> N >> W;

    for (int i = 0; i<N; i++) {
        // pair<ll, ll> temp;
        // cin >> temp.first >> temp.second;
        //fin >> temp.first >> temp.second; 
        //cows.push_back(temp);
        int tempW, tempT;
        //cin >> tempW >> tempT;
        fin >> tempW >> tempT;;
        weights.push_back(tempW);
        talents.push_back(tempT);
    }

    int ans = last_true(0, 1000*1000, check);
    //cout << ans << "\n";
    fout << ans << "\n";
}
