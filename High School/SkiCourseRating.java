import java.util.*;
import java.io.*;

public class SkiCourseRating {
    public static void main(String[] args) throws IOException {
       // Kattio io = new Kattio();
       Kattio io = new Kattio("skilevel");
        int M = io.nextInt();
        int N = io.nextInt();
        int T = io.nextInt();
        int[][] height = new int[M][N];
        int[][] multiplier = new int[M][N];
        for (int i = 0; i<M; i++) {
            for (int j = 0; j<N; j++) {
                height[i][j] = io.nextInt();
            }
        }
        for (int i = 0; i<M; i++) {
            for (int j = 0; j<N; j++) {
                multiplier[i][j] = io.nextInt();
            }
        }
        TreeSet<Edge> edges = new TreeSet<>();
        int[] dx = {1, -1, 0, 0};
        int[] dy = {0, 0, 1, -1};
        for (int i = 0; i<M; i++) {
            for (int j = 0; j<N; j++) {
                for (int k = 0; k<4; k++) {
                    int x = i+dx[k];
                    int y = j+dy[k];
                    if (x>=0 && x<M && y<N && y>=0) {
                        int d = Math.abs(height[i][j]-height[x][y]);
                        Pair p1 = new Pair(i,j);
                        Pair p2 = new Pair(x, y);
                        if (!edges.contains(new Edge(d, p2, p1))) {
                            edges.add(new Edge(d, p1, p2));
                        }
                    }
                }
            }
        }
        //System.out.println(edges);
        int[][] ans = new int[M][N];
        UnionFind graph = new UnionFind(M*N); //(x,y) -> x*N+y
        //System.out.println(Arrays.toString(graph.adj));
        for (Edge curr : edges) {
            Pair a = curr.a;
            Pair b = curr.b;
            int x = a.a*N+a.b;
            int y = b.a*N+b.b;
            if (graph.connected(x, y)) {
                continue;
            }
            int comp1 = graph.find(x);
            int comp2 = graph.find(y);
            if (graph.sizes[comp1] >= T) {
                if (graph.sizes[comp2] < T) {
                    graph.update(comp2, curr.d, ans);
                }
            }
            else {
                if (graph.sizes[comp2]>=T) {
                    graph.update(comp1, curr.d, ans);
                }
                else {
                    if (graph.sizes[comp1] + graph.sizes[comp2] >= T) {
                        graph.update(comp1, curr.d, ans);
                        graph.update(comp2, curr.d, ans);
                    }
                }
            }

            graph.union(x, y);
//            System.out.println("Edge: " + curr);
//            System.out.println("Union " + x + " " + y);
//            System.out.println("Adj: " + Arrays.toString(graph.adj));
//            System.out.println("Sizes: " + Arrays.toString(graph.sizes));
//            System.out.println("Component: " + Arrays.toString(graph.nodes));
        }
        if (T==1) {
            ans = new int[M][N];
        }
        long sum = 0;
        for (int i = 0; i<M; i++) {
            for (int j = 0; j<N; j++) {
                sum += (ans[i][j]*multiplier[i][j]);
            }
        }

//        for (int i = 0; i<M; i++) {
//            for (int j = 0; j<N; j++) {
//                io.print(ans[i][j] + " ");
//            }
//            io.println();
//        }


        io.println(sum);
        io.close();
    }
    public static class UnionFind {
        int[] nodes;
        int[] sizes;
        int components;
        List<Integer>[] adj;
        boolean[] visited;
        UnionFind(int n) {
            nodes = new int[n];
            sizes = new int[n];
            adj = new ArrayList[n];
            components = n;
            visited = new boolean[n];
            for (int i = 0; i < n; i++) {
                nodes[i] = i;
                sizes[i] = 1;
                adj[i] = new ArrayList<>();
            }
        }
        void union (int p, int q) {
            int i = find(p);
            int j = find(q);
            if (i == j) return;
            components--;
            if (sizes[i] < sizes[j]) {
                nodes[i] = nodes[j];
                sizes[j] += sizes[i];
                adj[j].add(i);
                adj[i].add(j);
            } else {
                nodes[j] = nodes[i];
                sizes[i] += sizes[j];
                adj[j].add(i);
                adj[i].add(j);
            }
        }
        int find (int index) {
            while (nodes[index] != index) {
                nodes[index] = nodes[nodes[index]];
                index = nodes[index];
            }
            return index;
        }
        boolean connected (int p, int q) {
            return find(p) == find(q);
        }
        void update (int component, int value, int[][] val) {
            dfs(component, value, val);
        }
        void dfs(int node, int value, int[][] val) {
            if (visited[node]) {
                return;
            }
            int y = node % val[0].length;
            int x = (node - y)/val[0].length;
            val[x][y] = value;
            visited[node] = true;
            for (Integer neighbor : adj[node]) {
                dfs(neighbor, value, val);
            }
        }
    }

    public static class Edge implements Comparable<Edge>{
        int d;
        Pair a;
        Pair b;
        public Edge(int d, Pair a, Pair b) {
            this.d = d;
            this.a = a;
            this.b = b;
        }


        public int compareTo(Edge o) {
            if (d == o.d) {
                if(a.compareTo(o.a) == 0) {
                    return b.compareTo(o.b);
                }
                return a.compareTo(o.a);
            }
            return Integer.compare(d, o.d);
        }

        public String toString() {
            return "Distance: " + d + " Points " + a + " <-> " + b;
        }

    }
    public static class Pair implements Comparable<Pair> {
        int a;
        int b;
        public Pair(int x, int y) {
            a = x;
            b = y;
        }
        public int compareTo(Pair o) {
            if (a == o.a) {
                return Integer.compare(b, o.b);
            }
            return Integer.compare(a, o.a);
        }
        public String toString() {
            return "("+a + ", " + b + ")";
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
