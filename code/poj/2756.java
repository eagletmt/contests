import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) throws IOException {
    Scanner cin = new Scanner(System.in);
    int t = cin.nextInt();
    while (t-- > 0) {
      BigDecimal a = cin.nextBigDecimal();
      BigDecimal b = cin.nextBigDecimal();
      System.out.println(a.add(b));
    }
  }
}

