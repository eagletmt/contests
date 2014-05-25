#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

string to_s(int n)
{
  ostringstream oss;
  oss << n;
  return oss.str();
}

vector<pair<int,string> > solve(int N)
{
  if (N <= 0) {
    return vector<pair<int,string> >();
  }
  vector<pair<int,string> > ans;
  for (int b = 0; b < 10 && N-b >= 0; b++) {
    const int a11 = N-b;
    if (a11 % 11 == 0) {
      const int a = a11 / 11;
      if (a == 0) {
        ans.push_back(make_pair(10*a+b, ""));
      } else {
        ans.push_back(make_pair(10*a+b, to_s(a)));
      }
    }
  }
  const int x = N%10;
  if (x % 2 == 0) {
    const int y = x/2, z = x/2+5;
    const string yy = to_s(y), zz = to_s(z);
    const vector<pair<int,string> > t = solve(N/10), s = solve(N/10-1);
    for (vector<pair<int,string> >::const_iterator it = t.begin(); it != t.end(); ++it) {
      ans.push_back(make_pair(10*it->first + y, it->second + yy));
    }
    for (vector<pair<int,string> >::const_iterator it = s.begin(); it != s.end(); ++it) {
      ans.push_back(make_pair(10*it->first + z, it->second + zz));
    }
  }
  return ans;
}

int main()
{
  int N;
  cin >> N;
  vector<pair<int,string> > ans = solve(N);
  sort(ans.begin(), ans.end());
  ans.erase(unique(ans.begin(), ans.end()), ans.end());
  cout << ans.size() << endl;
  for (vector<pair<int,string> >::const_iterator it = ans.begin(); it != ans.end(); ++it) {
    cout << it->first << " + " << it->second << " = " << N << endl;
  }
  return 0;
}
