import java.util.List;
import java.util.*;

public class ShortestRoutes1 {
    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        int M = io.nextInt();
        List<Edge>[] edges = new List[N];
        for (int i = 0; i < N; i++) {
            edges[i] = new ArrayList<>();
        }
        for (int i = 0; i < M; i++) {
            int a = io.nextInt() - 1;
            int b = io.nextInt() - 1;
            int c = io.nextInt();
            edges[a].add(new Edge(b, c));
            edges[b].add(new Edge(a, c));
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
            if (currentDistance != dist[node]) {
                continue;
            }
            for (Edge i : edges[node]) {
                // If we can reach a neighbouring node faster,
                // we update its minimum distance
                if (currentDistance + i.distance < dist[i.end]) {
                    dist[i.end] = currentDistance + i.distance;
                    pq.add(new Edge(i.end, dist[i.end]));
                }
            }
        }
        for (int i = 0; i<N; i++) {
            System.out.println(dist[i]);
        }
    }
    static class Edge implements Comparable<Edge> {
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

}
