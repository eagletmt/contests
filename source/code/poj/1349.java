import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    BigInteger[] facts = new BigInteger[51];
    facts[0] = BigInteger.ONE;
    for (int i = 1; i <= 50; i++) {
      facts[i] = facts[i-1].multiply(BigInteger.valueOf(i));
    }

    Scanner cin = new Scanner(System.in);
    String line;
    ArrayList<BigInteger> ans = new ArrayList<BigInteger>();
    while (!(line = cin.next()).equals("-1")) {
      char[] s = line.toCharArray();
      Pair p = readInt(s, 1);
      int n = p.n;
      int i = p.i+2;
      int[] perm = new int[n];
      for (int j = 0; j < n; j++) {
        p = readInt(s, i);
        perm[j] = p.n;
        i = p.i+1;
      }

      BigInteger m = BigInteger.ONE;
      boolean[] used = new boolean[n];
      for (int j = 0; j < n-1; j++) {
        int c = 0;
        for (int k = 0; k < perm[j]-1; k++) {
          if (!used[k]) {
            ++c;
          }
        }
        m = m.add(facts[n-j-1].multiply(BigInteger.valueOf(c)));
        used[perm[j]-1] = true;
      }
      ans.add(m);
    }
    int N = ans.size();
    for (int i = 0; i < N; i++) {
      if (i != 0) {
        System.out.print(",");
      }
      System.out.print(ans.get(i));
    }
    System.out.println();
  }

  static Pair readInt(char[] s, int i) {
    int n = 0;
    while ('0' <= s[i] && s[i] <= '9') {
      n = 10*n + s[i]-'0';
      i++;
    }
    return new Pair(n, i);
  }
}

class Pair {
  public int n, i;
  public Pair(int n, int i) {
    this.n = n;
    this.i = i;
  }
}
