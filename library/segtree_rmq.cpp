class SegTree {
  vector<int> dat;

public:
  int n2 = 1;
  SegTree(int m) {
    while (n2 < m) n2 *= 2;
    for (int i=0;i<n2*2-1;i++) {
      dat.emplace_back(INT_MAX);
    }
  }

  // update dat[k] to a
  void update(int k, int a) {
    k += n2-1;
    dat[k] = a;
    while (k > 0) {
      k = (k-1)/2;
      dat[k] = min(dat[k*2+1],dat[k*2+2]);
    }
  }

  int query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return INT_MAX;
    if (a <= l && r <= b) return dat[k];
    else {
      int vl = query(a,b,k*2+1,l,(l+r)/2);
      int vr = query(a,b,k*2+2,(l+r)/2,r);
      return min(vl,vr);
    }
  }

  // min of [a,b)
  int get(int a, int b) {
    return query(a,b,0,0,n2);
  }
};