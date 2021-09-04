vector<int> topological_sort(vector<vector<int>> e) {
  int n = e.size();
  vector<int> ans(0);
  vector<int> ins(n,0);
  for (int i=0;i<n;i++) {
    for (int j=0;j<e[i].size();j++) {
      ins[e[i][j]]++;
    }
  }
  queue<int> s;
  for (int i=0;i<n;i++) {
    if (ins[i] == 0) s.push(i);
  }
  while (!s.empty()) {
    int now = s.front();
    s.pop();
    ans.emplace_back(now);
    for (int i=0;i<e[now].size();i++) {
      ins[e[now][i]]--;
      if (ins[e[now][i]] == 0) {
        s.push(e[now][i]);
      }
    }
  }
  return ans;
}
