#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
static const int MAXN = 4000;
static const int MAXLEN = 200;

struct build_less
{
  const char *s;
  build_less(const char *a) : s(a) {}
  bool operator()(int i, int j) const { return strcmp(s+i, s+j) < 0; }
};

struct search_less
{
  const char *s;
  int idx;
  search_less(const char *t, int i) : s(t), idx(i) {}
  bool operator()(int i, char c) const { return s[i+idx] < c; }
  bool operator()(char c, int i) const { return c < s[i+idx]; }
};

struct SuffixArray
{
  char s[MAXLEN+1];
  int a[MAXLEN+1];;
  int len;

  void build()
  {
    for (int i = 0; i < len; i++) {
      a[i] = i;
    }
    sort(a, a+len, build_less(s));
  }

  int search(const char *t) const
  {
    typedef const int *Iterator;
    Iterator first = a, last = a+len;
    int i;
    for (i = 0; t[i] != '\0'; i++) {
      const pair<Iterator, Iterator> r = equal_range(first, last, t[i], search_less(s, i));
      first = r.first;
      last = r.second;
      if (first == last) {
        return i;
      }
    }
    return i;
  }
};


int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    static SuffixArray sa[MAXN];
    for (int i = 0; i < N; i++) {
      scanf("%s", sa[i].s);
      sa[i].len = strlen(sa[i].s);
      sa[i].build();
    }
    char *t = sa[0].s;
    const int tlen = sa[0].len;

    char *ans = 0;
    int anslen = -1;
    for (int i = 0; t[i] != '\0'; i++) {
      char *u = t+i;
      int n = tlen-i;
      for (int j = 1; j < N; j++) {
        n = min(n, sa[j].search(u));
      }
      if (n > anslen
          || (n == anslen && strcmp(u, ans) < 0)) {
        ans = u;
        anslen = n;
      }
    }
    if (anslen == 0) {
      puts("IDENTITY LOST");
    } else {
      ans[anslen] = 0;
      puts(ans);
    }
  }
  return 0;
}
