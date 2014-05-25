#include <cstdio>
#include <algorithm>
using namespace std;

bool dfs(int x, int y)
{
  // x <= y
  if (x == 0) {
    return false;
  } else if (y/x == 1) {
    return !dfs(y-x, x);
  } else {
    return true;
  }
}

int main()
{
  int x, y;
  while (scanf("%d %d", &x, &y) && x != 0) {
    if (x > y) {
      swap(x, y);
    }
    puts(dfs(x, y) ? "Stan wins" : "Ollie wins");
  }
  return 0;
}
