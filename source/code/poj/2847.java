import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    int T = cin.nextInt();
    while (T-- > 0) {
      String s = cin.next();
      char[] cs = s.toCharArray();
      BigInteger ans = BigInteger.ZERO;
      BigInteger e = BigInteger.ONE;
      for (int i = 0; i < cs.length; i++) {
        for (int j = 0; j < 10; j++) {
          BigInteger t = BigInteger.valueOf(j).multiply(e).add(ans);
          BigInteger n = t.pow(3);
          String sn = n.toString();
          if (i < sn.length() && sn.charAt(sn.length()-1-i) == cs[cs.length-1-i]) {
            ans = t;
          }
        }
        e = e.multiply(BigInteger.TEN);
      }
      System.out.println(ans);
    }
  }
}
