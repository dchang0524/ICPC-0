import java.util.*;
import java.io.*;

public class BattleForSurvive {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int n = io.nextInt();
            int[] power = new int[n];
            for (int i = 0; i<power.length; i++) {
                power[i] = io.nextInt();
            }
            long sum = 0;
            for (int i = 0; i<power.length-2; i++) {
                sum+=power[i];
            }
            System.out.println(power[power.length-1]-power[power.length-2]+sum);
        }
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