#include <iostream>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

long long gcd(long long a, long long b)
{
  if (a < b) {
    swap(a, b);
  }
  long long r;
  while ((r = a % b) != 0LL) {
    a = b;
    b = r;
  }
  return b;
}

struct ratio
{
  long long n, d;
  ratio() : n(0), d(1) {}
  ratio(long long a, long long b) : n(a), d(b)
  {
    normalize();
  }

  void normalize()
  {
    if (n == 0) {
      d = 1;
    } else {
      const long long g = gcd(n, d);
      n /= g;
      d /= g;
      if (d < 0) {
        n = -n;
        d = -d;
      }
    }
  }

  ratio inverse() const { return ratio(d, n); }

  ratio& operator-=(const ratio& r)
  {
    const long long dd = d * r.d;
    const long long nn = n*r.d - r.n*d;
    d = dd;
    n = nn;
    normalize();
    return *this;
  }
  ratio operator*(const ratio& r) const { return ratio(n * r.n, d * r.d); }
};
ostream& operator<<(ostream& os, const ratio& r)
{
  if (r.d == 1) {
    return os << r.n;
  } else {
    return os << r.n << '/' << r.d;
  }
}

typedef string::const_iterator Iterator;

typedef map<string,int> molecule_type;
molecule_type molecule(Iterator& it, const Iterator& last);

void append(molecule_type& m, const molecule_type& mm)
{
  for (molecule_type::const_iterator it = mm.begin(); it != mm.end(); ++it) {
    m[it->first] += it->second;
  }
}

int number(Iterator& it, const Iterator& last)
{
  if (it == last || !isdigit(*it)) {
    return 1;
  }
  int n = 0;
  while (it != last && isdigit(*it)) {
    n = 10*n + *it-'0';
    ++it;
  }
  return n;
}

molecule_type group(Iterator& it, const Iterator& last)
{
  molecule_type m;
  while (it != last && (*it == '(' || isupper(*it))) {
    molecule_type mm;
    if (*it == '(') {
      ++it;
      mm = molecule(it, last);
      assert(*it == ')');
      ++it;
    } else {
      const Iterator jt = it;
      ++it;
      while (it != last && islower(*it)) {
        ++it;
      }
      mm.insert(make_pair(string(jt, it), 1));
    }
    const int n = number(it, last);
    for (molecule_type::iterator jt = mm.begin(); jt != mm.end(); ++jt) {
      jt->second *= n;
    }
    append(m, mm);
  }
  return m;
}

molecule_type molecule(Iterator& it, const Iterator& last)
{
  molecule_type m = group(it, last);
  while (it != last && (*it == '(' || isupper(*it))) {
    const molecule_type mm = group(it, last);
    append(m, mm);
  }
  return m;
}

vector<molecule_type> molecule_sequence(Iterator& it, const Iterator& last)
{
  vector<molecule_type> v(1, molecule(it, last));
  while (it != last && *it == '+') {
    ++it;
    v.push_back(molecule(it, last));
  }
  return v;
}

vector<long long> gaussian_elimination(vector<vector<ratio> > a)
{
  const int N = a.size();
  const int M = a[0].size();
  const int K = min(N, M);
  for (int i = 0; i < K; i++) {
    for (int j = i+1; a[i][i].n == 0LL && j < N; j++) {
      swap(a[i], a[j]);
    }
    if (a[i][i].n == 0LL) {
      continue;
    }
    const ratio r = a[i][i].inverse();
    for (int k = i; k < M; k++) {
      a[i][k] = a[i][k] * r;
    }
    for (int j = 0; j < N; j++) {
      if (j == i) {
        continue;
      }
      const ratio t = a[j][i];
      for (int k = i; k < M; k++) {
        a[j][k] -= t * a[i][k];
      }
    }
  }

  vector<long long> ans;
  long long lcm = 1;
  for (int i = 0; i < M-1; i++) {
    const long long g = gcd(lcm, a[i][M-1].d);
    lcm = (lcm * a[i][M-1].d)/g;
  }
  for (int i = 0; i < M-1; i++) {
    ans.push_back(lcm/a[i][M-1].d * (-a[i][M-1].n));
  }
  ans.push_back(lcm);
  return ans;
}

vector<long long> solve(const string& str)
{
  Iterator it = str.begin(), last = str.end();
  const vector<molecule_type> lhs = molecule_sequence(it, last);
  assert(*it == '-');
  ++it;
  assert(*it == '>');
  ++it;
  const vector<molecule_type> rhs = molecule_sequence(it, last);
  assert(*it == '.');
  ++it;
  assert(it == last);

  map<string,int> dict;
  for (vector<molecule_type>::const_iterator jt = lhs.begin(); jt != lhs.end(); ++jt) {
    for (molecule_type::const_iterator kt = jt->begin(); kt != jt->end(); ++kt) {
      if (!dict.count(kt->first)) {
        const int id = dict.size();
        dict.insert(make_pair(kt->first, id));
      }
    }
  }
  const int N1 = lhs.size(), N2 = rhs.size();
  const int M = dict.size();
  vector<vector<ratio> > a(M, vector<ratio>(N1+N2));
  for (int i = 0; i < N1; i++) {
    for (molecule_type::const_iterator kt = lhs[i].begin(); kt != lhs[i].end(); ++kt) {
      a[dict[kt->first]][i] = ratio(kt->second, 1);
    }
  }
  for (int i = 0; i < N2; i++) {
    for (molecule_type::const_iterator kt = rhs[i].begin(); kt != rhs[i].end(); ++kt) {
      a[dict[kt->first]][i+N1] = ratio(-kt->second, 1);
    }
  }

  return gaussian_elimination(a);
}

int main()
{
  string s;
  while (getline(cin, s) && s != ".") {
    const vector<long long> r = solve(s);
    for (vector<long long>::const_iterator it = r.begin(); it != r.end(); ++it) {
      if (it != r.begin()) {
        cout << ' ';
      }
      cout << *it;
    }
    cout << endl;
  }
  return 0;
}
