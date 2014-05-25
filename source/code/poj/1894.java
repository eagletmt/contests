import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    int B = cin.nextInt();
    BigInteger x = cin.nextBigInteger();
    char[] ans = x.toString(B).toCharArray();
    int len = ans.length;
    for (int i = len-1; i > 0; i--) {
      if (ans[i] <= '0') {
        --ans[i-1];
        ans[i] = (char)(ans[i]+B);
      }
    }
    String r = new String(ans);
    System.out.println(r.replaceFirst("^0", ""));
  }
}
