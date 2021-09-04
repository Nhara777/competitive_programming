class UnionFind {
  int n;
  vector<int> par;
  vector<int> ranks;
  vector<int> sizes;

public:
  UnionFind(int m) {
    n = m;
    for (int i=0;i<n;i++) {
      par.emplace_back(i);
      ranks.emplace_back(0);
      sizes.emplace_back(1);
    }
  }

  int find(int x) {
    if (par[x] == x) return x;
    else return par[x] = find(par[x]); 
  }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (ranks[x] < ranks[y]) {
      par[x] = y;
      sizes[y] += sizes[x];
    }
    else {
      par[y] = x;
      sizes[x] += sizes[y];
      if (ranks[x] == ranks[y]) ranks[x]++;
    }
  }

  int sizing(int x) {
    return sizes[find(x)];
  }

  bool same(int x,int y) {
    return find(x) == find(y);
  }
};
