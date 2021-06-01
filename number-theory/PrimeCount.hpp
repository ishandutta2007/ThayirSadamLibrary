#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Source: misterkeemu
// Tested on: Yosupo Counting Primes
// Complexity: ???
// Returns number of primes <= N
// Works with some black magic, probably optimized Meissel-Lehmer. Must check.
// About 10x faster than any other Meissel-Lehmer implementation.
ll pi(const ll N) {
  if(N <= 1) return 0;
  if(N == 2) return 1;
  const int v = sqrtl(N);
  int s = (v + 1) / 2;
  vector<int> smalls(s);
  vector<int> roughs(s);
  vector<long long> larges(s);
  for(int i = 1; i < s; ++i) smalls[i] = i;
  for(int i = 0; i < s; ++i) roughs[i] = 2 * i + 1;
  for(int i = 0; i < s; ++i) larges[i] = (N / (2 * i + 1) - 1) / 2;
  vector<bool> skip(v+1);
  const auto divide = [] (ll n, ll d) -> int{ return double(n) / d; };
  const auto half = [] (int n) -> int{ return (n - 1) >> 1; };
  int pc = 0;
  for(int p = 3; p <= v; p += 2) if(!skip[p]){
    int q = p * p;
    if((ll)(q) * q > N) break;
    skip[p] = true;
    for(int i = q; i <= v; i += 2 * p) skip[i] = true;
    int ns = 0;
    for(int k = 0; k < s; ++k){
      int i = roughs[k];
      if(skip[i]) continue;
      ll d = (ll)(i) * p;
      larges[ns] = larges[k] - (d <= v ? larges[smalls[d >> 1] - pc] : smalls[half(divide(N, d))]) + pc;
      roughs[ns++] = i;
    }
    s = ns;
    for(int i = half(v), j = ((v / p) - 1) | 1; j >= p; j -= 2){
      int c = smalls[j >> 1] - pc;
      for(int e = (j * p) >> 1; i >= e; --i) smalls[i] -= c;
    }
    ++pc;
  }
  larges[0] += (ll)(s + 2 * (pc - 1)) * (s - 1) / 2;
  for(int k = 1; k < s; ++k) larges[0] -= larges[k];
  for(int l = 1; l < s; ++l){
    int q = roughs[l];
    ll M = N / q;
    int e = smalls[half(M / q)] - pc;
    if(e < l + 1) break;
    ll t = 0;
    for(int k = l + 1; k <= e; ++k) t += smalls[half(divide(M, roughs[k]))];
    larges[0] += t - (ll)(e - l) * (pc + l - 1);
  }
  return larges[0] + 1;
}
