import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    int N = cin.nextInt();
    int K = cin.nextInt();
    BigInteger[][] dp = new BigInteger[N+1][K+1];
    for (int k = 0; k <= K; k++) {
      dp[0][k] = BigInteger.ONE;
    }
    for (int n = 1; n <= N; n++) {
      for (int k = 1; k <= K; k++) {
        dp[n][k] = BigInteger.ZERO;
        for (int i = 1; i <= k && n-i >= 0; i++) {
          dp[n][k] = dp[n][k].add(dp[n-i][i]);
        }
      }
    }
    System.out.println(dp[N][K]);
  }
}
