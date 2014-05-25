#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

int parse(const string& s)
{
  int h = 0;
  string::const_iterator it = s.begin();
  while (*it != ':') {
    h = 10*h + (*it-'0');
    ++it;
  }
  ++it;
  int m = 0;
  while (it != s.end()) {
    m = 10*m + (*it-'0');
    ++it;
  }
  if (h == 12) {
    h = 0;
  }
  return h*60+m;
}

int main()
{
  map<string,int> tz;
  tz["UTC"] = 0;
  tz["GMT"] = 0;
  tz["BST"] = +1*60;
  tz["IST"] = +1*60;
  tz["WET"] = 0;
  tz["WEST"] = +1*60;
  tz["CET"] = +1*60;
  tz["CEST"] = +2*60;
  tz["EET"] = +2*60;
  tz["EEST"] = +3*60;
  tz["MSK"] = +3*60;
  tz["MSD"] = +4*60;
  tz["AST"] = -4*60;
  tz["ADT"] = -3*60;
  tz["NST"] = -3*60-30;
  tz["NDT"] = -2*60-30;
  tz["EST"] = -5*60;
  tz["EDT"] = -4*60;
  tz["CST"] = -6*60;
  tz["CDT"] = -5*60;
  tz["MST"] = -7*60;
  tz["MDT"] = -6*60;
  tz["PST"] = -8*60;
  tz["PDT"] = -7*60;
  tz["HST"] = -10*60;
  tz["AKST"] = -9*60;
  tz["AKDT"] = -8*60;
  tz["AEST"] = +10*60;
  tz["AEDT"] = +11*60;
  tz["ACST"] = +9*60+30;
  tz["ACDT"] = +10*60+30;
  tz["AWST"] = +8*60;

  string line;
  getline(cin, line);
  int N;
  {
    istringstream iss(line);
    iss >> N;
  }
  while (N-- > 0) {
    getline(cin, line);
    istringstream iss(line);
    vector<string> tks;
    for (string s; iss >> s; tks.push_back(s));
    int t;
    int from, to;
    if (tks.size() == 4) {
      t = parse(tks[0]);
      if (tks[1] == "p.m.") {
        t += 12*60;
      }
      if (!tz.count(tks[2]) || !tz.count(tks[3])) {
        throw "honi";
      }
      from = tz[tks[2]];
      to = tz[tks[3]];
    } else {
      if (tks[0] == "noon") {
        t = 12*60;
      } else {
        t = 0;
      }
      if (!tz.count(tks[1]) || !tz.count(tks[2])) {
        throw "honi";
      }
      from = tz[tks[1]];
      to = tz[tks[2]];
    }
    t = t - from + to;
    t = (t+24*60)%(24*60);
    if (t == 0) {
      cout << "midnight" << endl;
    } else if (t == 12*60) {
      cout << "noon" << endl;
    } else if (t < 12*60) {
      int h = t/60;
      if (h == 0) {
        h = 12;
      }
      printf("%d:%02d a.m.\n", h, t%60);
    } else {
      t -= 12*60;
      int h = t/60;
      if (h == 0) {
        h = 12;
      }
      printf("%d:%02d p.m.\n", h, t%60);
    }
  }
  return 0;
}
