#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int c2i(const string& s)
{
  int n;
  switch (s[s.size()-1]) {
    case 'C': n = 0;  break;
    case 'D': n = 1;  break;
    case 'H': n = 2;  break;
    case 'S': n = 3;  break;
    default:  throw s;
  }
  n *= 13;
  switch (s[0]) {
    case 'A': n += 1; break;
    case '2' ... '9': n += s[0]-'0';  break;
    case '1': n += 10;  break;
    case 'J': n += 11;  break;
    case 'Q': n += 12;  break;
    case 'K': n += 13;  break;
    default: throw s;
  }
  return n;
}

struct trie
{
  map<int,trie> m;
  typedef vector<int>::const_iterator Iterator;

  void insert(Iterator it, const Iterator& last)
  {
    if (it == last) {
      return;
    }
    const int n = *it;
    ++it;
    m[n].insert(it, last);
  }

  int size() const
  {
    int r = 1;
    for (map<int,trie>::const_iterator it = m.begin(); it != m.end(); ++it) {
      r += it->second.size();
    }
    return r;
  }
};

int main()
{
  ios::sync_with_stdio(false);
  int N;
  while (cin >> N && N != 0) {
    trie t;
    for (int i = 0; i < N; i++) {
      int K;
      cin >> K;
      vector<int> cards;
      for (int i = 0; i < K; i++) {
        string s;
        cin >> s;
        cards.push_back(c2i(s));
      }
      sort(cards.rbegin(), cards.rend());
      t.insert(cards.begin(), cards.end());
    }
    cout << t.size()-1 << endl;
  }
  return 0;
}
