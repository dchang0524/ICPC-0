#include <bits/stdc++.h>


using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, X;
    int sumSkills = 0;
    cin >> N >> X;
    vector<int> skill(N);
    for (int i = 0; i<N; i++) {
        cin >> skill[i];
        sumSkills += skill[i];
    }
    sort(skill.begin(), skill.end());
    // for (int i = 0; i<N; i++) {
    //     cout << skill[i] << " ";
    // }
    // cout << "\n";
    //cout << "input processed\n";

    //iterating from right to left, we assign +, -, or 0 to a person
        //essentially, + is starting a group, and - is ending a group
            //when you end a group, the current '-' can close any of one of the unpaired '+'
        //during this process, there can't be more -'s than +'s
        //also, if the (# of +'s) - (# of -'s) = 0, the current element must be a '+' or in a group of himself
            //because if it were 0, there are no recurring groups we can place the current element
            //if the (# of +'s) - (# of -'s) > 0, that means there's a recurring group that will end past this element
                //so the current element can go inside that group
                //and also, there are (# of +'s) - (# of -'s) groups he can go inside

    vector<vector<ll>> dp(sumSkills+1, vector<ll>(N+1)); 
    //dp[x][p] -> the number of ways to form x with p cumulative +'s  
    dp[skill[N-1]][1] = 1;
    dp[0][0] = 1;
    for (int i = N-2; i>=0; i--) {
        vector<vector<ll>> ndp(sumSkills+1, vector<ll>(N+1)); 
        for (int x = 0; x < sumSkills+1; x++) {
            for (int p = 0; p<=N-(i+1); p++) {
                if (x+skill[i] <= sumSkills) {
                    ndp[x+skill[i]][p+1] += dp[x][p]; //if a person becomes a '+'
                    ndp[x+skill[i]][p+1] %= MOD;
                }
                if (p > 0) {
                    ndp[x][p] += p*dp[x][p]; //if a person goes inside a group, there are currently p recurring groups
                    ndp[x][p] %= MOD;

                    if (x-skill[i] >= 0) { //or you could check whether dp[x][p]>0, as this x>skill[i] if this is a valid configuration
                        ndp[x-skill[i]][p-1] += p*dp[x][p]; //if a person becomes a '-'
                        ndp[x-skill[i]][p-1] %= MOD;
                    }
                    
                }
                ndp[x][p] += dp[x][p]; //if a person is in a team of himself
                ndp[x][p] %= MOD;
            }
        }

        // cout << "Contents of ndp after iteration i = " << i << ":\n";
        // for (int x = 0; x <= sumSkills; x++) {
        //     for (int p = 0; p <= N; p++) {
        //         if (ndp[x][p] != 0) {
        //             cout << "x: " << x << " p: " << p << " ndp[x][p]:" << ndp[x][p] << "\n";
        //         }
        //     }
        // }
        // cout << "\n";

        dp = ndp;
    }

    ll ans = 0;
    for (int x = 0; x<X+1 && x<sumSkills+1; x++) {
        ans += dp[x][0];
        ans %= MOD;
    }
    cout << ans;

}
