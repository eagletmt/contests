#include <cstdio>
#include <algorithm>
using namespace std;

static const int Y = 10000;

void show(int d, int a)
{
  printf("%d-%02d-%02d ", d/Y, (d%Y)/100, d%100);
  if (a == 0) {
    puts("No merit or demerit points.");
  } else if (a < 0) {
    printf("%d demerit point(s).\n", -a);
  } else {
    printf("%d merit point(s).\n", a);
  }
}

void merit(int& date, int& acc, int x)
{
  while ((acc < 0 && date+Y <= x) || (acc >= 0 && acc < 5 && date+2*Y <= x)) {
    if (acc < 0) {
      acc = acc < -2 ? acc/2 : 0;
      date += Y;
    } else {
      ++acc;
      date += 2*Y;
    }
    show(date, acc);
  }
}

int main()
{
  int date;
  scanf("%d", &date);
  int acc = 0;
  show(date, acc);
  for (int d, x; scanf("%d %d", &d, &x) != EOF;) {
    merit(date, acc, d);
    if (acc < 0) {
      acc -= x;
    } else if (2*acc <= x) {
      acc = -x + 2*acc;
    } else {
      acc -= (x+1)/2;
    }
    date = d;
    show(date, acc);
  }
  merit(date, acc, 100000000);
  return 0;
}
