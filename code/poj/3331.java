import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    int T = cin.nextInt();
    while (T-- > 0) {
      final int year = cin.nextInt();
      final int digit = cin.nextInt();

      final String f = fact(year).toString();
      int ans = 0;
      for (int i = 0; i < f.length(); i++) {
        if (f.charAt(i) == '0'+digit) {
          ++ans;
        }
      }
      System.out.println(ans);
    }
  }

  public static BigInteger fact(int x) {
    BigInteger r = BigInteger.ONE;
    for (int i = 1; i <= x; i++) {
      r = r.multiply(new BigInteger(Integer.toString(i)));
    }
    return r;
  }
}
