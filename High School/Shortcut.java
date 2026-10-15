import java.util.*;
import java.io.*;

public class Shortcut {
    public static void main (String[] args) {
        Kattio io = new Kattio();
        int N = io.nextInt();
        int M = io.nextInt();
        int T = io.nextInt();
        int[] num  = new int[N];
        for (int i = 0; i<N; i++) {
            num[i] = io.nextInt();
        }
        List<Edge>[] edges = new List[N];
        for (int i = 0; i<N; i++) {
            edges[i] = new ArrayList();
        }
        for (int i = 0; i<M; i++) {
            int a = io.nextInt()-1;
            int b = io.nextInt()-1;
            int d = io.nextInt();
            edges[a].add(new Edge(b, d));
            edges[b].add(new Edge(a, d));
        }
        long[] dist = new long[N];
        PriorityQueue<Edge> pq = new PriorityQueue<>();
        Arrays.fill(dist, Long.MAX_VALUE);
        int start = 0;
        dist[start] = 0;
        pq.add(new Edge(0, 0));
        while (!pq.isEmpty()) {
            Edge curr = pq.poll();
            long currentDistance = curr.distance;
            int node = curr.end;
            if (currentDistance != dist[node]) { continue; }
            for (Edge i : edges[node]) {
                if (currentDistance + i.distance < dist[i.end]) {
                    dist[i.end] = currentDistance + i.distance;
                    pq.add(new Edge(i.end, dist[i.end]));
                }
            }
        }





        io.close();
    }
    public static class Node implements Comparable<Node> {

        @Override
        public int compareTo(Node o) {
            return 0;
        }
    }
    public static class Edge implements Comparable<Edge> {
        long distance;
        int end;
        public Edge(int end, long distance) {
            this.distance = distance;
            this.end = end;
        }


        public int compareTo(Edge o) {
            if (distance == o.distance) {
                return Integer.compare(end, o.end);
            }
            return Long.compare(distance, o.distance);
        }
        public String toString() {
            return " End: " + end + " Distance: " + distance;
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
