#include <iostream>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

struct mod
{
  int operator()(int n) const
  {
    static const int m = 32768;
    return (n%m+m)%m;
  }
};
static const mod M = mod();

struct matrix
{
  vector<vector<int> > v;
  matrix() {}
  matrix(int r, int c) : v(r, vector<int>(c, 0)) {}

  int row() const { return v.size(); }
  int column() const { return v[0].size(); }
  bool scalar() const { return row() == 1 && column() == 1; }
  matrix transpose() const
  {
    matrix m(column(), row());
    for (int i = 0; i < row(); i++) {
      for (int j = 0; j < column(); j++) {
        m.v[j][i] = v[i][j];
      }
    }
    return m;
  }
  matrix& operator+=(const matrix& m)
  {
    assert(row() == m.row() && column() == m.column());
    for (int i = 0; i < row(); i++) {
      for (int j = 0; j < column(); j++) {
        v[i][j] = M(v[i][j] + m.v[i][j]);
      }
    }
    return *this;
  }
  matrix& operator-=(const matrix& m)
  {
    assert(row() == m.row() && column() == m.column());
    for (int i = 0; i < row(); i++) {
      for (int j = 0; j < column(); j++) {
        v[i][j] = M(v[i][j] - m.v[i][j]);
      }
    }
    return *this;
  }
  matrix& negate()
  {
    for (int i = 0; i < row(); i++) {
      for (int j = 0; j < column(); j++) {
        v[i][j] = M(-v[i][j]);
      }
    }
    return *this;
  }
};

matrix operator*(const matrix& m1, const matrix& m2)
{
  if (m1.scalar()) {
    const int c = m1.v[0][0];
    matrix m(m2);
    for (int i = 0; i < m2.row(); i++) {
      for (int j = 0; j < m2.column(); j++) {
        m.v[i][j] = M(m.v[i][j] * c);
      }
    }
    return m;
  } else if (m2.scalar()) {
    return m2 * m1;
  } else {
    assert(m1.column() == m2.row());
    matrix m(m1.row(), m2.column());
    for (int i = 0; i < m1.row(); i++) {
      for (int j = 0; j < m2.column(); j++) {
        for (int k = 0; k < m1.column(); k++) {
          m.v[i][j] = M(m.v[i][j] + m1.v[i][k]*m2.v[k][j]);
        }
      }
    }
    return m;
  }
}

ostream& operator<<(ostream& os, const matrix& m)
{
  for (int i = 0; i < m.row(); i++) {
    for (int j = 0; j < m.column(); j++) {
      if (j != 0) {
        os << ' ';
      }
      os << m.v[i][j];
    }
    os << endl;
  }
  return os;
}

typedef string::const_iterator Iterator;
map<char, matrix> env;

matrix number(Iterator& it, const Iterator& last)
{
  int n = 0;
  while (it != last && isdigit(*it)) {
    n = 10*n + *it-'0';
    ++it;
  }
  matrix m(1, 1);
  m.v[0][0] = n;
  return m;
}

matrix expr(Iterator& it, const Iterator& last);

vector<matrix> row(Iterator& it, const Iterator& last)
{
  vector<matrix> v(1, expr(it, last));
  while (*it == ' ') {
    ++it;
    v.push_back(expr(it, last));
  }
  return v;
}

matrix rowseq(Iterator& it, const Iterator& last)
{
  vector<matrix> rr = row(it, last);
  vector<vector<matrix> > v(1, rr);
  int r = rr[0].row();
  int c = 0;
  for (vector<matrix>::const_iterator jt = rr.begin(); jt != rr.end(); ++jt) {
    c += jt->column();
  }
  while (*it == ';') {
    ++it;
    rr = row(it, last);
    r += rr[0].row();
    v.push_back(rr);
  }
  matrix m(r, c);
  int i = 0;
  for (vector<vector<matrix> >::const_iterator jt = v.begin(); jt != v.end(); ++jt) {
    int j = 0;
    for (vector<matrix>::const_iterator kt = jt->begin(); kt != jt->end(); ++kt) {
      for (int k = 0; k < kt->row(); k++) {
        for (int l = 0; l < kt->column(); l++) {
          m.v[i+k][j+l] = kt->v[k][l];
        }
      }
      j += kt->column();
    }
    i += jt->front().row();
  }
  return m;
}

matrix primary(Iterator& it, const Iterator& last)
{
  matrix m;
  if (*it == '[') {
    ++it;
    m = rowseq(it, last);
    assert(*it == ']');
    ++it;
  } else if (*it == '(') {
    ++it;
    m = expr(it, last);
    assert(*it == ')');
    ++it;
  } else if (isupper(*it)) {
    const char var = *it;
    ++it;
    assert(env.count(var) != 0);
    m = env[var];
  } else if (isdigit(*it)) {
    m = number(it, last);
  } else {
    throw "primary parse error";
  }

  while (it != last) {
    if (*it == '(') {
      // indexed-primary
      ++it;
      const matrix m1 = expr(it, last);
      assert(m1.row() == 1);
      assert(*it == ',');
      ++it;
      const matrix m2 = expr(it, last);
      assert(m2.row() == 1);
      assert(*it == ')');
      ++it;
      matrix r(m1.column(), m2.column());
      for (int i = 0; i < m1.column(); i++) {
        for (int j = 0; j < m2.column(); j++) {
          r.v[i][j] = m.v[m1.v[0][i]-1][m2.v[0][j]-1];
        }
      }
      m = r;
    } else if (*it == '\'') {
      // transposed-primary
      ++it;
      m = m.transpose();
    } else {
      break;
    }
  }
  return m;
}

matrix factor(Iterator& it, const Iterator& last)
{
  if (*it == '-') {
    ++it;
    return factor(it, last).negate();
  } else {
    return primary(it, last);
  }
}

matrix term(Iterator& it, const Iterator& last)
{
  matrix m = factor(it, last);
  while (it != last && *it == '*') {
    ++it;
    m = m * factor(it, last);
  }
  return m;
}

matrix expr(Iterator& it, const Iterator& last)
{
  matrix m = term(it, last);
  while (it != last && (*it == '+' || *it == '-')) {
    const char op = *it;
    ++it;
    if (op == '+') {
      m += term(it, last);
    } else {
      m -= term(it, last);
    }
  }
  return m;
}

matrix assignment(Iterator& it, const Iterator& last)
{
  assert(isupper(*it));
  const char var = *it;
  ++it;
  assert(*it == '=');
  ++it;
  const matrix m = expr(it, last);
  assert(*it == '.');
  ++it;
  assert(it == last);
  return env[var] = m;
}

matrix eval(const string& s)
{
  Iterator it = s.begin(), last = s.end();
  return assignment(it, last);
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    env.clear();
    cin.ignore();
    for (int i = 0; i < N; i++) {
      string s;
      getline(cin, s);
      const matrix m = eval(s);
      cout << m;
    }
    cout << "-----" << endl;
  }
  return 0;
}
