import java.io.*;
import java.util.*;
import java.lang.*;

public class scheme {
    public static void quicksort(int[][] a, int k, int l, int r) {
        int i = l, j = r, t;
        int key = a[(l + r) / 2][k];
        while (i <= j) {
            while (a[i][k] < key) {
                i++;
            }
            while (key < a[j][k]) {
                j--;
            }
            if (i <= j) {
                for (int p = 0; p < a[0].length; p++) {
                    t = a[i][p];
                    a[i][p] = a[j][p];
                    a[j][p] = t;
                }
                i++;
                j--;
            }
        }
        if (l < j) quicksort(a, k, l, j);
        if (i < r) quicksort(a, k, i, r);
    }


    public static void main(String[] args) {
        java.util.Scanner in = new java.util.Scanner(System.in);
        boolean flag1 = true;
        boolean flag2 = true;
        int n;
        long res;
        n = in.nextInt();
        int[] a = new int[n];
        int[][] b = new int[33][n + 1];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
        }
        res = in.nextLong();
        for (int i = 0; i < 33; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = a[j] % 2;
                a[j] /= 2;
            }
            b[i][n] = (int) res % 2;
            res /= 2;
        }
        for (int i = n - 1; i >= 0; i--) {
            quicksort(b, i, 0, 32);
        }
        for (int j = 1; j < 33 && flag2; j++) {
            flag1 = true;
            for (int i = n - 1; i >= 0 && flag2; i--) {
                if (b[j][i] != b[j - 1][i]) {
                    flag1 = false;
                    continue;
                }
            }
            if (b[j][n] != b[j - 1][n] && flag1) {
                flag2 = false;
                System.out.println("Impossible");
                break;
            }
        }
        if (flag2) {
            flag1 = false;
            flag2 = false;
            for (int j = 0; j < 33; j++) {
                if (b[j][n] == 1) {
                    if (flag1) {
                        System.out.print("|");
                    } else {
                        flag1 = true;
                    }
                    flag2 = false;
                    for (int i = 0; i <= n - 1; i++) {
                        if (flag2) {
                            System.out.print("&");
                        } else {
                            flag2 = true;
                        }
                        if (b[j][i] == 0) {
                            System.out.print("~");
                        }
                        System.out.print(String.valueOf(i + 1));
                    }
                }
            }
            if(flag1 == false) {
                flag1 = false;
                flag2 = false;
                for (int j = 0; j < 33; j++) {
                    if (b[j][n] == 0) {
                        if (flag1) {
                            System.out.print("&");
                        } else {
                            flag1 = true;
                        }
                        flag2 = false;
                        for (int i = 0; i <= n - 1; i++) {
                            if (flag2) {
                                System.out.print("|");
                            } else {
                                System.out.print("(");
                                flag2 = true;
                            }
                            if (b[j][i] == 1) {
                                System.out.print("~");
                            }
                            System.out.print(String.valueOf(i + 1));
                        }
                        System.out.print(")");
                    }
                }
            }
        }

    }
}