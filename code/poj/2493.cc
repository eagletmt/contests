#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    map<string, int> dict;
    for (int i = 0; i < N; i++) {
      string word;
      cin >> word;
      if (word.size() > 2) {
        sort(word.begin()+1, word.begin()+word.size()-1);
      }
      ++dict[word];
    }
    int M;
    cin >> M;
    cin.ignore();
    cout << "Scenario #" << Ti << ":" << endl;
    while (M-- > 0) {
      string line;
      getline(cin, line);
      int ans = 1;
      istringstream iss(line);
      string word;
      while (iss >> word) {
        if (word.size() > 2) {
          sort(word.begin()+1, word.begin()+word.size()-1);
        }
        ans *= dict[word];
      }
      cout << ans << endl;
    }
    cout << endl;
  }
  return 0;
}
