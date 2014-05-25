#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct expr
{
  int loc;
  char v;
  expr *lhs, *rhs;
  expr(int l, char c) : loc(l), v(c), lhs(0), rhs(0) {}
  expr(int l, expr *e) : loc(l), v(0), lhs(e), rhs(0) {}
  expr(int l, char o, expr *x, expr *y) : loc(l), v(o), lhs(x), rhs(y) {}
  ~expr() { delete lhs; delete rhs; }

  bool eval(const bool *b, string& buf) const
  {
    bool x;
    if (!lhs) {
      // symbol
      x = b[v-'a'];
    } else if (!rhs) {
      // neg
      x = !lhs->eval(b, buf);
    } else {
      // binop
      bool l = lhs->eval(b, buf);
      bool r = rhs->eval(b, buf);
      switch (v) {
        case '&':
          x = l && r;
          break;
        case '|':
          x = l || r;
          break;
        case '-':
          x = !l || r;
          break;
        case '<':
          x = l == r;
          break;
        default:
          cerr << "V = " << v << ", loc = " << loc << endl;
          throw "unknown operator";
      }
    }
    buf[loc] = '0' + x;
    return x;
  }
};

int skip_white(int i, const string& s)
{
  while (i < s.size() && s[i] == ' ') {
    ++i;
  }
  return i;
}

pair<int,expr*> parse_expr(int i, const string& s);

pair<int,expr*> parse_factor(int i, const string& s)
{
  i = skip_white(i, s);
  if (s[i] == '(') {
    pair<int,expr*> e = parse_expr(i+1, s);
    i = skip_white(e.first, s);
    if (s[i] != ')') {
      throw "unmatched paren";
    }
    return make_pair(i+1, e.second);
  } else {
    return make_pair(i+1, new expr(i, s[i]));
  }
}

pair<int,expr*> parse_term(int i, const string& s)
{
  i = skip_white(i, s);
  if (s[i] == '!') {
    int loc = i;
    pair<int,expr*> e = parse_factor(i+1, s);
    return make_pair(e.first, new expr(loc, e.second));
  } else {
    return parse_factor(i, s);
  }
}

inline bool isop(char c) { return c == '&' || c == '|' || c == '-' || c == '<'; }

pair<int,expr*> parse_expr(int i, const string& s)
{
  i = skip_white(i, s);
  pair<int,expr*> l = parse_term(i, s);
  i = skip_white(l.first, s);
  expr *lhs = l.second;
  while (i < s.size() && isop(s[i])) {
    char op = s[i];
    int loc = i;
    i = skip_white(i+1, s);
    if (op == '-' || op == '<') {
      if (s[i] != '-') {
        throw "unk1";
      }
      loc = i;
      i = skip_white(i+1, s);
      if (s[i] != '>') {
        throw "unk2";
      }
      i = skip_white(i+1, s);
    }
    pair<int,expr*> r = parse_term(i, s);
    i = skip_white(r.first, s);
    lhs = new expr(loc, op, lhs, r.second);
  }
  return make_pair(i, lhs);
}

int main()
{
  string line;
  while (getline(cin, line)) {
    vector<char> vars;
    for (string::const_iterator it = line.begin(); it != line.end(); ++it) {
      if ('a' <= *it && *it <= 'z') {
        vars.push_back(*it);
      }
    }
    sort(vars.rbegin(), vars.rend());
    vars.erase(unique(vars.begin(), vars.end()), vars.end());
    const int N = vars.size();

    expr *e = parse_expr(skip_white(0, line), line).second;
    bool b[30];
    string buf(line.size(), ' ');
    cout << line << endl;
    for (unsigned s = 0; s < (1<<N); s++) {
      for (int i = 0; i < N; i++) {
        b[vars[i]-'a'] = (s & (1<<i)) != 0;
      }
      e->eval(b, buf);
      cout << buf << endl;
    }
    cout << endl;
    delete e;
  }
  return 0;
}
