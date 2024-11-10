import java.io.*;
import java.util.*;
public class MoortalCowmbat {
    public static void main(String[] args) throws IOException {
        Kattio io = new Kattio("cowmbat");
        int N = io.nextInt();
        int M = io.nextInt();
        int K = io.nextInt();
        String[] lowerCase = {"a", "b", "c", "d", "e", "f", "g", "h",
                "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
        HashMap<String, Integer> caseNum = new HashMap<>();
        for (int i = 0; i<lowerCase.length; i++) {
            caseNum.put(lowerCase[i],i);
        }
        String s = io.next();
        String[] letter = s.split("");
        int[] letterNum = new int[N];
        for (int i = 0; i<N; i++) {
            letterNum[i] = caseNum.get(letter[i]);
        }
        int[][] minCost = new int[M][M];
        for (int i = 0; i<M; i++) {
            for (int j = 0; j<M; j++) {
                minCost[i][j] = io.nextInt();
            }
        }
        for (int k = 0; k < M; k++) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++) {
                    int newDist = minCost[i][k] + minCost[k][j];
                    if (newDist < minCost[i][j]) {
                        minCost[i][j] = newDist;
                    }
                }
            }
        }


        int[][] prefixCost = new int[N][M];
        for (int m = 0; m<M; m++) {
            prefixCost[0][m] = minCost[letterNum[0]][m];
            for (int i = 1; i<N; i++) {
                prefixCost[i][m] = prefixCost[i-1][m] + minCost[letterNum[i]][m];
            }
        }

        int[][] dp = new int[N][M];
        for (int i = 0; i<N; i++) {
            for (int j = 0; j<M; j++) {
                dp[i][j] = Integer.MAX_VALUE;
            }
        }
        //dp[i][c] minimum cost to fill from 0 to i given the char[i] = c and the current streak of c is at least K
        for (int m = 0; m<M; m++) {
            dp[K-1][m] = prefixCost[K-1][m];
        }
        for (int i = K; i<N; i++) {
            for (int m = 0; m<M; m++) {
                dp[i][m] = Math.min(dp[i][m], dp[i-1][m]+minCost[letterNum[i]][m]);
                for (int c = 0; c<M; c++) {
                    if (dp[i-K][c] != Integer.MAX_VALUE) {
                        dp[i][m] = Math.min(dp[i][m], dp[i-K][c] + prefixCost[i][m] - prefixCost[i-K][m]);
                    }
                }
            }
        }
        int ans = Integer.MAX_VALUE;
        for (int i = 0; i<M; i++) {
            ans = Math.min(ans, dp[N-1][i]);
        }
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
