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
        int N; cin >> N;
        string s; cin >> s;
        map<char, int> freq;
        for (char c : s) {
            freq[c]++;
        }

        int minCount = INT_MAX, maxCount = INT_MIN;
        char minChar = '\0', maxChar = '\0';
        for (const auto& kv : freq) {
            char character = kv.first;
            int count = kv.second;

            if (count < minCount) {
                minCount = count;
                minChar = character;
            }
            if (count >= maxCount) {
                maxCount = count;
                maxChar = character;
            }
        }
        int minIdx = s.find(minChar);
        s[minIdx] = maxChar;
        cout << s << endl;
    }
}
