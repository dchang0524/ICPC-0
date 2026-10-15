import java.util.*;

public class BesslaMotors {
    public static void main (String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt(); //nodes
        int M = io.nextInt(); //edges
        int C = io.nextInt(); //sources
        int R = io.nextInt(); //radius
        int K = io.nextInt(); //required visits

        List<Edge>[] edges = new List[N];
        for (int i = 0; i<N; i++) {
            edges[i] = new ArrayList<>();
        }
        for (int i = 0; i<M; i++) {
            int a = io.nextInt()-1;
            int b = io.nextInt()-1;
            int c = io.nextInt();
            edges[a].add(new Edge(b, c, -1));
            edges[b].add(new Edge(a, c, -1));
        }

        long[] dist = new long[N];
        PriorityQueue<Edge> pq = new PriorityQueue<>();
        Arrays.fill(dist, Long.MAX_VALUE);
        HashMap<Integer, Long>[] sources = new HashMap[N];
        HashSet<Integer>[] visited = new HashSet[N];
        for (int i = 0; i<N; i++) {
            sources[i] = new HashMap<>();
            visited[i] = new HashSet<>();
        }
        for (int i = 0; i<C; i++) {
            dist[i] = 0;
            pq.add(new Edge(i, 0, i));
            sources[i].put(i, Long.valueOf(0));
        }
        //if a node is visited by K sources, we continue
        //if a node is already visited by that source we continue
        while (!pq.isEmpty()) {
            Edge curr = pq.poll();
            long currentDistance = curr.distance;
            int node = curr.node;
            int source = curr.source;
            if (visited[node].size()>K) {
                continue;
            }
            if (visited[node].contains(source)) {
                continue;
            }
            if (sources[node].containsKey(source) && sources[node].get(source) != currentDistance) {
                continue;
            }
            visited[node].add(source);

            for (Edge i : edges[node]) {
                long newDist = currentDistance+i.distance;
                if (visited[i.node].size()>K) {
                    continue;
                }
                if (sources[i.node].containsKey(source) && newDist< sources[i.node].get(source) && newDist<=R) {
                    sources[i.node].put(source, newDist);
                    pq.add(new Edge(i.node, newDist, source));
                }
                else if (!sources[i.node].containsKey(source) && newDist<=R) {
                    sources[i.node].put(source, newDist);
                    pq.add(new Edge(i.node, newDist, source));
                }
            }
        }
        int num = 0;
        for (int i = C; i<N; i++) {
            if (sources[i].keySet().size()>=K) {
                num++;
            }
        }
        System.out.println(num);
        for (int i = C; i<N; i++) {
            if (sources[i].keySet().size()>=K) {
                System.out.println(i+1);
            }
        }

    }

    public static class Edge implements Comparable<Edge> {
        long distance;
        int node;
        int source;
        public Edge(int node, long distance, int source) {
            this.distance = distance;
            this.node = node;
            this.source = source;
        }


        public int compareTo(Edge o) {
            if (distance == o.distance) {
                if (node == o.node) {
                    return Integer.compare(source, o.source);
                }
                return Integer.compare(node, o.node);
            }
            return Long.compare(distance, o.distance);
        }
        public String toString() {
            return " Node: " + node + " Distance: " + distance;
        }


    }

}