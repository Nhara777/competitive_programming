#define MOD1 998244353
#define MOD2 469762049

long long pow(long long n, long long k, long long mod) {
  long long num = n;
  long long ans = 1;
  long long left = k;
  while (left != 0) {
    if (left%2 == 1) ans = ans*num%mod;
    left /= 2;
    num = num*num%mod;
  }
  return ans;
}

long long mod_inv(long long n, long long mod) {
  return pow(n, mod-2, mod);
}

vector<long long> ntt(vector<long long> f, long long n, long long mod) {
  if (n == 1) return f;
  else
  {
    vector<long long> f0(n/2);
    vector<long long> f1(n/2);
    for (int i=0;i<n/2;i++) {
      f0[i] = f[i*2];
      f1[i] = f[i*2+1];
    }
    f0 = ntt(f0, n/2, mod);
    f1 = ntt(f1, n/2, mod);
    long long zeta = pow((long long)3, (mod-1)/n, mod); // prepare number
    long long pow_zeta = 1;
    for (int i=0;i<n;i++) {
      f[i] = (f0[i%(n/2)]+pow_zeta*f1[i%(n/2)])%mod;
      pow_zeta = pow_zeta*zeta%mod;
    }
    return f;
  }
}

vector<long long> inv_ntt(vector<long long> f, long long n, long long mod, long long nf) {
  if (n == 1) return f;
  else
  {
    vector<long long> f0(n/2);
    vector<long long> f1(n/2);
    for (int i=0;i<n/2;i++) {
      f0[i] = f[i*2];
      f1[i] = f[i*2+1];
    }
    f0 = inv_ntt(f0, n/2, mod, nf);
    f1 = inv_ntt(f1, n/2, mod, nf);
    long long zeta = mod_inv(pow((long long)3, (mod-1)/n, mod), mod);
    long long pow_zeta = 1;
    for (int i=0;i<n;i++) {
      f[i] = (f0[i%(n/2)]+pow_zeta*f1[i%(n/2)])%mod;
      pow_zeta = pow_zeta*zeta%mod;
    }
    if(n == nf) {
      for (int i=0;i<n;i++) f[i] = f[i]*mod_inv(n, mod)%mod;
    }
    return f;
  }
}

vector<long long> NTT(vector<long long> a, vector<long long> b) // a,b: count array
{
  int n = a.size();
  vector<int> ka(n+1, 0);
  vector<int> kb(n+1, 0);
  for (int i=0;i<n;i++) {
    ka[i+1] = a[i];
    kb[i+1] = b[i]; 
  }
  long long n2 = 1;
  while (n2 <= n*2) n2 *= 2;
  vector<long long> g(n2, 0);
  vector<long long> h(n2, 0);
  for (int i=0;i<=n;i++) {
    g[i] = ka[i];
    h[i] = kb[i];
  }
  vector<long long> g1(n2, 0);
  vector<long long> h1(n2, 0);
  vector<long long> g2(n2, 0);
  vector<long long> h2(n2, 0);
  g1 = ntt(g, n2, MOD1);
  h1 = ntt(h, n2, MOD1);
  g2 = ntt(g, n2, MOD2);
  h2 = ntt(h, n2, MOD2);
  vector<long long> gh1(n2);
  for (int i=0;i<n2;i++) gh1[i] = g1[i]*h1[i]%MOD1;
  vector<long long> gh2(n2);
  for (int i=0;i<n2;i++) gh2[i] = g2[i]*h2[i]%MOD2;
  vector<long long> ans1(n2, 0);
  ans1 = inv_ntt(gh1, n2, MOD1, n2);
  vector<long long> ans2(n2, 0);
  ans2 = inv_ntt(gh2, n2, MOD2, n2);
  vector<long long> ans(n*2+1, 0);
  for (int i=0;i<=n*2;i++) {
    long long k = (ans2[i]-ans1[i])+(long long)MOD1*MOD2;
    k %= MOD2;
    k = k*mod_inv(MOD1%MOD2, MOD2)%MOD2;
    ans[i] = (k*MOD1+ans1[i])%((long long)MOD1*MOD2);
  }
  return ans;
}