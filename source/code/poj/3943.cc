#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <complex>
using namespace std;
typedef complex<int> P;
namespace std {
  bool operator<(const P& a, const P& b)
  {
    if (a.real() == b.real()) {
      return a.imag() < b.imag();
    } else {
      return a.real() < b.real();
    }
  }
};

inline int cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct segment
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}

  inline bool intersects(const segment& seg) const
  {
    return
      max(a.real(), b.real()) >= min(seg.a.real(), seg.b.real())
      && max(seg.a.real(), seg.b.real()) >= min(a.real(), b.real())
      && max(a.imag(), b.imag()) >= min(seg.a.imag(), seg.b.imag())
      && max(seg.a.imag(), seg.b.imag()) >= min(a.imag(), b.imag())
      && static_cast<long long>(cross(seg.b - seg.a, a - seg.a)) * cross(seg.b - seg.a, b - seg.a) <= 0LL
      && static_cast<long long>(cross(b - a, seg.a - a)) * cross(b - a, seg.b - a) <= 0LL;
  }
};

bool touch(const segment& s1, const segment& s2)
{
  return s1.intersects(s2) && (cross(s1.a-s1.b, s2.a-s1.b) == 0 || cross(s1.a-s1.b, s2.b-s1.b) == 0);
}

struct DisjointSet/*{{{*/
{
  vector<int> parent;

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n) : parent(n, -1) {}

  bool unite(int x, int y)
  {
    const int a = root(x);
    const int b = root(y);
    if (a != b) {
      if (parent[a] < parent[b]) {
        parent[a] += parent[b];
        parent[b] = a;
      } else {
        parent[b] += parent[a];
        parent[a] = b;
      }
      return true;
    } else {
      return false;
    }
  }

  bool find(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

template <class T>
int numbering(map<T,int>& m, const T& x)
{
  typename map<T,int>::const_iterator it = m.find(x);
  if (it == m.end()) {
    const int id = m.size();
    m.insert(make_pair(x, id));
    return id;
  } else {
    return it->second;
  }
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    DisjointSet s(2*N);
    vector<segment> v;
    map<P, int> m;
    for (int i = 0; i < N; i++) {
      int x1, y1, x2, y2;
      scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
      const P p1(x1, y1), p2(x2, y2);
      const int i1 = numbering(m, p1);
      const int i2 = numbering(m, p2);
      s.unite(i1, i2);
      v.push_back(segment(p1, p2));
    }

    vector<vector<segment> > cls;
    vector<int> done(N, false);
    for (int i = 0; i < N; i++) {
      if (!done[i]) {
        done[i] = true;
        vector<segment> c(1, v[i]);
        const int i1 = m[v[i].a];
        for (int j = i+1; j < N; j++) {
          const int i3 = m[v[j].a];
          if (s.find(i1, i3)) {
            c.push_back(v[j]);
            done[j] = true;
          }
        }
        cls.push_back(c);
      }
    }

    for (vector<vector<segment> >::iterator it = cls.begin(); it != cls.end();) {
      if (it->size() == 1) {
        const segment& s1 = it->front();
        for (vector<vector<segment> >::iterator jt = cls.begin(); jt != cls.end(); ++jt) {
          if (jt->size() >= 2) {
            for (vector<segment>::iterator kt = jt->begin(); kt != jt->end(); ++kt) {
              if (touch(s1, *kt) || touch(*kt, s1)) {
                jt->push_back(it->front());
                it = cls.erase(it);
                goto NEXT;
              }
            }
          }
        }
        ++it;
  NEXT:
        ;
      } else {
        ++it;
      }
    }

    int ans[10] = {0};
    for (vector<vector<segment> >::const_iterator it = cls.begin(); it != cls.end(); ++it) {
      const int L = it->size();
      map<P,int> m1;
      int c2 = 0;
      for (vector<segment>::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
        const P& p1 = jt->a;
        const P& p2 = jt->b;
        ++m1[p1];
        ++m1[p2];
        for (vector<segment>::const_iterator kt = it->begin(); kt != it->end(); ++kt) {
          const P& p3 = kt->a;
          const P& p4 = kt->b;
          if (p1 != p3 && p2 != p3 && p1 != p4 && p2 != p4 && touch(*jt, *kt)) {
            ++c2;
          }
        }
      }
      const int c1 = m1.size();

      if (L == 4 && c1 == 4 && c2 == 0) {
        ++ans[0];
      } else if (L == 1) {
        ++ans[1];
      } else if (L == 5 && c1 == 6 && c2 == 0) {
        // 2 or 5
        P p;
        for (map<P,int>::const_iterator jt = m1.begin(); jt != m1.end(); ++jt) {
          if (jt->second == 1) {
            p = jt->first;
          }
        }
        for (vector<segment>::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
          if (jt->a == p || jt->b == p) {
            const P& p1 = p;
            const P& p2 = jt->a == p ? jt->b : jt->a;
            for (vector<segment>::const_iterator kt = it->begin(); kt != it->end(); ++kt) {
              const P& p3 = kt->a;
              const P& p4 = kt->b;
              if (p2 == p3 && p1 != p4) {
                if (cross(p2-p1, p4-p1) < 0) {
                  ++ans[2];
                } else {
                  ++ans[5];
                }
                goto DONE;
              } else if (p2 == p4 && p1 != p3) {
                if (cross(p2-p1, p3-p1) < 0) {
                  ++ans[2];
                } else {
                  ++ans[5];
                }
                goto DONE;
              }
            }
          }
        }
DONE:
        ;
      } else if (L == 4 && c1 == 6 && c2 == 1) {
        ++ans[3];
      } else if (L == 3 && c1 == 5 && c2 == 1) {
        ++ans[4];
      } else if (L == 5 && c1 == 6 && c2 == 1) {
        ++ans[6];
      } else if (L == 3 && c1 == 4 && c2 == 0) {
        ++ans[7];
      } else if (L == 5 && c1 == 6 && c2 == 2) {
        ++ans[8];
      } else if (L == 4 && c1 == 5 && c2 == 1) {
        ++ans[9];
      } else {
        fprintf(stderr, "BUG!!! L=%d, c1=%d, c2=%d\n", L, c1, c2);
        for (vector<segment>::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
          fprintf(stderr, "  segment (%d,%d) - (%d,%d)\n", jt->a.real(), jt->a.imag(), jt->b.real(), jt->b.imag());
        }
      }
    }

    printf("%d", ans[0]);
    for (int i = 1; i < 10; i++) {
      printf(" %d", ans[i]);
    }
    putchar('\n');
  }
  return 0;
}
