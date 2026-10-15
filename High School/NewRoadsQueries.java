import java.util.*;

public class NewRoadsQueries {
    static boolean[] visited;
    static HashSet<Integer>[] edges;
    static HashSet<Integer>[] children;
    static int[] parents;
    static TreeMap<Integer, HashSet<Integer>> levelMap;
    static int[] level;
    static List<Integer>[] jump;

    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        int M = io.nextInt();
        int Q = io.nextInt();
        UnionFind graph = new UnionFind(N+1);
        edges = new HashSet[N+1];
        for (int i = 1; i<N+1; i++) {
            edges[i] = new HashSet();
        }
        for (int i = 0; i<M; i++) {
            int a = io.nextInt();
            int b = io.nextInt();
            if (graph.find(a) != graph.find(b)) {
                edges[a].add(b);
                edges[b].add(a);
                graph.union(a, b);
            }
        }

        level = new int[N+1];
        visited = new boolean[N+1];
        children = new HashSet[N+1];
        for (int i = 1; i<N+1; i++) {
            children[i] = new HashSet();
        }
        parents = new int[N+1];
        levelMap = new TreeMap<>();
        for (int i = 0; i<N; i++) {
            levelMap.put(i, new HashSet<>());
        }

        for (int i  = 1; i<N+1; i++) {
            if (!visited[i]) {
                level[i] = 0;
                levelMap.get(0).add(i);
                dfs(i);
            }
        }

//        System.out.println(Arrays.toString(children));
//        System.out.println(Arrays.toString(parents));
//        System.out.println(Arrays.toString(level));
//        System.out.println(levelMap);
        jump = new List[N+1];
        for (int i = 0; i<N+1; i++) {
            jump[i] = new ArrayList<>();
        }
        for (Integer l : levelMap.keySet()) {
            int pow = 0;
            int curr = 1;
            while (curr<=l) {
              curr = curr*2;
              pow++;
            }
            pow--;

            for (Integer node : levelMap.get(l)) {
                curr = 1;
                int parent = parents[node];
                if (parent != 0) {
                    jump[node].add(parent);
                    for (int i = 1; i<=pow; i++) {
                        curr *= 2;
                        jump[node].add(binaryJump(parent, curr-1));
                    }
                }
            }
        }
        System.out.println(Arrays.toString(jump));



    }
    public static int binaryJump (int node, int distance) {
        if (distance == 0) {
            return node;
        }
        int pow = 0;
        int curr = 1;
        while (curr<=distance) {
            curr *= 2;
            pow++;
        }
        pow--;
        curr /= 2;
        return binaryJump(jump[node].get(pow), distance-curr);
    }
    public static int max (int node, int distance) {
        if (distance == 0) {
            return node;
        }
        int pow = 0;
        int curr = 1;
        while (curr<=distance) {
            curr *= 2;
            pow++;
        }
        pow--;
        curr /= 2;
        return max(jump[node].get(pow), distance-curr);
    }
    public static void dfs (int n) {
        if (visited[n]) {
            return;
        }
        visited[n] = true;
        for (Integer adj : edges[n]) {
            if (!visited[adj]) {
                children[n].add(adj);
                parents[adj] = n;
                level[adj] = level[n]+1;
                levelMap.get(level[adj]).add(adj);
                dfs(adj);
            }
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
        boolean connected (int p, int q) {
            return find(p) == find(q);
        }
    }
}
