vector<int> linear_prime(int n) { // (2~N) 
  vector<int> lp(n+1);
  vector<int> pr(0);
  for (int i=2;i<=n;i++) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.emplace_back(i);
    }
    for(int j=0;j<pr.size() && pr[j] <= lp[i] && i*pr[j] <= n;j++) {
      lp[i*pr[j]] = pr[j];
    }
  }
  return lp; //(minimum prime factors) or pr(primes)
}