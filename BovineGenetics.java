import java.util.Scanner;

public class BovineGenetics {
    static long mod = 1000000007;
    public static void main(String[] args) {
        //A, G, C, T, ? -> 0, 1, 2, 3, 4
        Scanner io = new Scanner(System.in);
        String[] let = {"A", "G", "C", "T", "?"};
        String[] s = io.next().split("");
        int N = s.length;
        int[] seq = new int[N];
        for (int i = 0; i<N; i++) {
            for (int d = 0; d<let.length; d++) {
                if (s[i].equals(let[d])) {
                    seq[i] = d;
                    break;
                }
            }
        }

        long[][][] dp1 = new long[N][4][4];
        //dp1[i][a]
        //# ways to fill until i such that there is only 1 impartial or full group and the group ends with a and starts with b
        int start = seq[0];
        if (start == 4) {
            for (int a = 0; a<4; a++) {
                dp1[0][a][a] = 1;
            }
        }
        else {
            dp1[0][seq[0]][seq[0]] = 1;
        }
        for (int i = 1; i<N; i++) {
            if (seq[i] == 4) {
                for (int a = 0; a<4; a++) {
                    for (int c = 0; c<4; c++) {
                        for (int b = 0; b<4; b++) {
                            if (c != a) {
                                dp1[i][b][a] += dp1[i-1][b][c];
                            }
                        }
                    }
                }
            }
            else if (seq[i] == seq[i-1]) {
                break;
            }
            else if (seq[i] != seq[i-1]) {
                for (int a = 0; a<4; a++) {
                    for (int b = 0; b<4; b++) {
                        if (a != seq[i]) {
                            dp1[i][b][seq[i]] += dp1[i-1][b][a];
                            dp1[i][b][seq[i]] %= mod;
                        }
                    }
                }
            }
        }


        long[][][][][] dp = new long[N][4][4][4][2];
        //dp[i][a][b][c][d]
        // # ways to fill until i
        // such that previous full group starts with type a
        // current group starts with b
        // current group ends with c
        // d=0 -> current group is impartial, d=1 -> current group is full,
        for (int i = 1; i<N; i++) {
            if (seq[i] == 4) {
                for (int z = 0; z<4; z++) {
                    seq[i] = z;
                    //dp[i][seq[i]][a][seq[i]][1] -> end the group
                    //1 to i-1 ends at a full group -> dp[i][seq[i]][seq[i]][seq[i]][1]
                    for (int a = 0; a<4; a++) {
                        // a = seq[i-1]
                        dp[i][seq[i]][seq[i]][seq[i]][1] += dp[i-1][a][seq[i]][a][1];
                        dp[i][seq[i]][seq[i]][seq[i]][1] %= mod;
                    }
                    //1 to i-1 ends at a partial group -> dp[i][seq[i]][a][seq[i]][1]
                    for (int a = 0; a<4; a++) {
                        for (int b = 0; b<4; b++) {
                            if (b != seq[i]) {
                                dp[i][seq[i]][a][seq[i]][1] += dp[i-1][seq[i]][a][b][0];
                                dp[i][seq[i]][a][seq[i]][1] %= mod;
                            }
                        }
                    }
                    //1 to i-1 is one full group
                    if (seq[i] ==  seq[0] || seq[0] == 4) {
                        for (int a = 0; a<4; a++) {
                            dp[i][seq[i]][seq[i]][seq[i]][1] += dp1[i-1][seq[i]][a];
                            dp[i][seq[i]][seq[i]][seq[i]][1] %= mod;
                        }
                    }

                    //dp[i][a][b][seq[i]][0] -> don't end a group
                    //1 to i-1 ends at a partial group -> dp[i][a][b][seq[i]][0] += dp[i-1][a][b][x][0]
                    for (int a = 0; a<4; a++) {
                        for (int b = 0; b<4; b++) {
                            for (int c = 0; c<4; c++) {
                                if (c != seq[i])
                                    dp[i][a][b][seq[i]][0] += dp[i-1][a][b][c][0];
                                dp[i][a][b][seq[i]][0] %= mod;
                            }
                        }
                    }

                    //1 to i-1 ends at a full group -> dp[i][a][seq[i]][seq[i]][0] += dp[i-1][b][a][b][1]
                    for (int a = 0; a<4; a++) {
                        for (int b = 0; b<4; b++) {
                            dp[i][a][seq[i]][seq[i]][0] += dp[i-1][b][a][b][1];
                            dp[i][a][seq[i]][seq[i]][0] %= mod;
                        }
                    }
                    //1 to i-1 is one full group -> dp[i][seq[0]][seq[i]][seq[i]][0] += dp1[i-1][a]
                    if (seq[0] != 4) {
                        for (int a = 0; a<4; a++) {
                            dp[i][seq[0]][seq[i]][seq[i]][0] += dp1[i-1][seq[0]][a];
                            dp[i][seq[0]][seq[i]][seq[i]][0] %= mod;
                        }
                    }
                    else {
                        for (int b = 0; b<4; b++) {
                            for (int a = 0; a<4; a++) {
                                dp[i][b][seq[i]][seq[i]][0] += dp1[i-1][b][a];
                                dp[i][b][seq[i]][seq[i]][0] %= mod;
                            }
                        }
                    }
                }
                seq[i] = 4;
            }
            else {
                //dp[i][seq[i]][a][seq[i]][1] -> end the group
                //1 to i-1 ends at a full group -> dp[i][seq[i]][seq[i]][seq[i]][1]
                for (int a = 0; a<4; a++) {
                    // a = seq[i-1]
                    dp[i][seq[i]][seq[i]][seq[i]][1] += dp[i-1][a][seq[i]][a][1];
                    dp[i][seq[i]][seq[i]][seq[i]][1] %= mod;
                }
                //1 to i-1 ends at a partial group -> dp[i][seq[i]][a][seq[i]][1]
                for (int a = 0; a<4; a++) {
                    for (int b = 0; b<4; b++) {
                        if (b != seq[i]) {
                            dp[i][seq[i]][a][seq[i]][1] += dp[i-1][seq[i]][a][b][0];
                            dp[i][seq[i]][a][seq[i]][1] %= mod;
                        }
                    }
                }
                //1 to i-1 is one full group
                if (seq[i] ==  seq[0] || seq[0] == 4) {
                    for (int a = 0; a<4; a++) {
                        dp[i][seq[i]][seq[i]][seq[i]][1] += dp1[i-1][seq[i]][a];
                        dp[i][seq[i]][seq[i]][seq[i]][1] %= mod;
                    }
                }

                //dp[i][a][b][seq[i]][0] -> don't end a group
                //1 to i-1 ends at a partial group -> dp[i][a][b][seq[i]][0] += dp[i-1][a][b][x][0]
                for (int a = 0; a<4; a++) {
                    for (int b = 0; b<4; b++) {
                        for (int c = 0; c<4; c++) {
                            if (c != seq[i])
                                dp[i][a][b][seq[i]][0] += dp[i-1][a][b][c][0];
                            dp[i][a][b][seq[i]][0] %= mod;
                        }
                    }
                }

                //1 to i-1 ends at a full group -> dp[i][a][seq[i]][seq[i]][0] += dp[i-1][b][a][b][1]
                for (int a = 0; a<4; a++) {
                    for (int b = 0; b<4; b++) {
                            dp[i][a][seq[i]][seq[i]][0] += dp[i-1][b][a][b][1];
                            dp[i][a][seq[i]][seq[i]][0] %= mod;
                    }
                }
                //1 to i-1 is one full group -> dp[i][seq[0]][seq[i]][seq[i]][0] += dp1[i-1][a]
                if (seq[0] != 4) {
                    for (int a = 0; a<4; a++) {
                        dp[i][seq[0]][seq[i]][seq[i]][0] += dp1[i-1][seq[0]][a];
                        dp[i][seq[0]][seq[i]][seq[i]][0] %= mod;
                    }
                }
                else {
                    for (int b = 0; b<4; b++) {
                        for (int a = 0; a<4; a++) {
                            dp[i][b][seq[i]][seq[i]][0] += dp1[i-1][b][a];
                            dp[i][b][seq[i]][seq[i]][0] %= mod;
                        }
                    }
                }
            }
        }
        long ans = 0;
        for (int a = 0; a<4; a++) {
            for (int b = 0; b<4; b++) {
                for (int c = 0; c<4; c++) {
                    ans+= dp[N-1][a][b][c][1];
                    ans %= mod;
                }
            }
        }
        for (int a = 0; a<4; a++) {
            for (int b = 0; b<4; b++) {
                ans += dp1[N-1][b][a];
                ans %= mod;
            }
        }

        System.out.println(ans);

    }
}
