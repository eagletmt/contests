import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);

    for (int Ti = 1;; Ti++) {
      BigInteger p = cin.nextBigInteger();
      BigInteger q = cin.nextBigInteger();
      if (q.equals(BigInteger.ZERO)) {
        break;
      }
      System.out.printf("Case %d:\n", Ti);
      System.out.printf("%s / %s\n", p.toString(), q.toString());

      ArrayList<BigInteger> a = new ArrayList<BigInteger>();
      int width = 0;
      while (!p.mod(q).equals(BigInteger.ZERO)) {
        BigInteger[] qr = p.divideAndRemainder(q);
        a.add(qr[0]);
        width += qr[0].toString().length() + 3;
        p = q;
        q = qr[1];
      }
      p = p.divide(q).subtract(BigInteger.ONE);
      width += p.toString().length() + 4;
      a.add(p);

      int indent = 0;
      for (BigInteger n : a) {
        String s = n.toString();
        int frac = width - indent - s.length() - 3;
        for (int i = 0; i < indent + s.length() + 3 + (frac-1)/2; i++) {
          System.out.print(".");
        }
        System.out.print("1");
        for (int i = 0; i < frac/2; i++) {
          System.out.print(".");
        }
        System.out.println("");
        for (int i = 0; i < indent; i++) {
          System.out.print(".");
        }
        System.out.print(s);
        System.out.print(".+.");
        for (int i = 0; i < frac; i++) {
          System.out.print("-");
        }
        System.out.println("");
        indent += s.length() + 3;
      }
      for (int i = 0; i < width-1; i++) {
        System.out.print(".");
      }
      System.out.println("1");
    }
  }
}
