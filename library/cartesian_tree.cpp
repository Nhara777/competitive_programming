template<typename T>
pair<vector<vector<int>>,vector<int>> cartesian_tree(vector<T> &a) {
  int n = a.size();
  vector<int> par(n,-1);
  stack<int> st;  for (int i=0;i<n;i++) {
    int prev = -1;
    while (!st.empty() && a[i] < a[st.top()]) {
      prev = st.top();
      st.pop();
    }
    if (prev != -1) par[prev] = i;
    if (!st.empty()) par[i] = st.top();
    st.push(i);
  }
  vector<vector<int>> g(n);
  for (int i=0;i<n;i++) {
    if (par[i] != -1) {
      g[par[i]].emplace_back(i);
    }
  }
  return make_pair(g,par);
}