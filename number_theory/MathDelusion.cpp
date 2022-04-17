// https://codeforces.com/gym/345883/problem/A
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;

const int N = 1e6;
const int MOD = 1e9 + 7;

vector<int> mu, phi, primes;
vector<bool> is_prime;

int Add(int a, int b) { a += b; if (a >= MOD) a -= MOD; return a; }

int Sub(int a, int b) { a -= b; if (a < 0) a += MOD; return a; }

int Mul(Long a, Long b) { return ((a * b) % MOD); }

void Sieve(int n) {
  is_prime = vector<bool>(n + 1, true);
  mu = vector<int>(n + 1, 1);
  phi = vector<int>(n + 1, 1);
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      mu[i] = -1;
      phi[i] = i - 1;
    }
    for (int j = 0; j < (int) primes.size() && i * primes[j] <= n; j++) {
      is_prime[i * primes[j]] = false;
      if (i % primes[j] == 0) {
        phi[i * primes[j]] = phi[i] * primes[j];
        mu[i * primes[j]] = 0;
        break;
      } else {
        phi[i * primes[j]] = phi[i] * phi[primes[j]];
        mu[i * primes[j]] = mu[i] * mu[primes[j]];
      }
    }
  }
}

vector<int> cnt, sum;

void Update(int& ans, int n, int d) {
  int mul = sum[n];
  mul = Mul(mul, n);
  mul = Mul(mul, d);
  if (mu[d] < 0) {
    ans = Sub(ans, mul);
  } else if (mu[d] > 0) {
    ans = Add(ans, mul);
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  Sieve(n);
  cnt = vector<int>(n + 1, 0);
  for (int i = 1; i <= n; i++) cnt[phi[i]]++;
  sum = vector<int>(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    int j = 1;
    while (i * j <= n) {
      sum[i] = Add(sum[i], Mul(j, cnt[i * j]));
      j++;
    }
    sum[i] = Mul(sum[i], sum[i]);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int d = 1; d * d <= i; d++) {
      if (i % d != 0) continue;
      int rem = i / d;
      Update(ans, i, d);
      if (d != rem) Update(ans, i, rem);
    }
  }
  cout << ans << '\n';
  return 0;
}
