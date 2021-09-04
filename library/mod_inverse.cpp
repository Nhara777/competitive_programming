long long mod_inv(long long n) {
  long long left = MOD-2; //define MOD
  long long ks = n;
  long long ans = 1;
  while (left != 0) {
    if (left%2 == 1) ans = ans*ks%MOD;
    left /= 2;
    ks = ks*ks%MOD;
  }
  return ans;
}