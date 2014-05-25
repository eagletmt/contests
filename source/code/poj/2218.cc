#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  string msg;
  while (cin >> msg) {
    vector<pair<int,string> > v;
    string name;
    while (cin >> name && name != "END") {
      int days, weight;
      cin >> days >> weight;
      v.push_back(make_pair(weight-days, name));
    }
    sort(v.rbegin(), v.rend());
    for (vector<pair<int,string> >::const_iterator it = v.begin(); it != v.end(); ++it) {
      cout << it->second << endl;
    }
    cout << endl;
  }
  return 0;
}
