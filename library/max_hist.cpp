long long max_hist(vector<long long> h) {

  int n = h.size();
  h.emplace_back(0);
  long long ans = 0;
  stack<pair<long long,int>> st;
  for (int i=0;i<=n;i++) {
    if (st.empty()) st.push(make_pair(h[i],i));
    else {
      pair<long long,int> p = st.top();
      long long val = p.first;
      int ind = p.second;
      if (val < h[i]) st.push(make_pair(h[i],i));
      else if (val > h[i]) {
        int newi = i;
        while (!st.empty()) {
          p = st.top();
          val = p.first;
          ind = p.second;
          if (val < h[i]) break;
          ans = max(ans,val*(i-ind));
          newi = ind;
          st.pop();
        }
        st.push(make_pair(h[i],newi));
      }
    }
  }
  return ans;
}