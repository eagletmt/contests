import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    BigInteger two = new BigInteger("2");
    BigInteger[] a = new BigInteger[1000];
    a[0] = BigInteger.ZERO;
    a[1] = BigInteger.ONE;
    for (int i = 2; i < 1000; i++) {
      a[i] = a[i-2].add(two.pow(i-2));
    }

    Scanner cin = new Scanner(System.in);
    while (cin.hasNext()) {
      System.out.println(a[cin.nextInt()-1]);
    }
  }
}
