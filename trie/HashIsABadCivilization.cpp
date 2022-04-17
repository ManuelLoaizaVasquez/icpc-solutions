//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e6;

struct Node {
  bool found;
  int id;
  int last_end;
  int cnt;
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int b;
  cin >> b;
  string s;
  cin >> s;
  int n = (int) s.size();
  vector<int> node(n, -1);
  // Caso base: Longitud 1
  for (int i = 0; i < n; i++) {
    int c = s[i] - '0';
    node[i] = c;
  }
  int ans = 0;
  // Para longitudes >= 2
  vector<vector<Node>> dp((int) node.size(), vector<Node>(2, {false, -1, -1, 0}));
  for (int len = 2; len <= b; len++) {
    for (int i = 0; i < (int) node.size(); i++) {
      for (int j = 0; j < 2; j++) {
        dp[i][j] = {false, -1, -1, 0};
      }
    }
    vector<int> new_node;
    int nodes = 0;
    int tmp = 0;
    for (int i = 0; i + len - 1 < n; i++) {
      int last = i + len - 1;
      int c = s[last] - '0';
      int parent_node = node[i];
      if (!dp[parent_node][c].found) {
        dp[parent_node][c] = {true, nodes, last, 1};
        nodes++;
      } else {
        if (dp[parent_node][c].last_end < last - len + 1) {
          dp[parent_node][c].last_end = last;
          dp[parent_node][c].cnt++;
        }
      }
      new_node.push_back(dp[parent_node][c].id);
      tmp = max(tmp, dp[parent_node][c].cnt);
    }
    ans = max(ans, (len - 1) * tmp);
    node = new_node;
  }
  cout << n - ans << '\n';
  return 0;
}
