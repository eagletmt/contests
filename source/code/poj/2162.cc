#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  int N;
  cin >> N;
  cin.ignore();

  vector<string> lines;
  for (string line; getline(cin, line);) {
    lines.push_back(line);
  }
  const int M = lines.size();

  vector<string> pages;
  int i;
  for (i = N; i < M; i += N) {
    string page;
    if (lines[i].empty()) {
      // rule 1
      for (int j = i-N; j < i; j++) {
        page += " " + lines[j];
      }
      pages.push_back(page);
      ++i;
    } else if (!lines[i-1].empty() && (i+1 == M || (i+1 < M && lines[i+1].empty()))) {
      if (lines[i-2].empty() || lines[i-3].empty()) {
        // rule 4
        for (int j = i-N; j < i-2; j++) {
          page += " " + lines[j];
        }
        pages.push_back(page);
        if (lines[i-2].empty()) {
          i -= 1;
        } else {
          i -= 2;
        }
      } else {
        // rule 3
        for (int j = i-N; j < i-1; j++) {
          page += " " + lines[j];
        }
        pages.push_back(page);
        --i;
      }
    } else if (lines[i-2].empty() && !lines[i-1].empty()
        && !lines[i].empty() && i+1 < M && !lines[i+1].empty()) {
      // rule 2
      for (int j = i-N; j < i-1; j++) {
        page += " " + lines[j];
      }
      pages.push_back(page);
      --i;
    } else {
      for (int j = i-N; j < i; j++) {
        page += " " + lines[j];
      }
      pages.push_back(page);
    }
  }
  string buf;
  for (i -= N; i < M; i++) {
    buf += " " + lines[i];
  }
  pages.push_back(buf);

  map<string, vector<int> > dict;
  const int P = pages.size();
  for (i = 0; i < P; i++) {
    vector<string> v;
    buf = "";
    for (string::const_iterator it = pages[i].begin(); it != pages[i].end(); ++it) {
      if (isalpha(*it)) {
        buf += toupper(*it);
      } else {
        if (!buf.empty()) {
          v.push_back(buf);
        }
        buf.clear();
      }
    }
    if (!buf.empty()) {
      v.push_back(buf);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (vector<string>::const_iterator it = v.begin(); it != v.end(); ++it) {
      dict[*it].push_back(i+1);
    }
  }
  for (map<string, vector<int> >::const_iterator it = dict.begin(); it != dict.end(); ++it) {
    cout << it->first << " ";
    const vector<int>& v = it->second;
    vector<pair<int,int> > ans;
    ans.push_back(make_pair(v[0], v[0]));
    for (vector<int>::const_iterator jt = v.begin()+1; jt != v.end(); ++jt) {
      if (*jt == ans.back().second+1) {
        ++ans.back().second;
      } else {
        ans.push_back(make_pair(*jt, *jt));
      }
    }
    for (vector<pair<int,int> >::const_iterator jt = ans.begin(); jt != ans.end(); ++jt) {
      if (jt != ans.begin()) {
        cout << ",";
      }
      if (jt->first == jt->second) {
        cout << jt->first;
      } else if (jt->first+1 == jt->second) {
        cout << jt->first << "," << jt->second;
      } else {
        cout << jt->first << "-" << jt->second;
      }
    }
    cout << endl;
  }
  return 0;
}
