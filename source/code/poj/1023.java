import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    int T = cin.nextInt();
    BigInteger two = BigInteger.valueOf(2);
    while (T-- > 0) {
      int K = cin.nextInt();
      char[] pn = cin.next().toCharArray();
      BigInteger N = cin.nextBigInteger();
      BigInteger lo = BigInteger.ZERO, hi = BigInteger.ZERO;
      for (int i = 0; i < K; i++) {
        lo = lo.multiply(two);
        hi = hi.multiply(two);
        if (pn[i] == 'n') {
          lo = lo.subtract(BigInteger.ONE);
        } else {
          hi = hi.add(BigInteger.ONE);
        }
      }
      if (N.compareTo(lo) < 0 || hi.compareTo(N) < 0) {
        System.out.println("Impossible");
      } else {
        char[] ans = new char[K];
        for (int i = 0; i < K; i++) {
          if (N.testBit(i)) {
            ans[K-i-1] = '1';
            if (pn[K-i-1] == 'n') {
              N = N.add(BigInteger.ONE.shiftLeft(i+1));
            }
          } else {
            ans[K-i-1] = '0';
          }
        }
        System.out.println(ans);
      }
    }
  }
}
