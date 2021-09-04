vector<pair<char,int>> runLength(string s) {
  vector<pair<char,int>> p(0);
  char now = s[0];
  int len = 1;
  for (int i=1;i<s.size();i++) {
    if (s[i] == now) len++;
    else {
      p.emplace_back(make_pair(now,len));
      now = s[i];
      len = 1;
    }
  }
  p.emplace_back(make_pair(now,len));
  return p;
}