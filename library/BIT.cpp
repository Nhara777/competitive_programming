class BIT {
  vector<int> dat;

public:
  int n;
  BIT(int m) {
    n = m;
    for (int i=0;i<=n;i++) {
      dat.emplace_back(0);
    }
  }

  void add(int k, int a) { 
    // k: 1-indexed
    while (k <= n) {
      dat[k] += a;
      k += (k & -k);
    }
  }

  int sum(int k) {
    // k: 1-indexed
    int s = 0;
    while (k > 0) {
      s += dat[k];
      k -= (k & -k);
    }
    return s;
  }
};