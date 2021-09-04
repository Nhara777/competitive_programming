// return inverse of k! mod MOD (0<=k<=t)
vector<long long> fact_inv(int t, long long MOD) {
  vector<long long> inv(t+1,1);
  vector<long long> ret(t+1,1);
  for (int i=2;i<=t;i++) inv[i] = (MOD-inv[MOD%i]*(MOD/i)%MOD)%MOD;
  for (int i=2;i<=t;i++) ret[i] = rfact[i-1]*inv[i]%MOD;
  return ret;
}