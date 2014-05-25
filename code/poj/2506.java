import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    BigInteger[] dp = new BigInteger[251];
    dp[0] = dp[1] = BigInteger.ONE;
    for (int i = 2; i <= 250; i++) {
      dp[i] = dp[i-1].add(dp[i-2].multiply(BigInteger.valueOf(2)));
    }

    Scanner cin = new Scanner(System.in);
    while (cin.hasNextInt()) {
      int n = cin.nextInt();
      System.out.println(dp[n]);
    }
  }
}
