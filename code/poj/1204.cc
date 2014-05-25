#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct ans
{
  int i, j, dir;
  ans() : i(-1), j(-1), dir(-1) {}
  ans(int a, int b, int c) : i(a), j(b), dir(c) {}
};

int L, C;
char grid[1000][1000];
ans ret[1000];
static const int di[] = {-1, -1, 0, 1, 1, 1, 0, -1};
static const int dj[] = {0, 1, 1, 1, 0, -1, -1, -1};

struct AhoCorasick
{
  struct node {
    node *failure;
    node *edge[26];
    vector<int> accepted;

    ~node() {
      for (int i = 0; i < 26; i++) {
        if (edge[i] != this) {
          delete edge[i];
        }
      }
    }
  };

  node *root;

  AhoCorasick(const char words[1000][1001], int W)
    : root(new node())
  {
    // build trie
    for (int i = 0; i < W; i++) {
      const char *s = words[i];
      node *u = root;
      for (int j = 0; s[j] != '\0'; j++) {
        const int idx = s[j] - 'A';
        if (!u->edge[idx]) {
          u->edge[idx] = new node();
        }
        u = u->edge[idx];
      }
      u->accepted.push_back(i);
    }

    // build failure link
    root->failure = 0;
    queue<node *> q;
    for (int i = 0; i < 26; i++) {
      if (root->edge[i]) {
        node *next = root->edge[i];
        q.push(next);
        next->failure = root;
      } else {
        root->edge[i] = root;
      }
    }
    while (!q.empty()) {
      node *u = q.front();
      q.pop();
      for (int i = 0; i < 26; i++) {
        node *next = u->edge[i];
        if (next) {
          q.push(next);
          node *rev = u->failure;
          while (!rev->edge[i]) {
            rev = rev->failure;
          }
          next->failure = rev->edge[i];
          const vector<int> &v = next->failure->accepted;
          for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
            next->accepted.push_back(*it);
          }
        }
      }
    }
  }

  ~AhoCorasick() {
    delete root;
  }

  void match(int i, int j, int d) const
  {
    node *u = root;
    for (; 0 <= i && i < L && 0 <= j && j < C; i += di[d], j += dj[d]) {
      const int idx = grid[i][j] - 'A';
      while (!u->edge[idx]) {
        u = u->failure;
      }
      u = u->edge[idx];
      for (vector<int>::const_iterator jt = u->accepted.begin(); jt != u->accepted.end(); ++jt) {
        ret[*jt] = ans(i, j, d);
      }
    }
  }
};

int main()
{
  int W;
  scanf("%d %d %d", &L, &C, &W);
  for (int i = 0; i < L; i++) {
    scanf("%s", grid[i]);
  }
  static char words[1000][1001];
  for (int i = 0; i < W; i++) {
    scanf("%s", words[i]);
  }

  AhoCorasick ac(words, W);
  for (int i = 0; i < L; i++) {
    ac.match(i, 0, 1);
    ac.match(i, 0, 2);
    ac.match(i, 0, 3);
    ac.match(i, C-1, 5);
    ac.match(i, C-1, 6);
    ac.match(i, C-1, 7);
  }
  for (int j = 0; j < C; j++) {
    ac.match(L-1, j, 7);
    ac.match(L-1, j, 0);
    ac.match(L-1, j, 1);
    ac.match(0, j, 3);
    ac.match(0, j, 4);
    ac.match(0, j, 5);
  }

  for (int i = 0; i < W; i++) {
    const ans& a = ret[i];
    const int n = strlen(words[i]) - 1;
    printf("%d %d %c\n", a.i - di[a.dir]*n, a.j - dj[a.dir]*n, 'A' + a.dir);
  }
  return 0;
}
