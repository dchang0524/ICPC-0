import java.util.*;

public class StrongestFriendshipGroup {
    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        int M = io.nextInt();
        int[] deg = new int[N];
        HashSet<Integer>[] edges = new HashSet[N];
        for (int i = 0; i<N; i++) {
            edges[i] = new HashSet<>();
        }
        for (int i = 0; i<M; i++) {
            int a = io.nextInt()-1;
            int b = io.nextInt()-1;
            deg[a]++;
            deg[b]++;
            edges[a].add(b);
            edges[b].add(a);
        }

        TreeSet<Pair> degree = new TreeSet<>();
        HashSet<Integer> leftovers = new HashSet<>();
        for (int i = 0; i<N; i++) {
            degree.add(new Pair(deg[i], i));
        }
        //System.out.println(degree);
        for (int i = 0; i<N; i++) {
            leftovers.add(i);
        }
        ArrayList<Integer> order = new ArrayList<>();
       // System.out.println(degree);
        while (!degree.isEmpty()) {
            Pair lowest = degree.first();
            leftovers.remove(lowest.node);
            degree.remove(lowest);
            //System.out.println("Removing Node " + lowest.node);
            int currNode = lowest.node;
            deg[currNode] = 0;
            order.add(currNode);
            for (Integer adj : edges[currNode]) {
                if (leftovers.contains(adj)) {
                    degree.remove(new Pair(deg[adj], adj));
                    deg[adj]--;
                    degree.add(new Pair(deg[adj], adj));
               //     System.out.println("Removing Edge " + lowest.node + " " + adj);
               //     System.out.println(degree);
                }
            }
        }
        //System.out.println(order);
        Collections.reverse(order); //do DSU in this order
        UnionFind graph = new UnionFind(N);
        HashSet<Integer> current = new HashSet<>();
        deg = new int[N];
        int maxFriendship = 0;
        //System.out.println(order);
        for (int i = 0; i<order.size(); i++) {
            //add the node
            //System.out.println("Add Node " + order.get(i));
            current.add(order.get(i));
            for (Integer adj : edges[order.get(i)]) {
               // System.out.println("Add(?) Edge " + order.get(i) + " " + adj);
                if (current.contains(adj)) {
                //    System.out.println("Added edge");
                    graph.union(adj, order.get(i));
                    deg[order.get(i)]++;
                    deg[adj]++;
                }
             //   System.out.println("Degrees: " + Arrays.toString(deg));
            }
            maxFriendship = Math.max(maxFriendship, deg[order.get(i)]*graph.size(graph.find(order.get(i))));
            //System.out.println("Current Friendship: " +  deg[order.get(i)]*graph.size(graph.find(order.get(i))));
        }
        System.out.println(maxFriendship);
    }
    public static class Pair implements Comparable<Pair> {
        int degree;
        int node;
        public Pair(int deg, int v) {
            degree = deg;
            node = v;
        }
        @Override
        public int compareTo(Pair o) {
            if (degree == o.degree) {
                return Integer.compare(node, o.node);
            }
            return Integer.compare(degree, o.degree);
        }
        public String toString() {
            return ("Node: " + node + " Degree: " + degree);
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
