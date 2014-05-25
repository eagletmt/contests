#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  vector<vector<string> > lines;
  size_t max_words = 0;
  for (char buf[200]; fgets(buf, sizeof buf, stdin) != NULL;) {
    vector<string> words;
    char word[100];
    char *p = buf;
    int n;
    while (sscanf(p, "%s%n", word, &n) != EOF) {
      words.push_back(word);
      p += n;
    }
    lines.push_back(words);
    max_words = max(max_words, words.size());
  }
  const int N = lines.size();

  vector<int> lens;
  for (size_t j = 0; j < max_words; j++) {
    size_t len = 0;
    for (int i = 0; i < N; i++) {
      if (j < lines[i].size()) {
        len = max(len, lines[i][j].size());
      }
    }
    lens.push_back(len);
  }

  for (int i = 0; i < N; i++) {
    const int M = lines[i].size();
    for (int j = 0; j < M; j++) {
      if (j != 0) {
        putchar(' ');
      }
      fputs(lines[i][j].c_str(), stdout);
      if (j != M-1) {
        for (int k = lines[i][j].size(); k < lens[j]; k++) {
          putchar(' ');
        }
      }
    }
    putchar('\n');
  }
  return 0;
}
