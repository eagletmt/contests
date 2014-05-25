#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i];
    }
    const vector<int>::iterator last = unique(v.begin(), v.end());
    copy(v.begin(), last, ostream_iterator<int>(cout, " "));
    cout << "$" << endl;
  }
  return 0;
}
