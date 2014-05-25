import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    final BigInteger eof = BigInteger.valueOf(-1);
    while (true) {
      BigInteger n = cin.nextBigInteger();
      if (n.equals(eof)) {
        break;
      }

      if (n.compareTo(BigInteger.TEN) < 0) {
        System.out.println("1" + n);
      } else {
        StringBuilder sb = new StringBuilder();
        for (int i = 9; i >= 2; i--) {
          final BigInteger x = BigInteger.valueOf(i);
          while (!n.equals(BigInteger.ONE)) {
            BigInteger[] qr = n.divideAndRemainder(x);
            if (qr[1].equals(BigInteger.ZERO)) {
              sb.append(i);
              n = qr[0];
            } else {
              break;
            }
          }
        }
        if (n.equals(BigInteger.ONE)) {
          System.out.println(sb.reverse().toString());
        } else {
          System.out.println("There is no such number.");
        }
      }
    }
  }
}
