import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    BigInteger n;
    while (!(n = cin.nextBigInteger()).equals(BigInteger.ZERO)) {
      char[] cs = (n.subtract(BigInteger.ONE)).toString(2).toCharArray();
      System.out.print("{ ");
      BigInteger e = BigInteger.ONE;
      boolean first = true;
      for (int i = 0; i < cs.length; i++) {
        if (cs[cs.length-i-1] == '1') {
          if (!first) {
            System.out.print(", ");
          }
          System.out.print(e);
          first = false;
        }
        e = e.multiply(BigInteger.valueOf(3));
      }
      if (!first) {
        System.out.print(" ");
      }
      System.out.println("}");
    }
  }
}
