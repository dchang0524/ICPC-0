import java.util.*;
import java.io.*;

public class FencedIn {
    public static void main(String[] args) throws IOException {
        Kattio io = new Kattio("fencedin");
        //Kattio io = new Kattio();
        int A = io.nextInt();
        int B = io.nextInt();
        int N = io.nextInt();
        int M = io.nextInt();
        int[] xCoords = new int[N+2];
        int[] yCoords = new int[M+2];
        xCoords[1] = A;
        yCoords[1] = B;
        for (int i = 0; i<N; i++) {
            xCoords[2+i] = io.nextInt();
        }
        for (int i = 0; i<M; i++) {
            yCoords[2+i] = io.nextInt();
        }
        Arrays.sort(xCoords);
        Arrays.sort(yCoords);
        int[] xDist = new int[N+1];
        for (int i = 1; i<N+2; i++) {
            xDist[i-1] = xCoords[i]-xCoords[i-1];
        }
        int[] yDist = new int[M+1];
        for (int i = 1; i<M+2; i++) {
            yDist[i-1] = yCoords[i]-yCoords[i-1];
        }
        Arrays.sort(xDist);
        Arrays.sort(yDist);
        long ans = 0;
        ans += (long) M*xDist[0];
        ans += (long) N*yDist[0];


        long numHor = 1;
        long numVert = 1;
        TreeSet<Pair> mst = new TreeSet<>();
        for (int i = 1; i<xDist.length; i++) {
            mst.add(new Pair(xDist[i],0, i));
        }
        for (int i = 1; i<yDist.length; i++) {
            mst.add(new Pair(yDist[i],1, i));
        }
        long recent = 0;
        int totalNodes = (N+1)*(M+1);
        long connectedNodes = 0;
        while (connectedNodes < totalNodes) {
            Pair curr = mst.first();
            mst.remove(curr);
            recent = curr.a;
            if (curr.b == 0) {
                ans += (M+1-numVert)*recent;
                numHor++;
            }
            else if (curr.b == 1) {
                ans += (N+1-numHor)*recent;
                numVert++;
            }
            connectedNodes = numHor*(M+1) + numVert*(N+1) - numHor*numVert;
        }
        io.println(ans);
        io.close();

    }
    public static class Pair implements Comparable<Pair> {
        int a;
        int b;
        int c;
        public Pair(int a, int b, int c) {
            this.a = a;
            this.b = b; //0 -> horizontal, 1 -> vertical
            this.c = c;
        }
        public int compareTo(Pair o) {
            //change according to need
            if (a == o.a) {
                if (b == o.b) {
                    return Integer.compare(c, o.c);
                }
                return Integer.compare(b, o.b);
            }
            return Integer.compare(a, o.a);
        }
        public String toString() {
            return "a: " + a + " b: " + b;
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
