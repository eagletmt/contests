#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<pair<string,int> > q[2][26];
    vector<int> com_output[26];
    map<string, pair<int,int> > deal_output;
    for (int i = 0; i < N; i++) {
      string name, action;
      char com;
      int price;
      cin >> name >> action >> com >> price;
      const int c = com - 'A';
      const bool b = action == "SELL";
      if (!deal_output.count(name)) {
        deal_output[name] = make_pair(0, 0);
      }
      vector<pair<string,int> >::iterator it = q[b][c].end();
      if (b) {
        for (vector<pair<string,int> >::iterator jt(q[b][c].begin()); jt != q[b][c].end(); ++jt) {
          if (jt->first != name && jt->second >= price
              && (it == q[b][c].end() || it->second < jt->second)) {
            it = jt;
          }
        }
      } else {
        for (vector<pair<string,int> >::iterator jt(q[b][c].begin()); jt != q[b][c].end(); ++jt) {
          if (jt->first != name && jt->second <= price
              && (it == q[b][c].end() || it->second > jt->second)) {
            it = jt;
          }
        }
      }
      if (it == q[b][c].end()) {
        q[!b][c].push_back(make_pair(name, price));
      } else {
        const int p = (price + it->second) / 2;
        com_output[c].push_back(p);
        deal_output[b ? name : it->first].second += p;
        deal_output[b ? it->first : name].first += p;
        q[b][c].erase(it);
      }
    }
    for (int c = 0; c < 26; c++) {
      if (!com_output[c].empty()) {
        const vector<int>& v = com_output[c];
        int lowest = v[0], highest = v[0], sum = 0;
        for (vector<int>::const_iterator it(v.begin()); it != v.end(); ++it) {
          lowest = min(lowest, *it);
          highest = max(highest, *it);
          sum += *it;
        }
        cout << char('A'+c) << ' ' << lowest << ' ' << sum/v.size() << ' ' << highest << endl;
      }
    }
    cout << "--" << endl;
    for (map<string, pair<int,int> >::const_iterator it(deal_output.begin()); it != deal_output.end(); ++it) {
      cout << it->first << ' ' << it->second.first << ' ' << it->second.second << endl;
    }
    cout << "----------" << endl;
  }
  return 0;
}
