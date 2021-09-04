#define _GLIBCXX_DEBUG // test only

#include <bits/stdc++.h>
using namespace std;

class SCC {
  int n;
  vector<vector<int>> g;
  vector<vector<int>> rg;
  vector<int> vs;
  vector<bool> used;
  vector<int> cmp;

public:
  SCC(int m) {
    n = m;
    for (int i=0;i<n;i++) {
      g.emplace_back();
      rg.emplace_back();
      used.emplace_back();
      cmp.emplace_back();
    }
  }

  void add_edge(int from, int to) {
    g[from].emplace_back(to);
    rg[to].emplace_back(from);
  }

  void dfs(int v) {
    used[v] = true;
    for (int i=0;i<g[v].size();i++) {
      int to = g[v][i];
      if (!used[to]) dfs(to);
    }
    vs.emplace_back(v);
  }

  void rdfs(int v, int k) {
    used[v] = true;
    cmp[v] = k;
    for (int i=0;i<rg[v].size();i++) {
      int to = rg[v][i];
      if (!used[to]) rdfs(to,k);
    }
  }

  vector<vector<int>> scc() {
    for (int i=0;i<n;i++) used[i] = false;
    vs.clear();
    for (int i=0;i<n;i++) {
      if (!used[i]) dfs(i);
    }
    for (int i=0;i<n;i++) used[i] = false;
    int k = 0;
    for (int i=vs.size()-1;i >= 0;i--) {
      if (!used[vs[i]]) rdfs(vs[i],k++);
    }
    vector<vector<int>> res(k);
    for (int i=0;i<n;i++) {
      res[cmp[i]].emplace_back(i);
    }
    return res;
  }
};

int main() {
  
  ios::sync_with_stdio(false);
  cin.tie(0);
  string p,cnf;
  int n,m;
  cin >> p >> cnf >> n >> m;
  vector<int> a(m), b(m);
  SCC sc(n*2);
  // n,n+1,...,2n-1 express -.
  for (int i=0;i<m;i++) {
    int zer;
    cin >> a[i] >> b[i] >> zer;
    int from,to;
    from = -a[i];
    to = b[i];
    if (from < 0) from = abs(from)+n;
    if (to < 0) to = abs(to)+n;
    from--;to--;
    sc.add_edge(from,to);
    from = -b[i];
    to = a[i];
    if (from < 0) from = abs(from)+n;
    if (to < 0) to = abs(to)+n;
    from--;to--;
    sc.add_edge(from,to);
  }
  vector<vector<int>> res = sc.scc();
  vector<int> lis(n*2);
  for (int i=0;i<res.size();i++) {
    for (int j=0;j<res[i].size();j++) {
      int now = res[i][j];
      lis[now] = i;
    }
  }
  bool ok = true;
  for (int i=0;i<n;i++) {
    if (lis[i] == lis[i+n]) {
      ok = false;
    }
  }
  if (!ok) cout << "s UNSATISFIABLE" << endl;
  else {
    cout << "s SATISFIABLE" << endl;
    vector<bool> which(n);
    for (int i=0;i<n;i++) {
      if (lis[i] > lis[i+n]) {
        which[i] = true;
      }
      else which[i] = false;
    }
    cout << 'v';
    for (int i=0;i<n;i++) {
      cout << ' ';
      if (which[i]) cout << i+1;
      else cout << -(i+1);
    }
    cout << " 0" << endl;
  }
}
