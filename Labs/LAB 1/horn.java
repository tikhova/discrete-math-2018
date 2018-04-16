import java.io.*;
import java.util.*;
import java.lang.*;

public class horn {
    public static void main(String[] args) {
        int n, k, res, isolated_index;
        boolean has_isolated = true;
        boolean zero = false;

        java.util.Scanner in = new java.util.Scanner(System.in);
        n = in.nextInt();
        k = in.nextInt();

        int[][] a = new int[k][n];
        int[] b = new int[n];

        for (int i = 0; i < n; i++) {
            b[i] = -1;
        }

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = in.nextInt();
            }
        }

        while (has_isolated) {
            has_isolated = false;
            for (int i = 0; i < k; i++) {
                isolated_index = -1;
                for (int j = 0; j < n; j++) {
                    if (a[i][j] != -1 && b[j] == -1) {
                        if (isolated_index == -1) {
                            isolated_index = j;
                        } else {
                            isolated_index = -2;
                        }
                    } else if(a[i][j] != -1 && b[j] == a[i][j]) {
                        isolated_index = -2;
                    }
                }
                if (isolated_index >= 0) {
                    b[isolated_index] = a[i][isolated_index];
                    has_isolated = true;
                }
            }
        }

        for (int i = 0; i < k; i++) {
            res = 0;
            for (int j = 0; j < n; j++) {
                if (a[i][j] != -1 && (b[j] == -1 || a[i][j] == b[j])) {
                    res = 1;
                    break;
                }
            }
            if (res == 0) {
                zero = true;
                break;
            }
        }
        if(zero) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
    }
}