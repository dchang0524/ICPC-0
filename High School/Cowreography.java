import java.util.*;
import java.io.*;

public class Cowreography {
    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        String s1 = io.next();
        String[] S1 = s1.split("");
        int[] seq1 = new int[N];
        for (int i = 0; i<N; i++) {
            seq1[i] = Integer.parseInt(S1[i]);
        }
        String s2 = io.next();
        String[] S2 = s2.split("");
        int[] seq2 = new int[N];
        for (int i = 0; i<N; i++) {
            seq2[i] = Integer.parseInt(S2[i]);
        }

        TreeSet<Integer> ones = new TreeSet<>();
        TreeSet<Integer> zeros = new TreeSet<>();
        for (int i = 0; i<N; i++) {
            if (seq1[i] == 0) {
                zeros.add(i);
            }
            else {
                ones.add(i);
            }
        }


    }
}
