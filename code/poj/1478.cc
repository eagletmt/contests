#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct stmt
{
  int speaker, target, info;
  bool is_not;
};

stmt parse(const string& line)
{
  istringstream iss(line);
  string s;
  iss >> s;
  stmt t;
  t.speaker = s[0]-'A';
  t.is_not = false;
  iss >> s;
  if (s == "It") {
    t.target = -1;
    iss >> s;
    iss >> s;
    t.info = s == "day.";
  } else {
    t.target = s == "I" ? t.speaker : s[0]-'A';
    iss >> s;
    iss >> s;
    if (s == "not") {
      t.is_not = true;
      iss >> s;
    }
    if (s == "divine.") {
      t.info = 0;
    } else if (s == "human.") {
      t.info = 1;
    } else if (s == "evil.") {
      t.info = 2;
    } else {
      t.info = 3;
    }
  }
  return t;
}

bool say_true(int type, int day)
{
  switch (type) {
    case 0: //divine
      return true;
    case 1: //human
      return day;
    case 2: //evil
      return false;
  }
  throw "say_true";
}

bool ok(const vector<stmt>& info, const int a[5], int f)
{
  for (vector<stmt>::const_iterator it = info.begin(); it != info.end(); ++it) {
    const int speaker_type = a[it->speaker];
    const bool truthful_speaker = say_true(speaker_type, f);
    if (it->target == -1) {
      // day or night
      const bool correct_stmt = f == it->info;
      if (truthful_speaker != correct_stmt) {
        return false;
      }
    } else {
      const int target_type = a[it->target];

      bool r;
      if (it->info == 3) {
        const bool truthful_target = say_true(target_type, f);
        r = truthful_speaker == truthful_target;
      } else {
        bool correct_stmt = it->info == target_type;
        r = truthful_speaker != correct_stmt;
      }
      if (it->is_not) {
        r = !r;
      }
      if (r) {
        return false;
      }
    }
  }
  return true;
}

void answer(const int possible[5][3][2], int exists[5])
{
  int day_or_night = -1;
  int result[5];
  int cnt = 0;
  for (int i = 0; i < 5; i++) {
    result[i] = -1;
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 2; k++) {
        if (possible[i][j][k]) {
          ++cnt;
          if (result[i] == -1) {
            result[i] = j;
          } else if (result[i] == j) {
            // ok
          } else {
            // not deducible
            result[i] = -2;
          }
          if (day_or_night == -1) {
            day_or_night = k;
          } else if (day_or_night == k) {
            // ok
          } else {
            // not deducible
            day_or_night = -2;
          }
        }
      }
    }
  }
  if (cnt == 0) {
    cout << "This is impossible." << endl;
  } else {
    cnt = 0;
    for (int i = 0; i < 5; i++) {
      if (exists[i] && result[i] >= 0) {
        static const string tbl[] = {"divine", "human", "evil"};
        cout << char(i+'A') << " is " << tbl[result[i]] << "." << endl;
        ++cnt;
      }
    }
    if (day_or_night >= 0) {
      ++cnt;
      static const string tbl[] = {"night", "day"};
      cout << "It is " << tbl[day_or_night] << "." << endl;
    }
    if (cnt == 0) {
      cout << "No facts are deducible." << endl;
    }
  }
}

int main()
{
  int N;
  for (int Ti = 1; cin >> N && N != 0; Ti++) {
    cin.ignore();
    vector<stmt> info;
    int exists[5] = {0};
    for (int i = 0; i < N; i++) {
      string line;
      getline(cin, line);
      const stmt r = parse(line);
      info.push_back(r);
      exists[r.speaker] = true;
      if (r.target != -1) {
        exists[r.target] = true;
      }
    }

    int possible[5][3][2];
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 2; k++) {
          possible[i][j][k] = false;
        }
      }
    }
    int a[5];
    for (a[0] = 0; a[0] < 3; a[0]++) {
      for (a[1] = 0; a[1] < 3; a[1]++) {
        for (a[2] = 0; a[2] < 3; a[2]++) {
          for (a[3] = 0; a[3] < 3; a[3]++) {
            for (a[4] = 0; a[4] < 3; a[4]++) {
              for (int f = 0; f < 2; f++) {
                if (ok(info, a, f)) {
                  for (int i = 0; i < 5; i++) {
                    possible[i][a[i]][f] = true;
                  }
                }
              }
            }
          }
        }
      }
    }

    cout << "Conversation #" << Ti << endl;
    answer(possible, exists);
    cout << endl;
  }
  return 0;
}
