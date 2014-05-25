#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int count = 1;
  int depth;
  while (cin >> depth && depth != 0) {
    vector<int> v(depth);
    for (int i = 0; i < depth; i++) {
      char x;
      cin >> x >> v[i];
    }
    vector<int> stree(1<<depth);
    for (int i = 0; i < 1<<depth; i++) {
      char b;
      cin >> b;
      int c = 0;
      for (int j = 0; j < depth; j++) {
        c |= ((i&(1<<j))>>j)<<(depth-v[depth-j-1]);
      }
      stree[c] = b-'0';
    }

    int m;
    cin >> m;
    cout << "S-Tree #" << count++ << ':' << endl;
    for (int i = 0; i < m; i++) {
      string s;
      cin >> s;
      int b = 0;
      for (int j = 0; j < depth; j++) {
        b |= (s[j]-'0')<<(depth-j-1);
      }
      cout << stree[b];
    }
    cout << endl << endl;
  }
  return 0;
}
