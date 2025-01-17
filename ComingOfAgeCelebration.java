import java.util.*;
import java.io.*;

public class ComingOfAgeCelebration {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int N = io.nextInt();
        int[] stones = new int[N];
        for (int i = 0; i < N; i++) {
            stones[i] = io.nextInt();
        }
        BIT received = new BIT(N);
        for (int i = 0; i < N; i++) {
            if (stones[i] + received.prefSum(i) < N-i-1) {
                received.add(i+1, 1);
                received.add(i + stones[i] + received.prefSum(i) + 1, -1);
                stones[i] -= stones[i] + received.prefSum(i);
            }
            else {
                received.add(i+1, 1);
                stones[i] -= N-i-1;
            }
        }
        for (int i = 0; i < N; i++) {
            io.print(stones[i] + received.prefSum(i) + " ");
        }
        io.close();
    }   
    public static class BIT {
        private final int[] bit;
        private final int len;
    
    
        public BIT(int len) {
            bit = new int[len + 1];
            this.len = len;
        }
    
    
        public void add(int ind, int val) {
            ind++;
            for (; ind <= len; ind += ind & -ind) { bit[ind] += val; }
        }
    
    
        public int prefSum(int ind) { //sum [0,ind]
            ind++;
            int sum = 0;
            for (; ind > 0; ind -= ind & -ind) { sum += bit[ind]; }
            return sum;
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