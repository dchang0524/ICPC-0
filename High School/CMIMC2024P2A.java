import java.util.*;
public class CMIMC2024P2A {
    public static void main(String[] args) {
        //1 = O_1, 3=O_2, ... (2n-1) = O_n
        //2 = e_1, 4=e_2, ... (2n)=e_n
    }
    public ArrayList<Integer> encode (TreeSet<Integer> nums) {
        ArrayList<Integer> permutation = new ArrayList<>();
        if (numEvens(nums) == 5) {
            int x = nums.last();
            nums.remove(x);
            permutation = order(nums, x/2);
        }
        if (numEvens(nums) == 4) {
            
        }


        return permutation;
    }

    public ArrayList<Integer> order(TreeSet<Integer> nums, int i) {
        //1 2 3 4 <- 1
        //1 2 4 3 <- 2
        //4 3 2 1 <- 24
        ArrayList<Integer> permutation = new ArrayList<>();
        i--;
        while (permutation.size()<4) {

        }
        return permutation;
    }

    public int numEvens(TreeSet<Integer> nums) {
        int cnt = 0;
        for (Integer i : nums) {
            if (i % 2 == 0) {
                cnt++;
            }
        }
        return cnt;
    }

}
