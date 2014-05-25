#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
static const double EPS = 1e-6;

bool is_zero(double x) { return fabs(x) < EPS; }

bool gaussian_elimination(vector<vector<double> >& a, vector<double>& b)
{
  const int N = a.size();
  const int M = a[0].size();
  const int K = min(N, M);
  vector<int> sigma(N);
  for (int i = 0; i < N; i++) {
    sigma[i] = i;
  }

  for (int i = 0; i < K; i++) {
    int p;
    for (p = i; is_zero(a[i][i]) && p < N; p++);
    if (p == N) {
      continue;
    }
    swap(a[i], a[p]);
    swap(b[i], b[p]);
    swap(sigma[i], sigma[p]);
    if (is_zero(a[i][i])) {
      continue;
    }
    const double r = 1.0/a[i][i];
    for (int k = i; k < M; k++) {
      a[i][k] *= r;
    }
    b[i] *= r;
    for (int j = 0; j < N; j++) {
      if (j == i) {
        continue;
      }
      const double t = a[j][i];
      for (int k = i; k < M; k++) {
        a[j][k] -= t * a[i][k];
      }
      b[j] -= t * b[i];
    }
  }

  const vector<vector<double> > t1(a);
  const vector<double> t2(b);
  for (int i = 0; i < N; i++) {
    a[sigma[i]] = t1[i];
    b[sigma[i]] = t2[i];
  }
  return true;
}
typedef string::const_iterator Iterator;

void skip_white(Iterator& it, const Iterator& last)
{
  while (it != last && *it == ' ') {
    ++it;
  }
}

int number(Iterator& it, const Iterator& last)
{
  int n = 0;
  while (it != last && '0' <= *it && *it <= '9') {
    n = 10*n + (*it-'0');
    ++it;
  }
  return n;
}

pair<vector<double>, double> parse(Iterator& it, const Iterator& last)
{
  skip_white(it, last);
  if (it == last) {
    while (true);
  }
  if (*it == '(') {
    ++it;
    skip_white(it, last);
    vector<pair<vector<double>, double> > rs;
    while (*it != ')') {
      const pair<vector<double>, double> r = parse(it, last);
      rs.push_back(r);
      skip_white(it, last);
    }
    ++it;
    skip_white(it, last);

    const double N = rs.size();
    vector<double> v(26, 0);
    double c = 0;
    for (vector<pair<vector<double>, double> >::const_iterator jt = rs.begin(); jt != rs.end(); ++jt) {
      for (int i = 0; i < 26; i++) {
        v[i] += jt->first[i] / N;
      }
      c += jt->second / N;
    }
    return make_pair(v, c);
  } else if ('0' <= *it && *it <= '9') {
    int c = number(it, last);
    skip_white(it, last);
    return make_pair(vector<double>(26, 0), c);
  } else if (*it == '-') {
    ++it;
    int c = number(it, last);
    skip_white(it, last);
    return make_pair(vector<double>(26, 0), -c);
  } else if ('a' <= *it && *it <= 'z') {
    vector<double> v(26, 0);
    v[*it-'a'] = 1;
    ++it;
    skip_white(it, last);
    return make_pair(v, 0);
  } else {
    while (true);
  }
}

int main()
{
  int N;
  for (int Ti = 1; cin >> N && N != 0; Ti++) {
    cin.ignore();
    vector<vector<double> > m;
    vector<double> x;
    for (int i = 0; i < N; i++) {
      string s;
      getline(cin, s);
      Iterator it = s.begin(), last = s.end();
      int var = *it-'a';
      ++it;
      skip_white(it, last);
      if (*it != '=') {
        while (true);
      }
      ++it;
      skip_white(it, last);
      pair<vector<double>, double> r = parse(it, last);
      r.first[var] -= 1.0;
      r.second = -r.second;
      m.push_back(r.first);
      x.push_back(r.second);
    }

    printf("Game %d\n", Ti);
    if (gaussian_elimination(m, x)) {
      queue<int> q;
      vector<int> undef(N, false);
      for (int i = 0; i < N; i++) {
        if (is_zero(m[i][i])) {
          undef[i] = true;
          q.push(i);
        }
      }
      while (!q.empty()) {
        const int n = q.front();
        q.pop();
        for (int i = 0; i < N; i++) {
          if (!is_zero(m[i][n]) && !undef[i]) {
            undef[i] = true;
            q.push(i);
          }
        }
      }

      for (int i = 0; i < N; i++) {
        printf("Expected score for %c ", i+'a');
        if (undef[i]) {
          puts("undefined");
        } else {
          if (is_zero(x[i])) {
            x[i] = 0;
          }
          printf("= %.3f\n", x[i]);
        }
      }
    } else {
      while (true);
    }
    puts("");
  }
  return 0;
}
