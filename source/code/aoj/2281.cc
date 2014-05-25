#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    string s;
    cin >> s;
    vector<pair<int,int> > v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i].first >> v[i].second;
      --v[i].first; --v[i].second;
    }

    for (vector<pair<int,int> >::const_reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
      const int gap = abs(it->first - it->second);
      swap(s[it->first], s[it->second]);
      s[it->first] = ((s[it->first]-'a'+gap)%26)+'a';
      s[it->second] = ((s[it->second]-'a'+gap)%26)+'a';
    }
    cout << s << endl;
  }
  return 0;
}
