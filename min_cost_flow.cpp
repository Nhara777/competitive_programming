class MinCostFlow {
  using T = tuple<int,int,int,int>; //to,cap,cost,rev
  using P = pair<int,int>;
  int INF = (int)1e+9;
  vector<vector<T>> g;
  vector<int> h;
  vector<int> dist;
  vector<int> prevv;
  vector<int> preve;

public:
  int n;
  MinCostFlow(int m) {
    n = m;
    for (int i=0;i<n;i++) {
      g.emplace_back();
      h.emplace_back();
      dist.emplace_back();
      prevv.emplace_back();
      preve.emplace_back();
    }
  }

  void add_edge(int from, int to, int cap, int cost) {
    g[from].emplace_back(make_tuple(to,cap,cost,g[to].size()));
    g[to].emplace_back(make_tuple(from,0,-cost,g[from].size()-1));
  }

  int flow(int s, int t, int f) {
    int res = 0;
    for (int i=0;i<n;i++) h[i] = 0;
    while (f > 0) {
      priority_queue<P,vector<P>,greater<P>> pq;
      for (int i=0;i<n;i++) dist[i] = INF;
      dist[s] = 0;
      pq.push(P(0,s));
      while (!pq.empty()) {
        P p = pq.top();
        pq.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (int i=0;i<g[v].size();i++) {
          T nowt = g[v][i];
          int to = get<0>(nowt);
          int cap = get<1>(nowt);
          int cost = get<2>(nowt);
          if (cap > 0 && dist[to] > dist[v]+cost+h[v]-h[to]) {
            dist[to] = dist[v]+cost+h[v]-h[to];
            prevv[to] = v;
            preve[to] = i;
            pq.push(P(dist[to],to));
          }
        }
      }
      if (dist[t] == INF) {
        return -1;
      }
      for (int v=0;v<n;v++) h[v] += dist[v];
      int d = f;
      for (int v=t;v!=s;v=prevv[v]) {
        d = min(d, get<1>(g[prevv[v]][preve[v]]));
      }
      f -= d;
      res += d*h[t];
      for (int v=t;v!=s;v=prevv[v]) {
        get<1>(g[prevv[v]][preve[v]]) -= d;
        get<1>(g[v][get<3>(g[prevv[v]][preve[v]])]) += d;
      }
    }
    return res;
  }
};

// complexity: O(FElogV) or O(FV^2)