#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

string to_seq(string word)
{
  for (string::iterator it = word.begin(); it != word.end(); ++it) {
    switch (*it) {
      case 'a' ... 'c': *it = '2'; break;
      case 'd' ... 'f': *it = '3'; break;
      case 'g' ... 'i': *it = '4'; break;
      case 'j' ... 'l': *it = '5'; break;
      case 'm' ... 'o': *it = '6'; break;
      case 'p' ... 's': *it = '7'; break;
      case 't' ... 'v': *it = '8'; break;
      case 'w' ... 'z': *it = '9'; break;
    }
  }
  return word;
}

void dfs(const vector<pair<string,string> >& dic, const string& seq, vector<string>& ans, const string& word = "")
{
  if (seq.empty()) {
    ans.push_back(word);
  } else {
    for (vector<pair<string,string> >::const_iterator it = dic.begin(); it != dic.end(); ++it) {
      if (seq.size() >= it->second.size() && seq.find(it->second) == 0) {
        dfs(dic, seq.substr(it->second.size()), ans, word + it->first + " ");
      }
    }
  }
}

struct format
{
  void operator()(string& w) const { w[w.size()-1] = '.'; }
};

int main()
{
  int N;
  ostream_iterator<string> oiter(cout, "\n");
  while (cin >> N && N != 0) {
    vector<pair<string,string> > dic(N);
    for (int i = 0; i < N; i++) {
      cin >> dic[i].first;
      dic[i].second = to_seq(dic[i].first);
    }
    string seq;
    cin >> seq;
    vector<string> ans;
    dfs(dic, seq, ans);
    sort(ans.begin(), ans.end());
    for_each(ans.begin(), ans.end(), format());
    copy(ans.begin(), ans.end(), oiter);
    *oiter++ = "--";
  }
  return 0;
}
