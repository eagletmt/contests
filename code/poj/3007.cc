#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

struct fixed_string
{
  size_t len;
  char s[80];
  char *begin() { return s; }
  char *end() { return s + len; }
  bool operator<(const fixed_string& that) const
  {
    return strcmp(s, that.s) < 0;
  }
};

int main()
{
  int N;
  scanf("%d", &N);
  while (N-- > 0) {
    fixed_string w;
    scanf("%s", w.s);
    w.len = strlen(w.s);
    set<fixed_string> h;
    for (size_t i = 1; i < w.len; i++) {
      h.insert(w);
      reverse(w.begin(), w.begin()+i);
      h.insert(w);
      reverse(w.begin()+i, w.end());
      h.insert(w);
      reverse(w.begin(), w.begin()+i);
      h.insert(w);
      reverse(w.begin(), w.end());
      h.insert(w);
      reverse(w.begin()+w.len-i, w.end());
      h.insert(w);
      reverse(w.begin(), w.begin()+w.len-i);
      h.insert(w);
      reverse(w.begin()+w.len-i, w.end());
      h.insert(w);
      reverse(w.begin(), w.end());
    }
    printf("%lu\n", h.size());
  }
  return 0;
}
