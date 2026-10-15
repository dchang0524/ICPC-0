import java.util.*;

public class Cowmpetency {
    private static final long mod = 1000000007;
    private static long exp(long x, long n, long m) {
        x %= m;
        long res = 1;
        while (n > 0) {
            if (n % 2 == 1) { res= res*x %m; }
            x= x*x %m;
            n/= 2;
        }
        return res;
    }

    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        int Q = io.nextInt();
        int C = io.nextInt();

        int[] A = new int[Q];
        int[] H = new int[Q];
        for (int i = 0; i<Q; i++) {
            A[i] = io.nextInt()-1;
            H[i] = io.nextInt()-1;
        }
        Arrays.sort(A);
        Arrays.sort(H);

        //from h_i > a_i, a_i-1, ..., 1 and a_i+1, a_i+2, ... h_i -1 <= max(a_i, a_i-1, ..., 1)
        //all a_i are distinct
        //a_i < a_{i+1} < h_i < h_{i+1} is impossible
        //either a_i < h_i <= a_{i+1} < h_{i+1}
        //or a_i < a_{i+1} < h_{i} == h{i+1}
        //dp[i][v] maximum value -> number of ways to fill 1 to index[i] such that the maximum value from 1 to i is v
        TreeMap<Integer, Integer> value = new TreeMap<>();
        for (int i = 0; i<H.length; i++) {
            if (!value.containsKey(H[i])) {
                value.put(H[i], A[i]);
            }
        }

        int[] index = new int[value.keySet().size()*2];
        int cnt = 0;
        for (Integer k : value.keySet()) {
            index[cnt] = value.get(k);
            cnt++;
            index[cnt] = k;
            cnt++;
        }

        long[][] dp = new long[index.length][C+1];
        //fill dp[0]
        for (int i = 1; i<C+1; i++) {
            dp[0][i] = exp(i, index[0]+1, mod)-exp(i-1, index[0]+1, mod);
            dp[0][i] %= mod;
            if (dp[0][i] < 0) {
                dp[0][i] += mod;
            }
        }
        //fill dp
        for (int i = 1; i<dp.length; i++) {
            long[] difference = new long[C+1];
            if (i %2 == 0) { //type a
                long[] prefix = new long[C+1];
                for (int k = 1; k<prefix.length; k++) {
                    prefix[k] = prefix[k-1] + dp[i-1][k];
                    prefix[k] %= mod;
                }
                for (int v = 1; v<C+1; v++) {
                    long mult = exp(v, index[i]-index[i-1], mod)-exp(v-1, index[i]-index[i-1], mod);
                    mult %= mod;
                    if (mult<0) {
                        mult += mod;
                    }
                    dp[i][v] = dp[i-1][v]*exp(v, index[i]-index[i-1], mod) + prefix[v-1]*mult;
                    dp[i][v] %= mod;
                }
            }
            else { //type h
                for (int v = 1; v<C; v++) {
                    difference[v+1] = (dp[i-1][v]*exp(v, index[i]-1-index[i-1], mod))%mod;
                }
                long sum = 0;
                for (int v = 1; v<C+1; v++) {
                    dp[i][v] = sum + difference[v];
                    dp[i][v] = dp[i][v] % mod;
                    sum += difference[v];
                    sum = sum%mod;
                }
            }

        }



        long ans = 0;
        for (int i = 1; i<C+1; i++) {
            ans += dp[dp.length-1][i];
            ans = ans%mod;
        }
        if (index[index.length-1] < N-1) {
            ans = ans*exp(C, (N-1 - index[index.length-1]), mod);
            ans%= mod;
        }
        System.out.println(ans);

    }


}
