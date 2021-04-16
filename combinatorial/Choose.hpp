#include <bits/stdc++.h>
using namespace std;

#include "../number-theory/ModInt.hpp"

vector<mod_int> fact, invfact, inv;

void prepare_factorials(int N) {
  assert(N >= 2);
  fact.resize(N+1);
  invfact.resize(N+1);
  inv.resize(N+1);
  inv[1] = invfact[1] = invfact[0] = fact[0] = fact[1] = 1;
  for (int i = 2; i <= N; i++) {
    fact[i] = fact[i-1]*i;
    inv[i] = inv[MOD%i]*(MOD-MOD/i);
    invfact[i] = invfact[i-1]*inv[i];
  }
}

mod_int choose(int n, int k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fact[n]*(invfact[k]*invfact[n-k]);
}