import java.io.*;
import java.util.*;

public class StampPainting {
    static long mod = 1000000007; //10^9 + 7
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

    public static void main (String[] args) throws IOException {
        Kattio io = new Kattio("spainting");
        //Kattio io = new Kattio();
        int N = io.nextInt();
        int M = io.nextInt();
        int K = io.nextInt();

        //define block -> contiguous with the same color
        //any combination of colors that has at least one block with size >=K is valid
        //case work based on the first index of a block of the first block
        //dp[i] = number of ways to fill until index i such that there are no blocks
        ///dp[i] = dp[i-1]*M - dp[i-k+1]*(M-1)
        long[] dp = new long[N];
        for (int i = 0; i<K-1; i++) {
            dp[i] = exp(M, i+1);
        }
        dp[K-1] = dp[K-2]*M-M;
        dp[K-1] %= mod;
        if (dp[K-1]<0) {
            dp[K-1] += mod;
        }
        for (int i = K; i<N; i++) {
            dp[i] = ((dp[i-1]*M)%mod) - ((dp[i-K]*(M-1))%mod);
            if (dp[i]<0) {
                dp[i] += mod;
            }
        }
        long ans = M*exp(M, N-K);
        ans %= mod;
        for (int i = 0; i<N-K; i++) {
            //first block starts at i+1
            //first block has to end at least i+K
            long curr = (dp[i]*(M-1)%mod)*exp(M, N-1-i-K)%mod;
            ans += curr;
            ans %= mod;
        }
       // System.out.println(Arrays.toString(dp));
        io.println(ans);
        io.close();
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
