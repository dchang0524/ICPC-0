#include <bits/stdc++.h>

//https://oj.uz/problem/view/CEOI18_clo
using namespace std;
typedef long long ll;

ll inf = 1000000000000000000LL;

void print_dp(const vector<ll>& dp, const string& message = "") {
    if (!message.empty()) {
        cout << message << endl;
    }
    cout << "dp array:" << endl;
    for (size_t i = 0; i < dp.size(); ++i) {
        if (dp[i] != -inf) { // Only print reachable states
            cout << "dp[" << i << "] = " << dp[i] << endl;
        }
    }
    cout << "-----------------------" << endl;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //consider the subproblem where all clock rates are equal
        //This problem could be solved by considering the two dp arrays:
            //revenue[k] = the maximum revenue that could be earned from k cores
            //price[k] = the minimum price required to buy at least k cores
        //The answer is just max(revenue[k] - price[k])
    //Consider extending the previous subproblem by sorting the array of clock rates of orders and computers, then processing an order or computer in reverse order
        //the traditional knapsack transition doesn't really work
            //we must ensure previous orders use previous computers
            //the presence of leftover cores from processing previous orders and computers
            //the possibility of buying a previous computer (ex: computer with much higher clock rate)
        //change dp to profit[l] = maximum profit from having l leftover cores (actually, I tried profit[c][l], where c is the number of cores sold, but I realized c wouldn't matter)
            //using this method, we can process and store all previous computers by having a lot of leftover cores
            //when we process an order with price v and # of cores required c
                //newProfit[l] = max(profit[l+c] + v, profit[l]), if profit[l+c] is reachable
            //when we process a computer with price v and # of cores c
                //newProfit[l+c] = max(profit[l+c], profit[l] - v), if profit[l] is reachable
            //if profit[l] is unreachable, profit[l] = -infinity
            //by processing the computers and orders in decreasing clock rate, we ensure every computer currently process has higher or equal clock rate to an order being processed
    int N, M;
    cin >> N;
    vector<tuple<int, ll, ll>> computers(N);
    for (int i = 0; i < N; i++) {
        auto& [a, b, c] = computers[i];
        cin >> a >> b >> c;
    }
    sort(computers.begin(), computers.end(),
         [](const auto& a, const auto& b) {
             return get<1>(a) < get<1>(b);
         });
    cin >> M;
    vector<tuple<int, ll, ll>> orders(M);
    for (int i = 0; i < M; i++) {
        auto& [a, b, c] = orders[i];
        cin >> a >> b >> c;
    }
    sort(orders.begin(), orders.end(),
         [](const auto& a, const auto& b) {
             return get<1>(a) < get<1>(b);
         });
         
    // for (const auto& [a, b, c] : computers) {
    //     cout << a << " " << b << " " << c << endl;
    // }
    // for (const auto& [a, b, c] : orders) {
    //     cout << a << " " << b << " " << c << endl;
    // }



    int maxCores = 50*N;
    vector<ll> dp(maxCores + 1, -inf);
    dp[0] = 0;
    int j = M-1;
    for (int i = N-1; i>= 0; i--) {
        while (j >= 0 && get<1>(orders[j]) > get<1>(computers[i])) {
            //process order
            //newProfit[l] = max(profit[l+c] + v, profit[l]), if profit[l+c] is reachable
            for (int l = 0; l < maxCores + 1; l++) {
                int newInd = l + get<0>(orders[j]);
                if (newInd <= maxCores && dp[newInd] != -inf) {
                    dp[l] = max(dp[l], dp[newInd] + get<2>(orders[j]));
                }
            }
            //print_dp(dp, "After processing order j = " + to_string(j));
            j--;
        }
        //process computer
        //newProfit[l+c] = max(profit[l+c], profit[l] - v), if profit[l] is reachable
        for (int l = maxCores; l >= 0; l--) {
            int newInd = l - get<0>(computers[i]);
            if (newInd >= 0 && dp[newInd] != -inf) {
                dp[l] = max(dp[l], dp[l - get<0>(computers[i])] - get<2>(computers[i]));
            }
        }
        //print_dp(dp, "After processing computer i = " + to_string(i));
    }
    while (j >= 0) {
            //process order
            //newProfit[l] = max(profit[l+c] + v, profit[l]), if profit[l+c] is reachable
            for (int l = 0; l < maxCores + 1; l++) {
                int newInd = l + get<0>(orders[j]);
                if (newInd <= maxCores && dp[newInd] != -inf) {
                    dp[l] = max(dp[l], dp[newInd] + get<2>(orders[j]));
                }
            }
            //print_dp(dp, "After processing order j = " + to_string(j));
            j--;
    }

    ll ans = 0;
    for (int i = 0; i < dp.size(); i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << "\n";
            
}
