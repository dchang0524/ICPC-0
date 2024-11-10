import java.util.*;
import java.io.*;

public class CircularBarnRevisited {
    public static void main(String[] args) throws IOException {
        Kattio io = new Kattio("cbarn2");
        //Kattio io = new Kattio();
        int N = io.nextInt();
        int K = io.nextInt();
        int[] nums = new int[N];
        for (int i = 0; i<N; i++) {
            nums[i] = io.nextInt();
        }

        long ans = Integer.MAX_VALUE;
        for (int i = 0; i<N; i++) {
            int[] curr = new int[N];
            for (int k = 0; k<N; k++) {
                curr[k] = nums[(i+k)%N];
            }
            long[][][] dp = new long[N][N][K+1]; //dp[i][j][k] = minimum distance given you filled until index i and the last door is at j and you opened k doors
            //curr[0] is a door
            for (int a = 0; a<N; a++) {
                for (int b = 0; b<N; b++) {
                    for (int c = 0; c<K+1; c++) {
                        dp[a][b][c] = Integer.MAX_VALUE;
                    }
                }
            }
            dp[0][0][1] = 0;
            for (int k = 1; k<N; k++) {
                dp[k][0][1] = dp[k-1][0][1] + (long)curr[k]*(k);
            }
            for (int k = 0; k<K+1; k++) {
                dp[0][0][k] = 0;
            }

            for (int a = 1; a<N; a++) {
                for (int b = 0; b<a; b++) {
                    for (int c = 2; c<K+1; c++) {
                        if (dp[a-1][b][c] != Integer.MAX_VALUE)
                            dp[a][b][c] = Math.min(dp[a][b][c], dp[a-1][b][c] + (a-b)*curr[a]);
                        if (dp[a-1][b][c-1] != Integer.MAX_VALUE)
                            dp[a][a][c] = Math.min(dp[a][a][c], dp[a-1][b][c-1]);
                    }
                }
            }
            for (int b = 0; b<N; b++) {
                for (int k = 0; k<K+1; k++) {
                    ans = Math.min(ans, dp[N-1][b][k]);
                }
            }

//            System.out.println("Cycle Shift: " + i);
//            System.out.println(Arrays.toString(curr));
//            for (int k = 0; k<K; k++) {
//                System.out.println("k: " + k);
//                for (int a = 0; a<N; a++) {
//                    for (int b = 0; b<N; b++) {
//                        System.out.print(dp[a][b][k] + " ");
//                    }
//                    System.out.println();
//                }
//            }
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
