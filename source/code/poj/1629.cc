#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int N, M, P;
  cin >> N >> M >> P;
  vector<int> cnt(26, 0);
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
      ++cnt[*it-'A'];
    }
  }
  for (int i = 0; i < P; i++) {
    string s;
    cin >> s;
    for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
      --cnt[*it-'A'];
    }
  }
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < cnt[i]; j++) {
      cout << char('A'+i);
    }
  }
  cout << endl;
  return 0;
}
