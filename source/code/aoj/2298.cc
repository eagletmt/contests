#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

struct event {
  int pos;
  enum event_type { CARROT, DOWN, GOAL };
  event_type ev;
  event(int p, event_type e) : pos(p), ev(e) {}
  bool operator<(const event& that) const { return pos > that.pos; }
};

int main()
{
  int N, K, T, U, V, L;
  cin >> N >> K >> T >> U >> V >> L;
  priority_queue<event> q;
  q.push(event(L, event::GOAL));
  for (int i = 0; i < N; i++) {
    int d;
    cin >> d;
    q.push(event(d, event::CARROT));
  }

  bool running = false;
  int running_dist = 0;
  int prev = 0;
  int have = 0;
  int ignore = 0;
  bool goal = false;
  while (!q.empty() && !goal) {
    const event::event_type ev = q.top().ev;
    const int pos = q.top().pos;
    q.pop();
    if (running) {
      running_dist += pos - prev;
    }
    switch (ev) {
      case event::CARROT:
        if (running) {
          if (have == K) {
            ++ignore;
            q.push(event(pos+V*T, event::DOWN));
          } else {
            ++have;
          }
        } else {
          q.push(event(pos+V*T, event::DOWN));
          running = true;
        }
        break;
      case event::DOWN:
        if (ignore > 0) {
          --ignore;
        } else if (have > 0) {
          --have;
          q.push(event(pos+V*T, event::DOWN));
        } else {
          running = false;
        }
        break;
      case event::GOAL:
        goal = true;
        break;
    }
    prev = pos;
  }

  printf("%.6f\n", running_dist/double(V) + (L-running_dist)/double(U));
  return 0;
}
