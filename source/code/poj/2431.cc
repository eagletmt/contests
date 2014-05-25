#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  scanf("%d", &N);
  vector<pair<int,int> > fuels(N);
  for (int i = 0; i < N; i++) {
    scanf("%d%d", &fuels[i].first, &fuels[i].second);
  }
  int L, P;
  scanf("%d%d", &L, &P);
  sort(fuels.begin(), fuels.end(), greater<pair<int,int> >());

  int ans = 0;
  vector<pair<int,int> >::const_iterator it = fuels.begin();
  const vector<pair<int,int> >::const_iterator end = fuels.end();
  int rest = L - P;
  priority_queue<int> q;
  while (rest > 0) {
    while (it != end && it->first >= rest) {
      q.push(it->second);
      ++it;
    }
    if (q.empty()) {
      ans = -1;
      break;
    } else {
      rest -= q.top();
      q.pop();
      ++ans;
    }
  }
  printf("%d\n", ans);

  return 0;
}
