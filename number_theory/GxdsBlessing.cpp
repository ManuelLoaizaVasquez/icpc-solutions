// https://codeforces.com/gym/345883/problem/C
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1e7;

vector<Long> f, primes;
vector<bool> is_prime;

void Sieve(int n) {
  is_prime = vector<bool>(n + 1, true);
  f = vector<Long>(n + 1, 1);
  f[1] = 1;
  for (Long i = 2; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      f[i] = i - 1;  // TODO
    }
    for (Long j = 0; j < (int) primes.size() && i * primes[j] <= n; j++) {
      is_prime[i * primes[j]] = false;
      if (i % primes[j] == 0) {
        f[i * primes[j]] = f[i] * primes[j];  // TODO
        break;
      } else {
        f[i * primes[j]] = f[i] * f[primes[j]];  // TODO
      }
    }
  }
}

void Solve(void) {
  Long n;
  cin >> n;
  Long ans = 0;
  for (Long d = 1; d * d <= n; d++) {
    if (n % d != 0) continue;
    Long rem = n / d;
    ans += f[d] * f[d];
    if (d != rem) ans += f[rem] * f[rem];
  }
  cout << ans << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(N);
  int tt;
  cin >> tt;
  while (tt--) Solve();
  return 0;
}