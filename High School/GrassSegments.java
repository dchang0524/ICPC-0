import java.util.*;
import java.io.*;

public class GrassSegments {
    public static void main(String[] args) {
        Scanner io = new Scanner(System.in);
        int N = io.nextInt();
        //when computing answer for segment i
        //consider the other segment x
        //if lx<=li<ri<=rx answer++
        //if lx<=li, then answer++ if rx>=li+k
        //if rx>=ri, then answer++ if li<=ri-k
        //if li<=lx<rx<=ri -> consider this case separately for all segments
        //compute this part using a sliding window type of thing

        //consider each segment as node, directed edge from a to b if b is completely contained in a
        //if two segments are same, give increment weight of the node and consider keep all the k values in an arraylist or smth
        //use smth like binary jumping on each node to store the maximum length 2^x levels below the current node for 0<x<logN
    }
}
