#include <iostream>
#include <vector>
using namespace std;
static const int M = 2011;

int powmod(int a, int n)
{
  if (n == 0) {
    return 1;
  } else if (n & 1) {
    return (a * powmod(a, n-1))%M;
  } else {
    const int e = powmod(a, n>>1);
    return (e * e)%M;
  }
}

struct parser
{
  int i;
  vector<string> src;
  parser() : i(0), src() {}

  int width() const { return src[0].size(); }
  int height() const { return src.size(); }
  int find_base(int top, int bot)
  {
    for (; i < width(); i++) {
      for (int k = top; k < bot; k++) {
        if (src[k][i] != '.') {
          return k;
        }
      }
    }
    throw "find_base";
  }

  int parse(int top, int bot)
  {
    return expr(find_base(top, bot), top, bot);
  }

  int expr(int base, int top, int bot)
  {
    const string& line = src[base];
    int r = term(base, top, bot);
    while (i+2 < width() && line[i] == '.' && (line[i+1] == '+' || line[i+1] == '-') && line[i+2] == '.') {
      const char op = line[i+1];
      i += 3;
      const int t = term(base, top, bot);
      if (op == '+') {
        r = (r + t)%M;
      } else {
        r = ((r - t)%M + M)%M;
      }
    }
    return r;
  }

  int term(int base, int top, int bot)
  {
    const string& line = src[base];
    int r = factor(base, top, bot);
    while (i+2 < width() && line[i] == '.' && line[i+1] == '*' && line[i+2] == '.') {
      i += 3;
      const int t = factor(base, top, bot);
      r = (r * t)%M;
    }
    return r;
  }

  int factor(int base, int top, int bot)
  {
    const string& line = src[base];
    if (line[i] == '-') {
      if (line[i+1] == '.') {
        i += 2;
        const int r = factor(base, top, bot);
        return (-r + M)%M;
      } else {
        const int save = i;
        const int n = parse(top, base);
        i = save;
        const int d = parse(base+1, bot);
        i = save;
        while (i < width() && line[i] == '-') {
          ++i;
        }
        return (n * powmod(d, M-2))%M;
      }
    } else {
      return powexpr(base, top, bot);
    }
  }

  int powexpr(int base, int top, int bot)
  {
    int r = primary(base, top, bot);
    if (base-1 >= top && i < width() && isdigit(src[base-1][i])) {
      const int n = src[base-1][i]-'0';
      i++;
      return powmod(r, n);
    } else {
      return r;
    }
  }

  int primary(int base, int top, int bot)
  {
    const string& line = src[base];
    if (line[i] == '(' && line[i+1] == '.') {
      i += 2;
      const int r = expr(base, top, bot);
      i += 2;
      return r;
    } else {
      const int n = line[i]-'0';
      i++;
      return n;
    }
  }
};

int main()
{
  int N;
  while (cin >> N && N != 0) {
    parser p;
    p.src.resize(N);
    for (int i = 0; i < N; i++) {
      cin >> p.src[i];
    }
    cout << p.parse(0, N) << endl;
  }
  return 0;
}
