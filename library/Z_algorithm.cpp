vector<int> z(string s) {
  int n = s.size();
  vector<int> a(n);
  a[0] = n;
  int i = 1, j = 0;
  while (i < n)
  {
    while (i+j < s.size() && s[j] == s[i+j]) j++;
    a[i] = j;
    if (j == 0) {
      i++;
      continue;
    }
    int k = 1;
    while (i+k < s.size() && k+a[k] < j) {
      a[i+k] = a[k];
      k++;
    }
    i += k;
    j -= k;
  }
  return a;
}