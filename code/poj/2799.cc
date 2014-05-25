#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

string show(unsigned u)
{
  ostringstream oss;
  oss << ((u>>24)&0xFF) << "." << ((u>>16)&0xFF) << "." << ((u>>8)&0xFF) << "." << (u&0xFF);
  return oss.str();
}

int main()
{
  int M;
  cin >> M;
  unsigned l = numeric_limits<unsigned>::max();
  unsigned h = 0;
  for (int i = 0; i < M; i++) {
    unsigned a, b, c, d;
    char e;
    cin >> a >> e >> b >> e >> c >> e >> d;
    const unsigned f = (a<<24) | (b<<16) | (c<<8) | d;
    l = min(l, f);
    h = max(h, f);
  }

  unsigned m;
  for (int n = 0; n <= 32; n++) {
    m = ~((1ULL<<n)-1U);
    if ((l & m) == (h & m)) {
      break;
    }
  }

  cout << show(l & m) << endl;
  cout << show(m) << endl;
  return 0;
}
