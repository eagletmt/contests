import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
  static class Edge {
    int from, to;
    boolean[] visited, looped;
    Edge(int from, int to, boolean[] visited, boolean[] looped) {
      this.from = from;
      this.to = to;
      this.visited = visited;
      this.looped = looped;
    }
  }

  static class NotCactusError extends Exception {
  }

  public static void main(String[] args) {
    new Main().run();
  }

  List<List<Edge>> g;
  BigInteger ans;
  LinkedList<Edge> history;
  List<Boolean> visited;

  void run() {
    Scanner cin = new Scanner(System.in);
    int N = cin.nextInt();
    int M = cin.nextInt();
    g = new ArrayList<List<Edge>>();
    visited = new ArrayList<Boolean>();
    for (int i = 0; i < N; i++) {
      g.add(new ArrayList<Edge>());
      visited.add(false);
    }
    for (int i = 0; i < M; i++) {
      int K = cin.nextInt();
      int prev = cin.nextInt();
      --prev;
      for (int j = 1; j < K; j++) {
        int u = cin.nextInt();
        --u;
        boolean[] b = new boolean[1];
        boolean[] l = new boolean[1];
        b[0] = l[0] = false;
        g.get(prev).add(new Edge(prev, u, b, l));
        g.get(u).add(new Edge(u, prev, b, l));
        prev = u;
      }
    }
    try {
      ans = BigInteger.ONE;
      history = new LinkedList<Edge>();
      dfs(0, 0);
      if (checkConnected()) {
        System.out.println(ans);
      } else {
        System.out.println("0");
      }
    } catch (NotCactusError e) {
      System.out.println("0");
    }
  }

  boolean checkConnected() {
    for (boolean b : visited) {
      if (!b) {
        return false;
      }
    }
    return true;
  }

  void dfs(int n, int steps) throws NotCactusError {
    if (visited.get(n)) {
      Iterator<Edge> it = history.iterator();
      int len = 0;
      while (it.hasNext()) {
        Edge e = it.next();
        if (e.looped[0]) {
          throw new NotCactusError();
        }
        e.looped[0] = true;
        ++len;
        if (e.from == n) {
          break;
        }
      }
      ans = ans.multiply(BigInteger.valueOf(len+1));
    } else {
      visited.set(n, true);
      for (Edge e : g.get(n)) {
        if (!e.visited[0]) {
          e.visited[0] = true;
          history.addFirst(e);
          dfs(e.to, steps+1);
          history.pollFirst();
        }
      }
    }
  }
}
