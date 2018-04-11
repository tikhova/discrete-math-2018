import java.util.regex.Pattern;
import java.lang.String;

public class Main {
    public static void main(String[] args) {
        java.util.Scanner in = new java.util.Scanner(System.in);
        
        int x = in.nextInt();
        int y = in.nextInt();
        int z = in.nextInt();

        String stringX = Integer.toBinaryString(x);
        String stringY = Integer.toBinaryString(y);
        String stringZ = Integer.toBinaryString(z);

        int xLength = stringX.length();
        int yLength = stringY.length();
        int zLength = stringZ.length();

        int maxLength = Math.max(Math.max(xLength, yLength), zLength);

        for (int i = 0; i < maxLength - xLength; i++)
            stringX = "0" + stringX;
        for (int i = 0; i < maxLength - yLength; i++)
            stringY = "0" + stringY;
        for (int i = 0; i < maxLength - zLength; i++)
            stringZ = "0" + stringZ;

        String word = "";
        for (int i = 0; i < maxLength; i++) {
            word = word + Character.toString(stringX.charAt(i)) + Character.toString(stringY.charAt(i)) +
                    Character.toString(stringZ.charAt(i));
        }
        if (Pattern.matches("((000)|(((01)|(10))1)|(001)(((01|10)0)|(111))*(110))*", word) && x + y == z ||
                !Pattern.matches("((000)|(((01)|(10))1)|(001)(((01|10)0)|(111))*(110))*", word) && x + y != z) {
            System.out.println("You're the best <3");
        } else {
            System.out.println("Fuck this shit...");
            System.out.println(stringX);
            System.out.println(stringY);
            System.out.println(stringZ);
            System.out.println(word);
        }
    }
}