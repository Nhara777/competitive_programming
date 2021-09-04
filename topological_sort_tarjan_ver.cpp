vector<int> topological_sort(vector<vector<int>> e) {
  int n = e.size();
  vector<bool> visited(n,false);
  vector<int> ans(0);
  stack<int> st;
  for (int i=0;i<n;i++) {
    if (!visited[i]) {
      st.push(i);
      visited[i] = true;
    }
    while (!st.empty()) {
      int now = st.top();
      bool found = false;
      for (int j=0;j<e[now].size();j++) {
        if (!visited[e[now][j]]) {
          st.push(e[now][j]);
          visited[e[now][j]] = true;
          found = true;
          break;
        }
      }
      if (found) continue;
      else {
        ans.emplace_back(now);
        st.pop();
      }
    }
  }
  reverse(ans.begin(), ans.end());
  return ans;
}