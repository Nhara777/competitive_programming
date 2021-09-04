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
