vector<int> kmp_table(string w) {
  int n = w.size();
  vector<int> table(n+1);
  int j = -1;
  table[0] = -1;
  for (int i=0;i<n;i++) {
    while (j >= 0 && w[i] != w[j]) j = table[j];
    j++;
    table[i+1] = j;
  }
  return table;
}

vector<int> kmp_search(string s, string w) {
  vector<int> ret;
  vector<int> table = kmp_table(w);
  int m = 0;
  int i = 0;
  while (m+i < s.size()) {
    if (w[i] == s[m+i]) {
      i++;
      if (i == w.size()) {
        ret.emplace_back(m);
        m = m+i-table[i];
        i = table[i];
      }
    }
    else {
      m = m+i-table[i];
      if (i > 0) {
        i = table[i];
      }
    }
  }
  return ret;
}