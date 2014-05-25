import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    while (cin.hasNext()) {
      String s = cin.next();
      char[] cs = s.toCharArray();
      BigDecimal n = BigDecimal.valueOf(0), eight = BigDecimal.valueOf(8);
      BigDecimal e = BigDecimal.valueOf(1);
      for (int i = 2; i < cs.length; i++) {
        n = n.multiply(eight).add(BigDecimal.valueOf(cs[i] - '0'));
        e = e.multiply(eight);
      }
      n = n.divide(e);
      System.out.printf("%s [8] = %s [10]\n", s, n);
    }
  }
}
