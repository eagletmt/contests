#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

bool vowel(char c)
{
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int syllables(const string& word)
{
  int c = 0;
  for (string::const_iterator it = word.begin(); it != word.end();) {
    if (vowel(*it)) {
      ++c;
      while (it != word.end() && vowel(*it)) {
        ++it;
      }
    } else {
      ++it;
    }
  }
  return c;
}

int main()
{
  string inp;
  while (getline(cin, inp) && inp != "e/o/i") {
    vector<int> cs;
    istringstream iss(inp);
    string line;
    while (getline(iss, line, '/')) {
      int c = 0;
      istringstream ss(line);
      string word;
      while (ss >> word) {
        c += syllables(word);
      }
      cs.push_back(c);
    }
    if (cs[0] == 5 && cs[1] == 7 && cs[2] == 5) {
      cout << "Y" << endl;
    } else {
      for (int i = 0; i < 3; i++) {
        static int tbl[] = {5, 7, 5};
        if (cs[i] != tbl[i]) {
          cout << i+1 << endl;
          break;
        }
      }
    }
  }
  return 0;
}
