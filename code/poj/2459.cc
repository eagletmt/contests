#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct present
{
  int day;
  present(int d) : day(d) {}
  bool operator()(const pair<int,int>& c) const
  {
    return c.first <= day && day <= c.second;
  }
};

int main()
{
  int C, F1, F2, D;
  cin >> C >> F1 >> F2 >> D;
  vector<pair<int,int> > cows(C);
  for (int i = 0; i < C; i++) {
    cin >> cows[i].first >> cows[i].second;
  }

  int f = F2 + count_if(cows.begin(), cows.end(), present(D));
  while (f < F1) {
    --D;
    f += count_if(cows.begin(), cows.end(), present(D));
  }
  cout << D << endl;
  return 0;
}
