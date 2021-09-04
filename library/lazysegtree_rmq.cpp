class LazySegTree {
  vector<int> dat,lazy;
  vector<bool> change;

public:
  int n2 = 1;
  LazySegTree(int m) {
    while (n2 < m) n2 *= 2;
    for (int i=0;i<n2*2-1;i++) {
      dat.emplace_back(INT_MAX);
      lazy.emplace_back(0);
      change.emplace_back(false);
    }
  }

  void eval(int k, int l, int r) {
    if (change[k]) {
      dat[k] = lazy[k];
      if (r-l > 1) {
        lazy[k*2+1] = lazy[k];
        change[k*2+1] = true;
        lazy[k*2+2] = lazy[k];
        change[k*2+2] = true;
      }
      change[k] = false;
    }
  }

  void update(int a, int b, int v, int k, int l, int r) {
    eval(k,l,r);
    if (b <= l || r <= a) return;
    if (a <= l && r <= b) {
      change[k] = true;
      lazy[k] = v;
      eval(k,l,r);
    }
    else {
      update(a,b,v,k*2+1,l,(l+r)/2);
      update(a,b,v,k*2+2,(l+r)/2,r);
      dat[k] = min(dat[k*2+1],dat[k*2+2]);
    }
  }

  // update values of [a,b)
  void put(int a, int b, int v) {
    update(a,b,v,0,0,n2);
  }

  int query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return INT_MAX;
    eval(k,l,r);
    if (a <= l && r <= b) return dat[k];
    int vl = query(a,b,k*2+1,l,(l+r)/2);
    int vr = query(a,b,k*2+2,(l+r)/2,r);
    return min(vl,vr);
  }

  // min of [a,b)
  int get(int a, int b) {
    return query(a,b,0,0,n2);
  }

};