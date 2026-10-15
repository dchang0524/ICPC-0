import java.util.*;

public class Portals {
    public static void main (String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        PriorityQueue<Edge> pq = new PriorityQueue<>();
        List<Integer>[] portals = new List[2*N+1];
        UnionFind graph = new UnionFind(4*N);
        for (int i = 1; i<2*N+1; i++) {
            portals[i] = new ArrayList<>();
        }
        for (int i = 0; i<N; i++) {
            int w = io.nextInt();
            for (int j = 0; j<4; j++) {
                //number of node is 4*i + j
                int p = io.nextInt();
                portals[p].add(4*i+j);
            }
            graph.union(4*i, 4*i+1);
            graph.union(4*i+2, 4*i+3);
            pq.add(new Edge(4*i, 4*i+2, w));
        }
        for (int i = 1; i<2*N+1; i++) {
            int a = portals[i].get(0);
            int b = portals[i].get(1);
            graph.union(a, b);
        }
        long cost = 0;
        while (!pq.isEmpty()) {
            Edge curr = pq.poll();
            if (!graph.connected(curr.a, curr.b)) {
                graph.union(curr.a, curr.b);
                cost += curr.weight;
            }
        }
        System.out.println(cost);
    }
    static class Edge implements Comparable<Edge> {
        int a;
        int b;
        int weight;
        public Edge(int a, int b, int weight) {
            this.a = a;
            this.b = b;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge o) {
            if (weight == o.weight) {
                if (a == o.a) {
                    return Integer.compare(b, o.b);
                }
                return Integer.compare(a, o.a);
            }
            return Integer.compare(weight, o.weight);
        }
    }
    public static class UnionFind {
        int[] nodes;
        int[] sizes;
        int components;
        UnionFind(int n) {
            nodes = new int[n];
            sizes = new int[n];
            components = n;
            for (int i = 0; i < n; i++) {
                nodes[i] = i;
                sizes[i] = 1;
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
            } else {
                nodes[j] = nodes[i];
                sizes[i] += sizes[j];
            }
        }
        int find (int index) {
            while (nodes[index] != index) {
                nodes[index] = nodes[nodes[index]];
                index = nodes[index];
            }
            return index;
        }


        int size (int index) {
            return sizes[index];
        }
        boolean connected (int p, int q) {
            return find(p) == find(q);
        }
    }


}
