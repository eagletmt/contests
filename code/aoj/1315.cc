#include <iostream>
#include <vector>
#include <map>
using namespace std;

int parse(const string& t)
{
  return ((t[0]-'0')*10 + t[1]-'0')*60 + ((t[3]-'0')*10 + t[4]-'0');
}

int inter(int gb, int ge, int vb, int ve)
{
  if (ge < vb || ve < gb) {
    return 0;
  } else {
    return min(ge, ve) - max(gb, vb);
  }
}

void countup(map<string, int>& total, const map<string, vector<int> >& m)
{
  if (!m.count("000")) {
    return;
  }
  const vector<int>& god = m.find("000")->second;
  const int N = god.size();
  if (N % 2 != 0) {
    throw "N is not even";
  }
  for (map<string, vector<int> >::const_iterator it = m.begin(); it != m.end(); ++it) {
    if (it->first == "000") {
      continue;
    }
    const string& id = it->first;
    const vector<int>& v = it->second;
    const int M = v.size();
    if (M % 2 != 0) {
      throw "M is not even";
    }
    for (int i = 0; i < N; i += 2) {
      for (int j = 0; j < M; j += 2) {
        total[id] += inter(god[i], god[i+1], v[j], v[j+1]);
      }
    }
  }
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    string prev_date = "";
    map<string, vector<int> > m;
    map<string, int> total;
    for (int i = 0; i < N; i++) {
      string date, time, act, id;
      cin >> date >> time >> act >> id;
      if (date != prev_date) {
        countup(total, m);
        m.clear();
      }
      m[id].push_back(parse(time));
      prev_date = date;
    }
    countup(total, m);
    int ans = 0;
    for (map<string, int>::const_iterator it = total.begin(); it != total.end(); ++it) {
      ans = max(ans, it->second);
    }
    cout << ans << endl;
  }
  return 0;
}
