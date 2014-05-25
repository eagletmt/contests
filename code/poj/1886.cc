#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

pair<string, string> parse(const string& line)
{
  string::const_iterator it = line.begin();
  if (*it != '"') {
    throw "err1";
  }
  for (++it; *it != '"'; ++it);
  const string title(line.begin(), it+1);
  const string author(it+5, line.end());
  return make_pair(author, title);
}

int main()
{
  ios::sync_with_stdio(false);
  vector<pair<string, string> > shelf;
  map<string, string> dict;
  for (string line; getline(cin, line) && line != "END";) {
    const pair<string, string> r = parse(line);
    shelf.push_back(r);
    dict.insert(make_pair(r.second, r.first));
  }
  sort(shelf.begin(), shelf.end());

  vector<pair<string,string> > desk;
  for (string line; getline(cin, line) && line != "END";) {
    const string cmd = line.substr(0, 6);
    if (cmd == "SHELVE") {
      sort(desk.begin(), desk.end());
      for (vector<pair<string,string> >::const_iterator it = desk.begin(); it != desk.end(); ++it) {
        vector<pair<string,string> >::iterator jt = lower_bound(shelf.begin(), shelf.end(), *it);
        if (jt == shelf.begin()) {
          cout << "Put " << it->second << " first" << endl;
        } else {
          cout << "Put " << it->second << " after " << (jt-1)->second << endl;
        }
        shelf.insert(jt, *it);
      }
      desk.clear();
      cout << "END" << endl;
    } else {
      const string title = line.substr(7, line.size()-7);
      const pair<string, string> r = make_pair(dict[title], title);
      if (cmd == "BORROW") {
        vector<pair<string,string> >::iterator it = lower_bound(shelf.begin(), shelf.end(), r);
        shelf.erase(it);
      } else {
        desk.push_back(r);
      }
    }
  }
  return 0;
}
