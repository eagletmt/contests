#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct picture
{
  int height, width;
  vector<string> bitmap;
};

struct object
{
  const picture *pic;
  int posx, posy;
  string relative_to;
  int layer;
  int index;

  bool operator<(const object& o) const
  {
    if (layer != o.layer) {
      return layer < o.layer;
    } else {
      return index < o.index;
    }
  }
};

struct renderer
{
  map<string, picture> pictures;
  map<string, object> objects;

  void add_object(const string& id, const string& fname, object& o)
  {
    o.pic = &pictures[fname];
    objects.insert(make_pair(id, o));
  }

  void render()
  {
    vector<object> v;
    for (map<string, object>::iterator it = objects.begin(); it != objects.end(); ++it) {
      fix_position(it->second);
      v.push_back(it->second);
    }
    int W = 0, H = 0;
    for (vector<object>::const_iterator it = v.begin(); it != v.end(); ++it) {
      W = max(W, it->posx + it->pic->width);
      H = max(H, it->posy + it->pic->height);
    }
    sort(v.begin(), v.end());
    vector<string> img(H, string(W, ' '));
    for (vector<object>::const_iterator it = v.begin(); it != v.end(); ++it) {
      for (int i = 0; i < it->pic->height; i++) {
        for (int j = 0; j < it->pic->width; j++) {
          const char src = it->pic->bitmap[i][j];
          if (src != ' ') {
            img[it->posy + i][it->posx + j] = src;
          }
        }
      }
    }
    for (int i = 0; i < H; i++) {
      cout << img[i] << endl;
    }
  }

  void fix_position(object& o)
  {
    if (o.relative_to.empty()) {
      return;
    }
    object& target = objects[o.relative_to];
    fix_position(target);
    o.posx += target.posx;
    o.posy += target.posy;
    o.relative_to = "";
  }
};

int main()
{
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    renderer r;
    for (int i = 0; i < N; i++) {
      string fname;
      picture pic;
      cin >> fname >> pic.height >> pic.width;
      pic.bitmap.resize(pic.height);
      for (int j = 0; j < pic.height; j++) {
        string& row = pic.bitmap[j];
        cin >> row;
        replace(row.begin(), row.end(), '.', ' ');
      }
      r.pictures.insert(make_pair(fname, pic));
    }
    int M;
    cin >> M;
    cin.ignore();
    for (int i = 0; i < M; i++) {
      string s;
      getline(cin, s);
      replace(s.begin(), s.end(), '#', ' ');
      replace(s.begin(), s.end(), '{', ' ');
      string id;
      {
        istringstream iss(s);
        iss >> id;
      }
      object o;
      o.index = i;
      string file;
      for (int j = 0; j < 5; j++) {
        getline(cin, s);
        replace(s.begin(), s.end(), ':', ' ');
        replace(s.begin(), s.end(), ';', ' ');
        replace(s.begin(), s.end(), '=', ' ');
        istringstream iss(s);
        string key;
        iss >> key;
        if (key == "pos-x") {
          iss >> o.posx;
        } else if (key == "pos-y") {
          iss >> o.posy;
        } else if (key == "position") {
          string spec;
          iss >> spec;
          if (spec[0] == 'r') {
            iss >> o.relative_to;
          } else {
            o.relative_to = "";
          }
        } else if (key == "file") {
          iss >> file;
        } else if (key == "layer") {
          iss >> o.layer;
        } else {
          throw __LINE__;
        }
      }
      getline(cin, s);
      r.add_object(id, file, o);
    }
    cout << "Scenario #" << Ti << ":" << endl;
    r.render();
    cout << endl;
  }
  return 0;
}
