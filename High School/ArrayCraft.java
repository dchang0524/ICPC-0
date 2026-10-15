import java.util.Scanner;

public class ArrayCraft {
    public static void main (String[] args) {
        Scanner io = new Scanner(System.in);
        int T = io.nextInt();
        for (int t = 0; t<T; t++) {
            int N = io.nextInt();
            int x = io.nextInt()-1;
            int y = io.nextInt()-1;
            int[] a = new int[N];
            for (int i = y; i<=x; i++) {
                a[i] = 1;
            }
            int cnt = 1;
            for (int i = y-1; i>=0; i--) {
                a[i] = (int)Math.pow(-1, cnt);
                cnt++;
            }
            cnt = 1;
            for (int i = x+1; i<N; i++) {
                a[i] = (int)Math.pow(-1, cnt);
                cnt++;
            }

            for (int i = 0; i<N; i++) {
                System.out.print(a[i] + " ");
            }
            System.out.println();
        }
    }
}
