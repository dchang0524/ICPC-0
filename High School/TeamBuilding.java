import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class TeamBuilding {
    static long mod = 1000000009;
    public static void main(String[] args) throws IOException {
       //Kattio io = new Kattio();
        Kattio io = new Kattio("team");
        int N = io.nextInt();
        int M = io.nextInt();
        int K = io.nextInt();
        int[] win = new int[N];
        for (int i = 0; i<N; i++) {
            win[i] = io.nextInt();
        }
        int[] lose = new int[M];
        for (int i = 0; i<M; i++) {
            lose[i] = io.nextInt();
        }
        Arrays.sort(win);
        Arrays.sort(lose);

        long[][][] dp = new long[K+1][N][M];
        for (int i = 0; i<N; i++) {
            for (int j = 0; j<M; j++) {
                dp[0][i][j] = 1;
            }
        }
        //if i == 0
        if (win[0]>lose[0]) {
            dp[1][0][0] = 1;
        }

        for (int j = 1; j<M; j++) {
            dp[1][0][j] = dp[1][0][j-1];
            if (win[0]>lose[j]) {
                dp[1][0][j] += 1;
                dp[1][0][j] %= mod;
            }
        }
        for (int i = 1; i<N; i++) {
            dp[1][i][0] = dp[1][i-1][0];
            if (win[i]>lose[0]) {
                dp[1][i][0] += 1;
                dp[1][i][0] %= mod;
            }
        }

        for (int k = 1; k<=K; k++) {
            for (int i = 1; i<N; i++) {
                for (int j = 1; j<M; j++) {
                    if (k>Math.min(i+1, j+1)) {
                        continue;
                    }
                    dp[k][i][j] = dp[k][i-1][j] + dp[k][i][j-1] - dp[k][i-1][j-1];
                    dp[k][i][j] %= mod;
                    if (dp[k][i][j] < 0)
                        dp[k][i][j] += mod;
                    if (win[i]>lose[j]) {
                        dp[k][i][j] += dp[k-1][i-1][j-1];
                        dp[k][i][j] %= mod;
                    }
                }
            }
        }





        io.println(dp[K][N-1][M-1]);
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
