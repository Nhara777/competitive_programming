// paste extgcd first.
// return x = r (mod m) for x = b1 (mod m1) and x = b2 (mod m2).
// return (0,-1) if the answer doesn't exist.

pair<long long,long long> CRT(long long b1, long long m1, long long b2, long long m2) {
  long long p,q;
  long long d = extgcd(m1,m2,p,q);
  if ((b2-b1)%d != 0) return make_pair(0,-1);
  long long m = m1*(m2/d); // lcm(m1,m2)
  long long tmp = (b2-b1)/d*p%(m2/d);
  long long a = b1+m1*tmp;
  long long r = (a%m+m)%m;
  return make_pair(r,m);
}