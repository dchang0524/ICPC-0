#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    cout.flush();
    int ans; cin >> ans;
    return ans;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        int a = query(1, N/4);
        int b = query(N/4 + 1, N/2);
        int c = query(N/2 + 1, N/4*3);
        int s = a + b + c;
        if (s <= 1) {
            //K > N/4
            int d = 1 - (a || b || c);
            int start = b*N/4 + c*(N/2) + d*(N/4 * 3) + 1;
            int end = start - 1 + N/4;
            //bsearch for the first d where (l, l + d -1) == 0 such that l <= start and l+d-1 >= end
            int lo = N/4;
            int hi = N - 1;
            hi++;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                int toAdd = mid - (end - start + 1);
                int cStart = start;
                int cEnd = min(end + toAdd, N);
                cStart = start - (toAdd - (cEnd - end));
                if (query(cStart, cEnd) == 0) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            cout << "! " << lo << endl;
            cout.flush();
        }
        else {
            //K <= N/4
            int start = 1;
            if (a == 0) {
                start = N/2;
            } 
            int end = start + N/4 - 1;
            //bsearch for the first d where (start, start + d - 1) = 0
            int lo = 2;
            int hi = N/4 - 1;
            hi++;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (query(start, start + mid - 1) == 1) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            cout << "! " << lo << endl;
            cout.flush();
        }

    }
}
