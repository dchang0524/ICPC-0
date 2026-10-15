import java.util.Arrays;
import java.util.Scanner;

public class GridPuzzle {
    public static void main (String[] args) {
        Scanner io = new Scanner(System.in);
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int N = io.nextInt();
            int[] black = new int[N];
            for (int i = 0; i<N; i++) {
                black[i] = io.nextInt();
            }
            int[] move = new int[N];
            Arrays.fill(move, -1);

            int cnt = 0;
            for (int i = 0; i<N; i++) {
                cnt++;
                if (move[i] == -1) {
                    if (black[i] > 2) {
                        continue;
                    }
                    else {
                        if (i+1<N) {
                            move[i+1] = 0;
                        }
                    }
                }
                else {
                    if (move[i] == 0) {

                    }
                }
            }
        }
    }
}
