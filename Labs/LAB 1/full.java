import java.io.*;
import java.util.*;
import java.lang.*;

public class full {
    public static int pow_2(int n) {
        int pow = 1;
        for (int i = 0; i < n; i++) {
            pow *= 2;
        }
        return pow;
    }

    public static void main(String[] args) {
        java.util.Scanner in = new java.util.Scanner(System.in);
        int n;
        n = in.nextInt();
        int[] k = new int[n];
        String[] a = new String[n];

        boolean[] full = new boolean[5];
        for (int i = 0; i < 5; i++) {
            full[i] = false;
        }

        for (int i = 0; i < n; i++) {
            k[i] = in.nextInt();
            a[i] = in.next();
            k[i] = pow_2(k[i]);
        }

        for (int i = 0; i < n; i++) {
            if (a[i].charAt(0) == '1') {
                full[0] = true;
            }

            if (a[i].charAt(k[i] - 1) == '0') {
                full[1] = true;
            }

            for (int j = 0; j <= k[i] / 2; j++) {
                if (a[i].charAt(j) == a[i].charAt(k[i] - j - 1)) {
                    full[2] = true;
                    break;
                }
            }

            int x = k[i] / 2;
            while (x > 0) {
                for (int j = 0; j < k[i] - x; j++) {
                    if ((j / x) % 2 != 0) {
                        j += x;
                    }
                    if (j < k[i] - x && a[i].charAt(j) > a[i].charAt(j + x)) {
                        full[3] = true;
                        break;
                    }
                }
                x /= 2;
            }

            int[][] b = new int[k[i]][k[i]];
            for (int j = 0; j < k[i]; j++) {
                b[j][0] = Integer.valueOf(a[i].charAt(j));
            }
            for (int j = 1; j < k[i]; j++) {
                for (int p = 0; p < k[i] - j; p++) {
                    b[p][j] = (b[p][j - 1] + b[p + 1][j - 1]) % 2;
                }
            }
            for (int j = 1; j < k[i]; j*=2) {
                b[0][j] = 0;
            }
            for (int j = 1; j < k[i]; j++) {
                if (b[0][j] == 1) {
                    full[4] = true;
                    break;
                }
            }

            if (full[0] && full[1] && full[2] && full[3] && full[4]) {
                System.out.println("YES");
                break;
            }
        }
        if (!full[0] || !full[1] || !full[2] || !full[3] || !full[4]) {
            System.out.println("NO");
        }
    }
}