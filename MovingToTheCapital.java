import java.util.*;

public class MovingToTheCapital {
    static HashSet<Integer>[] edge;
    static int[] dist;

    static HashSet<Integer>[] freeEdges;
    static HashSet<Integer>[] backFreeEdge;
    static int[][] outDegree;
    static int[][] dp;

    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int tests = io.nextInt();
        for (int t = 0; t < tests; t++) {
            //input
            int N = io.nextInt();
            int M = io.nextInt();
            edge = new HashSet[N];
            for (int i = 0; i<N; i++) {
                edge[i] = new HashSet<>();
            }
            for (int i = 0; i<M; i++) {
                int u = io.nextInt()-1;
                int v = io.nextInt()-1;
                edge[u].add(v);
            }

            //calculate d_i
            dist = new int[N];
            Arrays.fill(dist, Integer.MAX_VALUE);
            dist[0] = 0;
            Queue<Integer> bfs = new LinkedList<>();
            bfs.add(0);
            while (!bfs.isEmpty()) {
                int top = bfs.poll();
                if (dist[top] == Integer.MAX_VALUE) continue;
                HashSet<Integer> adj = edge[top];
                if (!adj.isEmpty()) {
                    for (int e : adj) {
                        if (dist[e] == Integer.MAX_VALUE) {
                            dist[e] = dist[top] + 1;
                            bfs.add(e);
                        }
                    }
                }
            }




            dp = new int[2][N];
            outDegree = new int[2][N];
            for  (int i = 0; i<N; i++) {
                dp[0][i] = dist[i];
            }
            freeEdges = new HashSet[N];
            backFreeEdge = new HashSet[N];
            for (int i = 0; i<N; i++) {
                freeEdges[i] = new HashSet<>();
                backFreeEdge[i] = new HashSet<>();
            }
            for (int i = 0; i<N; i++) {
                for (Integer k : edge[i]) {
                    if (dist[i]<dist[k]) {
                        freeEdges[i].add(k);
                        backFreeEdge[k].add(i);
                        outDegree[0][i]++;
                        outDegree[1][i]++;
                    }
                }
            }
            topo(0);
            for (int i = 0; i<N; i++) {
                dp[1][i] = dp[0][i];
            }
            TreeMap<Integer, HashSet<Integer>> order = new TreeMap<>();
            for (int i = 0; i<N; i++) {
                if (order.containsKey(-1*dist[i])) {
                    order.get(-1*dist[i]).add(i);
                }
                else {
                    order.put(-1*dist[i], new HashSet<>());
                    order.get(-1*dist[i]).add(i);
                }
            }
            for (Integer d : order.keySet()) {
                for (Integer node : order.get(d)) {
                    for (Integer adj : edge[node]) {
                        if (dist[node]<dist[adj])
                            dp[1][node] = Math.min(dp[1][node], dp[1][adj]);
                        else
                            dp[1][node] = Math.min(dp[1][node], dp[0][adj]);
                    }
                }
            }

            for (int i = 0; i<N; i++) {
                System.out.print(Math.min(dp[0][i], dp[1][i]) + " ");
            }
            System.out.println();


        }
    }
    static void topo(int type) {
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < outDegree.length; i++) {
            if (outDegree[type][i] == 0) {
                q.add(i);
            }
        }

        while (!q.isEmpty()) {
            int node = q.poll();

            for (int next : backFreeEdge[node]) {
                outDegree[type][next]--;
                if (outDegree[type][next] == 0) q.add(next);
            }

            for (Integer adj : edge[node]) {
                if (dist[node]<dist[adj])
                    dp[0][node] = Math.min(dp[0][node], dp[0][adj]);
            }
        }
    }

}


