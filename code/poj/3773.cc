#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct AhoCorasick/*{{{*/
{
  struct node {
    int id;
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

  AhoCorasick(const vector<string> words) : root(new node())
  {
    root->id = 0;
    // build trie
    for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
      node *u = root;
      for (string::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
        const int idx = *jt - 'a';
        if (!u->edge[idx]) {
          u->edge[idx] = new node();
          u->edge[idx]->id = jt - it->begin() + 1;
        }
        u = u->edge[idx];
      }
      u->accepted.push_back(it - words.begin());
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

  node *next_node(node *u, char c) const
  {
    const int idx = c-'a';
    while (!u->edge[idx]) {
      u = u->failure;
    }
    return u->edge[idx];
  }
};/*}}}*/

int main()
{
  ios::sync_with_stdio(false);
  string s;
  while (getline(cin, s) && s != "0") {
    const vector<string> words(1, s);
    const int M = s.size();
    AhoCorasick ac(words);
    AhoCorasick::node *u = ac.root;
    for (int i = 0; i <= M; i++) {
      cout << i;
      for (int j = 0; j < 26; j++) {
        AhoCorasick::node *t = ac.next_node(u, 'a'+j);
        cout << " " << t->id;
      }
      cout << endl;
      if (i < M) {
        u = ac.next_node(u, s[i]);
      }
    }
  }
  return 0;
}
