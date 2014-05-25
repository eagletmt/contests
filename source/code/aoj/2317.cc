#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct event
{
  enum event_type { BEGIN, END, CUTOFF };
  event_type evt;
  int pos;
  int idx;
  event(event_type e, int p, int i = -1) : evt(e), pos(p), idx(i) {}
  bool operator<(const event& that) const { return pos < that.pos; }
};

int main()
{
  int N, M;
  cin >> N >> M;
  vector<pair<int,int> > intervals(N);
  for (int i = 0; i < N; i++) {
    cin >> intervals[i].first >> intervals[i].second;
  }
  vector<int> cutoffs(M);
  for (int i = 0; i < M; i++) {
    cin >> cutoffs[i];
  }

  vector<event> v;
  for (vector<pair<int,int> >::const_iterator it = intervals.begin(); it != intervals.end(); ++it) {
    v.push_back(event(event::BEGIN, min(it->first, it->second), it - intervals.begin()));
    v.push_back(event(event::END, max(it->first, it->second), it - intervals.begin()));
  }
  for (vector<int>::const_iterator it = cutoffs.begin(); it != cutoffs.end(); ++it) {
    v.push_back(event(event::CUTOFF, *it));
  }
  sort(v.begin(), v.end());
  vector<int> cnt(N, 0);
  int acc = 0;
  for (vector<event>::const_iterator it = v.begin(); it != v.end(); ++it) {
    switch (it->evt) {
      case event::BEGIN:
        cnt[it->idx] = acc;
        break;
      case event::END:
        cnt[it->idx] = acc - cnt[it->idx];
        break;
      case event::CUTOFF:
        ++acc;
        break;
    }
  }

  int on = 0, off = 0;
  int prev = 0;
  long long ans = 0LL;
  for (vector<event>::const_iterator it = v.begin(); it != v.end(); ++it) {
    ans += static_cast<long long>(it->pos - prev) * on;
    switch (it->evt) {
      case event::BEGIN:
        if (intervals[it->idx].first == it->pos || cnt[it->idx] % 2 == 0) {
          ++on;
        } else {
          ++off;
        }
        break;
      case event::END:
        if (intervals[it->idx].first == it->pos || cnt[it->idx] % 2 == 0) {
          --on;
        } else {
          --off;
        }
        break;
      case event::CUTOFF:
        swap(on, off);
        break;
    }
    prev = it->pos;
  }
  cout << ans << endl;
  return 0;
}
