import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    for (int N; (N = cin.nextInt()) != 0;) {
      int[] ans = solve(N);
      System.out.printf("%d! --\n", N);
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
          System.out.printf("   (%d) %4d ", 5*i+j, ans[5*i+j]);
        }
        System.out.println("");
      }
    }
  }

  static int[] solve(int N) {
    int[] ans = new int[10];
    BigInteger n = BigInteger.ONE;
    for (int i = 2; i <= N; i++) {
      n = n.multiply(BigInteger.valueOf(i));
    }
    char[] s = n.toString().toCharArray();
    for (char c : s) {
      ++ans[c - '0'];
    }
    return ans;
  }
}
