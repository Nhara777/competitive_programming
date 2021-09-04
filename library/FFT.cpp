#define PI acos(-1)

vector<complex<double>> dft(vector<complex<double>> f, int n) {
  if (n == 1) return f; // value of f(1) = c_i
  else {
    vector<complex<double>> f0(n/2);
    vector<complex<double>> f1(n/2);
    for (int i=0;i<n/2;i++) {
      f0[i] = f[i*2];
      f1[i] = f[i*2+1];
    }
    f0 = dft(f0, n/2);
    f1 = dft(f1, n/2);
    complex<double> zeta = complex<double>(cos(2*PI/n), sin(2*PI/n));
    complex<double> pow_zeta = complex<double>(1.0, 0.0);
    for (int i=0;i<n;i++) {
      f[i] = (f0[i%(n/2)]+pow_zeta*f1[i%(n/2)]);
      pow_zeta *= zeta;
    }
    return f;
  }
}

vector<complex<double>> inv_dft(vector<complex<double>> f, int n, int nf) {
  if (n==1) return f;
  else {
    vector<complex<double>> f0(n/2);
    vector<complex<double>> f1(n/2);
    for (int i=0;i<n/2;i++) {
      f0[i] = f[i*2];
      f1[i] = f[i*2+1];
    }
    f0 = inv_dft(f0, n/2, nf);
    f1 = inv_dft(f1, n/2, nf);
    complex<double> zeta = complex<double>(cos(-2*PI/n), sin(-2*PI/n));
    complex<double> pow_zeta = complex<double>(1.0, 0.0);
    for (int i=0;i<n;i++) {
      f[i] = (f0[i%(n/2)]+pow_zeta*f1[i%(n/2)]);
      pow_zeta *= zeta;
    }
    if (n == nf) {
      for (int i=0;i<n;i++) f[i] /= n;
    }
    return f;
  }
}

//a is like {1:0,2:3,3:4...}, b is also.
vector<int> fft(vector<int> a, vector<int> b) { //a,b: count array
  int n = a.size(); // |a|=|b|=|ans|/2
  vector<int> ka(n+1, 0);
  vector<int> kb(n+1, 0);
  for (int i=0;i<n;i++) {
    ka[i+1] = a[i];
    kb[i+1] = b[i]; 
  }
  int n2 = 1;
  while (n2 <= n*2) n2 *= 2;
  vector<complex<double>> g(n2, (0.0, 0.0));
  vector<complex<double>> h(n2, (0.0, 0.0));
  for (int i=0;i<=n;i++) g[i] = complex<double>(ka[i], 0);
  g = dft(g, n2);
  for (int i=0;i<=n;i++) h[i] = complex<double>(kb[i], 0);
  h = dft(h, n2);
  vector<complex<double>> gh(n2, (0,0));
  for (int i=0;i<n2;i++) gh[i] = g[i]*h[i];
  vector<complex<double>> kans(n2, 0);
  kans = inv_dft(gh, n2, n2);
  vector<int> ans(n*2+1, 0);
  for (int i=1;i<=n*2;i++) ans[i] = (int)round(kans[i].real())+0;
  return ans;
}