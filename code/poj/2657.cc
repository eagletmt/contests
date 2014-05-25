#include <iostream>
#include <vector>
#include <set>
#include <iterator>
using namespace std;

bool ok(int N, int Z, int K, const set<int>& s)
{
  vector<bool> visited(N, false);
  for (int pos = 0; pos != Z; pos = (pos + K) % N) {
    if (visited[pos] || s.find(pos) != s.end()) {
      return false;
    }
    visited[pos] = true;
  }
  return true;
}

int main(void)
{
  int N, Z, M;
  cin >> N >> Z >> M;
  Z--;
  set<int> s;
  for (int i = 0; i < M; i++) {
    int x;
    cin >> x;
    s.insert(x-1);
  }
  for (int K = 1; K < N; K++) {
    if (ok(N, Z, K, s)) {
      cout << K << endl;
      break;
    }
  }
  return 0;
}
