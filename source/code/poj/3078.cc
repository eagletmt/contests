#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int M, N;
    cin >> M >> N;
    vector<int> before(M), after(M);
    vector<string> v(M);
    for (int i = 0; i < M; i++) {
      cin >> v[i];
      before[i] = i;
      after[i] = -1;
    }
    for (int i = 0; i < N; i++) {
      int from, to;
      cin >> from >> to;
      --from; --to;
      after[to] = from;
      before[from] = -1;
    }
    for (int i = 0, j = 0; i < M; i++) {
      if (after[i] == -1) {
        for (; before[j] == -1; j++);
        after[i] = j;
        before[j] = -1;
      }
    }
    for (int i = 0; i < M; i++) {
      if (i != 0) {
        cout << ' ';
      }
      cout << v[after[i]];
    }
    cout << endl;
  }
  return 0;
}
