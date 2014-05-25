import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int N = cin.nextInt();
		HashMap<Pair, Long> m = new HashMap<Pair, Long>();
		TreeSet<Integer> rows = new TreeSet<Integer>(), cols = new TreeSet<Integer>();
		for (int i = 0; i < N; i++) {
			int c = cin.nextInt();
			int r = cin.nextInt();
			int v = cin.nextInt();
			cols.add(c);
			rows.add(r);
			Pair k = new Pair(c, r);
			if (m.containsKey(k)) {
				long o = m.get(k);
				m.put(k, o + v);
			} else {
				m.put(k, (long)v);
			}
		}
		Integer[] rs = new Integer[rows.size()], cs = new Integer[cols.size()];
		rows.toArray(rs);
		cols.toArray(cs);

		System.out.print("-1");
		for (int c : cs) {
			System.out.print(" " + c);
		}
		System.out.println("");
		for (int r : rs) {
			StringBuilder sb = new StringBuilder();
			sb.append("" + r);
			for (int c : cs) {
				Pair k = new Pair(c, r);
				if (m.containsKey(k)) {
					sb.append(" " + m.get(k));
				} else {
					sb.append(" 0");
				}
			}
			System.out.println(sb.toString());
		}
	}
}

class Pair {
	public int x, y;
	public Pair(int a, int b) { x = a;  y = b; }

	@Override
	public boolean equals(Object o) {
		Pair p = (Pair)o;
		return x == p.x && y == p.y;
	}

	@Override
	public int hashCode() { return new Long((long)x * y).hashCode(); }
}
