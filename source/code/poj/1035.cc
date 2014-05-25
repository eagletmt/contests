#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct fixed_string
{
  char buf[20];
  int len;
  bool operator==(const fixed_string& s) const { return strcmp(buf, s.buf) == 0; }
  const char& operator[](int i) const { return buf[i]; }
};

bool deleting(const fixed_string& correct, const fixed_string& inp)
{
  const int M = correct.len, N = inp.len;
  if (N != M+1) {
    return false;
  }
  for (int i = 0; i < N; i++) {
    if (inp[i] != correct[i]) {
      fixed_string s;
      memcpy(s.buf, inp.buf, i);
      strcpy(s.buf+i, inp.buf+i+1);
      if (s == correct) {
        return true;
      }
    }
  }
  return false;
}

bool replacing(const fixed_string& correct, const fixed_string& inp)
{
  const int M = correct.len, N = inp.len;
  if (N != M) {
    return false;
  }
  int c = 0;
  for (int i = 0; i < N; i++) {
    if (correct[i] != inp[i]) {
      ++c;
    }
  }
  return c <= 1;
}

bool inserting(const fixed_string& correct, const fixed_string& inp)
{
  const int M = correct.len, N = inp.len;
  if (N+1 != M) {
    return false;
  }
  for (int i = 0; i < M; i++) {
    if (inp[i] != correct[i]) {
      fixed_string s;
      memcpy(s.buf, inp.buf, i);
      s.buf[i] = correct[i];
      strcpy(s.buf+i+1, inp.buf+i);
      if (s == correct) {
        return true;
      }
    }
  }
  return false;
}

int main()
{
  vector<fixed_string> dict;
  for (fixed_string s; scanf("%s", s.buf) && s.buf[0] != '#';) {
    s.len = strlen(s.buf);
    dict.push_back(s);
  }

  for (fixed_string s; scanf("%s", s.buf) && s.buf[0] != '#';) {
    s.len = strlen(s.buf);
    if (find(dict.begin(), dict.end(), s) != dict.end()) {
      printf("%s is correct\n", s.buf);
      continue;
    }

    printf("%s:", s.buf);
    for (vector<fixed_string>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
      if (deleting(*it, s) || replacing(*it, s) || inserting(*it, s)) {
        printf(" %s", it->buf);
      }
    }
    putchar('\n');
  }
  return 0;
}
