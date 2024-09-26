import java.util.*;
import java.io.*;

public class PasswordCracking {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int N = io.nextInt();
            System.out.println("? 0");
            StringBuilder ans = new StringBuilder();
            int in = io.nextInt();
            if (in == 0) {
                ans.append("1".repeat(N));
                System.out.println("! " + ans);
            }
            else {
                ans.append("0");
                //append to back of String
                while (ans.length()<N) {
                    ans.append("1");
                    System.out.println("? " + ans);
                    in = io.nextInt();
                    if (in == 1) {
                        continue;
                    }
                    ans.deleteCharAt(ans.length()-1);
                    ans.append("0");
                    System.out.println("? " + ans);
                    in = io.nextInt();
                    if (in == 1) {
                        continue;
                    }
                    ans.deleteCharAt(ans.length()-1);
                    break;
                }
                if (ans.length() == N) {
                    System.out.println("! " + ans);
                }
                else {
                    while (ans.length()<N) {
                        ans.insert(0,"1");
                        System.out.println("? " + ans);
                        in = io.nextInt();
                        if (in == 1) {
                            continue;
                        }
                       ans.replace(0, 1, "0");
                    }
                    System.out.println("! " + ans);
                }
            }
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
