#include <iostream>
using namespace std;

int main(void)
{
  int L, M;
  while (cin >> L >> M && L+M != 0) {
    L++;
    for (int i = 0; i < M; i++) {
      int start, end;
      cin >> start >> end;
      L -= end - start + 1;
    }
    cout << L << endl;
  }
  return 0;
}
