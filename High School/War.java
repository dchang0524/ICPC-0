import java.util.Scanner;
import java.util.TreeMap;

public class War {
    public static void main (String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        UnionFind graph = new UnionFind(N);
        int t = io.nextInt();
        int a = io.nextInt();
        int b = io.nextInt();
        while (!(t==0 && a == 0 && b == 0)) {
            if (t == 1) {
                int r = graph.setFriends(a, b);
                if (r == -1) {
                    System.out.println(-1);
                }
            }
            if (t == 2) {
                int r = graph.setEnemies(a, b);
                if (r == -1) {
                    System.out.println(-1);
                }
            }
            if (t == 3) {
                System.out.println(graph.areFriends(a, b));
            }
            if (t == 4) {
                System.out.println(graph.areEnemies(a, b));
            }
            t = io.nextInt();
            a= io.nextInt();
            b= io.nextInt();
        }
    }
    public static class UnionFind {
        int[] nodes;
        int[] sizes;
        int[] enemies;
        int components;
        UnionFind(int n) {
            nodes = new int[n];
            sizes = new int[n];
            enemies = new int[n];
            components = n;
            for (int i = 0; i < n; i++) {
                nodes[i] = i;
                sizes[i] = 1;
                enemies[i] = -1;
            }
        }
        void union (int p, int q) {
            if (p == -1 || q == -1) {
                return;
            }
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
            if (index == -1) {
                return -1;
            }
            while (nodes[index] != index) {
                nodes[index] = nodes[nodes[index]];
                index = nodes[index];
            }
            return index;
        }
        int setFriends (int a, int b) {
            int i = find(a);
            int j = find(b);
            if (i == j) {
                return 1;
            }
            if (enemies[i] == j) {
                return -1;
            }
            int enemyI = find(enemies[i]);
            int enemyJ = find(enemies[j]);
            union(i, j);
            union(enemyI, enemyJ);
            enemies[i] = Math.max(find(enemyI), find(enemyJ));
            if (Math.max(find(enemyI), find(enemyJ)) != -1) {
                enemies[Math.max(find(enemyI), find(enemyJ))] = find(i);
            }
            return 1;
        }
        int setEnemies (int a, int b) {
            int i = find(a);
            int j = find(b);
            int enemyI = find(enemies[i]);
            int enemyJ = find(enemies[j]);
            if (i == j) {
                return -1;
            }
            if (enemyI == j) {
                return 1;
            }

            union(i, enemyJ);
            union(j, enemyI);
            enemies[find(i)] = find(j);
            enemies[find(j)] = find(i);
            return 1;
        }
        int areFriends (int a, int b) {
            int i = find(a);
            int j = find(b);
            if (i == j) {
                return 1;
            }
            return 0;
        }
        int areEnemies (int a, int b) {
            int i = find(a);
            int j = find(b);
            if (enemies[i] == j) {
                return 1;
            }
            return 0;
        }
    }


}
