#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct edge
{
  string word, output;
  int to;
};

void do_output(const string& out, char c)
{
  if (out == "\b") {
    cout << c;
  } else {
    cout << out;
  }
}

void operate(const vector<vector<edge> >& g)
{
  int n = 1;  // START
  while (n != 0) {
    int c = cin.get();
    int def_to = -1;
    string def_out;
    for (vector<edge>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      if (it->word == "\b") {
        def_to = it->to;
        def_out = it->output;
      } else if (it->word.find(c) != string::npos) {
        n = it->to;
        do_output(it->output, c);
        goto NEXT;
      }
    }
    if (def_to == -1) {
      throw "incorrect";
    }
    n = def_to;
    do_output(def_out, c);
NEXT:
    ;
  }
}

void normalize(string& s)
{
  for (string::iterator it = s.begin(); it != s.end(); ++it) {
    if (*it == '\\') {
      it = s.erase(it);
      switch (*it) {
        case 'b':
          *it = ' ';  break;
        case 'n':
          *it = '\n'; break;
        case '\\':
          break;
        case '0':
          s = ""; return;
        case 'c':
          s = "\b"; return;
        default:
          throw "unknown sequence";
      }
    }
  }
}

int main()
{
  int N;
  for (int Ti = 1; cin >> N && N != 0; Ti++) {
    map<string,int> d;
    d["END"] = 0; d["START"] = 1;
    vector<vector<edge> >g(2);
    for (int i = 0; i < N; i++) {
      string name;
      int M;
      cin >> name >> M;
      int u;
      if (d.count(name)) {
        u = d[name];
      } else {
        u = d[name] = g.size();
        g.push_back(vector<edge>());
      }
      for (int j = 0; j < M; j++) {
        edge e;
        string label;
        cin >> e.word >> label >> e.output;
        normalize(e.word);
        normalize(e.output);
        if (d.count(label)) {
          e.to = d[label];
        } else {
          e.to = d[label] = g.size();
          g.push_back(vector<edge>());
        }
        g[u].push_back(e);
      }
    }

    int c = cin.get();
    while (c != '\n') {
      c = cin.get();
    }
    cout << "Finite State Machine " << Ti << ":" << endl;
    operate(g);
  }
  return 0;
}
