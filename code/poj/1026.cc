#include <iostream>
#include <vector>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  int N;
  while (cin >> N && N != 0) {
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
      cin >> a[i];
      --a[i];
    }
    vector<int> periods(N, 1);
    for (int i = 0; i < N; i++) {
      for (int j = a[i]; j != i; j = a[j]) {
        ++periods[i];
      }
    }

    int k;
    while (cin >> k && k != 0) {
      cin.ignore();
      string msg;
      getline(cin, msg);
      string buf(N, ' '), ans(N, ' ');
      copy(msg.begin(), msg.end(), buf.begin());
      for (int i = 0; i < N; i++) {
        const int M = k % periods[i];
        int j = i;
        for (int c = 0; c < M; c++) {
          j = a[j];
        }
        ans[j] = buf[i];
      }
      cout << ans << endl;
    }
    cout << endl;
  }
  return 0;
}
