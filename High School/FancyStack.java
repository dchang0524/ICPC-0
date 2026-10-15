import java.util.*;
import java.io.*;

public class FancyStack {
    static long mod = 998244353;
    public static void main (String[] args) {
        Kattio io = new Kattio();
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int N = io.nextInt();
            TreeMap<Integer, Integer> nums = new TreeMap<>();
            for (int i = 0; i<N; i++) {
                int a = io.nextInt();
                if (nums.containsKey(a)) {
                    nums.put(a, nums.get(a)+1);
                }
                else {
                    nums.put(a, 1);
                }
            }
            int M = nums.keySet().size();
            int[] numsNum = new int[M];
            int[] numsCnt = new int[M];
            int cnt = 0;
            for (Integer v : nums.keySet()) {
                numsNum[cnt] = v;
                numsCnt[cnt] = nums.get(v);
                cnt++;
            }
            int[] lessThan = new int[M];
            for (int i = 1; i<M; i++) {
                lessThan[i] = lessThan[i-1] + numsCnt[i-1];
            }
            long[][] dp = new long[N/2+1][M];
            for (int j = 1; j<M; j++) {
                dp[1][j] = lessThan[j]*numsCnt[j];
            }

            for (int i = 2; i<=N/2 ;i++) {
                int length = 2*i;
                int prevLength = length-2;
                long[] difference = new long[M];
                for (int j = 0; j<M-1; j++) {
                    difference[j+1]  += dp[i-1][j]*Math.max(lessThan[j]-(prevLength-1), 0);
                    difference[j+1] %= mod;
                }
                long[] prefix = new long[M];
                prefix[0] = difference[0];
                for (int j = 1; j<M; j++) {
                    prefix[j] = prefix[j-1] + difference[j];
                    prefix[j] %= mod;
                }
                for (int j = 0; j<M; j++) {
                    dp[i][j] = prefix[j]*numsCnt[j];
                }
            }

            long ans = dp[N/2][M-1];
            long[] factorial = new long[N+1];
            factorial[1] = 1;
            for (int i = 2; i<N+1; i++) {
                factorial[i] = factorial[i-1]*i;
                factorial[i] %= mod;
            }

            for (int i = 0; i<M; i++) {
                ans *= exp(factorial[numsCnt[i]], mod-2);
                ans %= mod;
            }




            io.println(ans);
        }
        io.close();
    }
    public static long exp(long x, long n) {
        assert (n >= 0);
        long m = mod;
        x %= m;
        // note: m * m must be less than 2^63 to avoid long overflow
        long res = 1;
        while (n > 0) {
            if (n % 2 == 1) { res = res * x % m; }
            x = x * x % m;
            n /= 2;
        }
        return res;
    }
    public static class Kattio extends PrintWriter {
        private BufferedReader r;
        private StringTokenizer st;
        // standard input
        public Kattio() { this(System.in, System.out); }
        public Kattio(InputStream i, OutputStream o) {
            super(o);
            r = new BufferedReader(new InputStreamReader(i));
        }
        // USACO-style file input
        public Kattio(String problemName) throws IOException {
            super(problemName + ".out");
            r = new BufferedReader(new FileReader(problemName + ".in"));
        }
        // returns null if no more input
        public String next() {
            try {
                while (st == null || !st.hasMoreTokens())
                    st = new StringTokenizer(r.readLine());
                return st.nextToken();
            } catch (Exception e) { }
            return null;
        }
        public int nextInt() { return Integer.parseInt(next()); }
        public double nextDouble() { return Double.parseDouble(next()); }
        public long nextLong() { return Long.parseLong(next()); }
    }

}
