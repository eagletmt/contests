#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int N;
  cin >> N;
  vector<pair<int,int> > wires(N);
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    --a;  --b;
    wires[a].first = wires[b].second = i;
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if ((wires[i].first - wires[j].first) * (wires[i].second - wires[j].second) < 0) {
        ++ans;
      }
    }
  }
  cout << ans << endl;

  return 0;
}
