import java.io.*;
import java.util.*;
import java.lang.*;

public class triangle {

    public static void main(String[] args) {
        java.util.Scanner in = new java.util.Scanner(System.in);
        int n;
        int pow = 1;
        n = in.nextInt();
        for (int i = 0; i < n; i++) {
            pow *= 2;
        }
        String[] b = new String[pow];
        int[][] a = new int[pow][pow];
        for (int i = 0; i < pow; i++) {
            b[i] = in.next();
            a[i][0] = in.nextInt();
        }
        for (int j = 1; j < pow; j++) {
            for (int i = 0; i < pow - j; i++) {
                a[i][j] = (a[i][j - 1] + a[i + 1][j - 1]) % 2;
            }
        }
        for (int i = 0; i < pow; i++) {
            System.out.print(b[i]);
            System.out.println(" " + String.valueOf(a[0][i]));
        }
    }
}