class Dinic {
  using T = tuple<int,int,int>; //to,cap,rev
  vector<vector<T>> g;
  vector<int> level;
  vector<int> iter;

public:
  int n;
  Dinic(int m) {
    n = m;
    for (int i=0;i<n;i++) {
      g.emplace_back();
      level.emplace_back(-1);
      iter.emplace_back(0);
    }
  }

  void add_edge(int from, int to, int cap) {
    g[from].emplace_back(make_tuple(to,cap,g[to].size()));
    g[to].emplace_back(make_tuple(from,0,g[from].size()-1));
  }

  void bfs(int s) {
    for (int i=0;i<n;i++) {
      level[i] = -1;
    }
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int now = q.front();
      q.pop();
      for (int i=0;i<g[now].size();i++) {
        T nowt = g[now][i];
        int to = get<0>(nowt);
        int cap = get<1>(nowt);
        int rev = get<2>(nowt);
        if (cap > 0 && level[to] < 0) {
          level[to] = level[now]+1;
          q.push(to);
        }
      }
    }
  }

  int dfs(int now, int t, int f) {
    if (now == t) return f;
    for (int i=iter[now];i<g[now].size();i++) {
      iter[now] = i;
      T nowt = g[now][i];
      int to = get<0>(nowt);
      int cap = get<1>(nowt);
      int rev = get<2>(nowt);
      if (cap > 0 && level[now] < level[to]) {
        int d = dfs(to, t, min(f,cap));
        if (d > 0) {
          get<1>(g[now][i]) -= d;
          get<1>(g[to][rev]) += d;
          return d;
        }
      }
    }
    return 0;
  }

  int max_flow(int s, int t) {
    int flow = 0;
    while (true) {
      bfs(s);
      if (level[t] < 0) return flow;
      for (int i=0;i<n;i++) iter[i] = 0;
      int f;
      while ((f = dfs(s,t,INT_MAX)) > 0) {
        flow += f;
      }
    }
  }
};

/*
Usage:
1.init by n;
2.add edge (from,to,cap) (make rev automatically)
3.use "max_flow(s,t)"
*/
