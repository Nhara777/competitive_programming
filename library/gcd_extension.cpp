long long extgcd(long long a, long long b, long long &x, long long &y) { // ax+by=gcd(a,b), x,y are all OK.
  long long d = a;
  if (b != 0) {
    d = extgcd(b, a%b, y, x);
    y -= (a/b)*x;
  }
  else {
    x = 1;
    y = 0;
  }
  return d;
} // x,y are answers!