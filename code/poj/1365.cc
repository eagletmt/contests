#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int pow(int p, int e)
{
  if (e == 0) {
    return 1;
  } else if ((e & 1) == 0) {
    const int x = pow(p, e>>1);
    return x*x;
  } else {
    return p * pow(p, e-1);
  }
}

int main()
{
  for (string s; getline(cin, s) && s != "0";) {
    int n = 1;
    {
      istringstream iss(s);
      for (int p, e; iss >> p >> e;) {
        n *= pow(p, e);
      }
    }
    --n;

    vector<pair<int,int> > v;
    for (int i = 2; n != 1; i++) {
      pair<int,int> p(i, 0);
      while (n % i == 0) {
        n /= i;
        ++p.second;
      }
      if (p.second != 0) {
        v.push_back(p);
      }
    }
    if (v.empty()) {
      cout << "1 1" << endl;
    } else {
      for (vector<pair<int,int> >::const_reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
        if (it != v.rbegin()) {
          cout << " ";
        }
        cout << it->first << " " << it->second;
      }
      cout << endl;
    }
  }
  return 0;
}
