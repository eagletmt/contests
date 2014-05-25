#include <iostream>
#include <algorithm>
using namespace std;

int f(int miles, const string& code)
{
  if (code == "F") {
    return 2*miles;
  } else if (code == "B") {
    return 1.5*miles + 0.5;
  } else {
    return max(500, miles);
  }
}

int main()
{
  string city;
  while (cin >> city && city != "#") {
    string code;
    int miles;
    cin >> city >> miles >> code;
    int ans = f(miles, code);
    while (cin >> city && city != "0") {
      cin >> city >> miles >> code;
      ans += f(miles, code);
    }
    cout << ans << endl;
  }
  return 0;
}
