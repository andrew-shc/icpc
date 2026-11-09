#include <bits/stdc++.h>
#include <climits>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

// prefix sum
#define PS(v_ps, v_in)                                                         \
  vll v_ps(v_in.size() + 1, 0);                                                \
  for (ll i = 1; i < v_in.size() + 1; i++) {                                   \
    v_ps[i] = v_ps[i - 1] + v_in[i - 1];                                       \
  }

// suffix sum
#define SS(v_ss, v_in)                                                         \
  vll v_ss(v_in.size() + 1, 0);                                                \
  for (ll i = n - 1; i >= 0; i--) {                                            \
    v_ss[i] = v_ss[i + 1] + v_in[i];                                           \
  }

#define PB push_back
#define PF push_front
#define ST(v) std::sort(v.begin(), v.end())

#define II(i, n) for (ll i = 0; i < n; i++)

#define DD(i, n) for (ll i = n - 1; i >= 0; i--)

#define OIT(a)                                                                 \
  {                                                                            \
    for (auto &el : a) {                                                       \
      std::cout << el << " ";                                                  \
    }                                                                          \
    std::cout << std::endl;                                                    \
  }

template <typename... Args> void cout_vars(Args... args) {
  ((std::cout << std::fixed << std::setprecision(10) << args << " "), ...)
      << std::endl;
}
#define O(...) cout_vars(__VA_ARGS__)
#define OHYES std::cout << "YES" << std::endl
#define OHNO std::cout << "NO" << std::endl

#define IS(s)                                                                  \
  string s;                                                                    \
  cin >> s;

#define IV(a, n)                                                               \
  vll a;                                                                       \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai;                                                                     \
    std::cin >> ai;                                                            \
    a.push_back(ai);                                                           \
  }

#define IVP(ap, n)                                                             \
  vpll ap;                                                                     \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai, bi;                                                                 \
    std::cin >> ai >> bi;                                                      \
    ap.push_back({ai, bi});                                                    \
  }

template <typename... Args> void read_vars(Args &...args) {
  (std::cin >> ... >> args);
}
#define I(...)                                                                 \
  ll __VA_ARGS__;                                                              \
  read_vars(__VA_ARGS__)

#ifdef DEBUG
#include "debug.h"
#else
#define DBGLN(...)
#define DBG(...)
#define DBG_ITER(arr)
#define DBG_MAP(map_var)
#define DBLOCK if (false)
#endif

using namespace std;

//
//
//
//
//
//
//
//
//
//
// END MACROS
//
//
//
//
//
//
//
//
//
//

void solve(ll T);

int main() {
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  // comment out or set to true when working with interactive problems
  //
  //
  ios_base::sync_with_stdio(false);
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //

  cin.tie(NULL);
  cout.tie(NULL);

  ll T = 1;

  // comment out when working w/o testcases
  cin >> T;

  ll t = T;
  while (t--) {
    solve(T - t);
  }

  return 0;
}

// start:
//   end:

//
//
//
//
//
//
//
//
//
//
// NOTES
//
//
//
//
//
//
//
//
//
// GCD := all the common-shared/minimum prime factors
// (LCM := the maximum powers for each unique prime factors)
//
// A = G*p >= l
// B = G*q <= r
//
// for A to be miminimized and |A-B| => |B-A| to be maximized
//      we can just minimize A (within l-bound)
//
// restating the problem:
//
//  l <= A = G*p <= G*q = B <= r
//
//
//  l <= G*p
//  (l/G) <= ceil(l/G) = p
//
//  A can be found with G*ceil(l/G)
//
//  B can be found with G*floor(r/G)
//      given, q = floor(r/G) <= r/G
//
//  if A>B => failed..
//
//
//  ADDITIONAL REQUIREMENT:
//      G = the only integer's where shared prime-factors are allowed
//
//      gcd(p,q) = 1 required
//
//      p and q must be coprime of each other
//
//      bezout's identity?
//
//      px+qy = gcd(p,q)
//
//      Euclidean algorithm??
//
//      we want to find the largest p,q within l/r-bounds where the gcd(p,q)==1
//      (for any integer x,y)
//
//      px = 1-qy
//
// === STUCK: how to find gcd(p.q)==1 where p is the smallest while q is the
// largest ===
//
//
// !!! suppose G=1
//      then it's literally A=l, B=r
//      ~~~~^^
//      nope, we got to make suure there's no shared common prime factors
//
//!!! notice, regardless the method/pattern/how they're finding the perfect
//! pair, they're working in multiples of G (makes sense) but also importantly
//! they do seem to be searching it in some sort of searching manner (no
//! formulaes)
//
//! ~~if we naively assume we're searching naively
//! if we brute-force the search in (l+pG,r-qG)
//!     with increasing p,q
//!     makes sense! we try to go from the best (maximizes |A-B| or |B-A| w/ A
//!     minimized) and ensure the search space is restricted to multiples of G
//!     to simplify and optimize the search to remove obviously wrong A,B
//!     so we go from the best <-----> to the worst <->
//
//!! complexity O(K^2logA) logA is the time to compute GCD by euclidean algo
//!!!                      K^2 is the search space
//
// originally, the large input constraints makes one fear even a linear
// algorithm or even brute-force search, however apparently K^2 is not the whole
// answer and there's more to it (better complexity by prime gap etc.)
//
//! because of this brute-force search is basically just searching for the prime
//! number (taking the G-factor out), we can just use the prime gap theorem to
//! conclude that ON AVERAGE ln(A) gap between two primes
//!
//! because if either p or q is prime, then gcd(p,q) will always be 1
//
//! but the editorial further shows that (supposedly we bound up to 30x30 search
//! grid)
//
//! a pair with gcd=2 => 30x30/4 => 900/4=225
//! a pair with gcd=3 => every 3x3 grid (or 9) (or 900/9)
//! and even till we reach for a some gcd=37
//
// regardless, this is some heuristics that also appeared in Div2A before
//
//
// ln 10^18 > 18
// (actually about 41 so 50 is fine)
//
// NOTICE: despite brute-forcing, the additiona/subtraction by factors or
// multiples can break and look for suitable primes for some problems need
//
//
// per chatgpt (and looking at the editorial's code):
//      work in multiples of G (or else one may encounter integer overflow even
//      with unsigned long longs)

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  // I(l, r, G);
  ull l, r, G;
  cin >> l >> r >> G;

  // ull A = G * ((l + G - 1) / G);
  // ull B = G * (r / G);
  // ll A = (l + G - 1) / G;
  // ll B = r / G;
  ull A = (l + G - 1) / G;
  ull B = r / G;

  // bool good = false;
  II(K, 50) {
    II(i, K) {
      // ull A_prime = A + i * G;
      ull A_prime = A + i;
      // if (B <= (K - 1 - i) * G) {
      //   continue;
      // }
      if (B <= K - 1 - i) {
        continue;
      }
      // ull B_prime = B - (K - 1 - i) * G;
      ull B_prime = B - (K - 1 - i);

      // edge case, when A=G=B, this does not work (not actually should work and
      // should be the final case to check / no not the final case to check)
      // if (A_prime <= r && B_prime >= l && gcd(A_prime / G, B_prime / G) == 1)
      // {
      if (gcd(A_prime, B_prime) == 1) {
        // if (!(A_prime * G <= r && B_prime >= l)) {
        // if (!(A_prime * G <= r && B_prime * G >= l)) {
        if (A_prime > B || B_prime < A) {
          // OOB
          // can result in an overall answer of -1 -1 if bounds are too tight
          continue;
        }

        // if (A_prime <= r && B_prime >= l && gcd(A_prime / G, B_prime / G)
        // == 1 &&
        //     A_prime != B_prime) {
        A = A_prime;
        B = B_prime;
        O(A * G, B * G);
        return;
        // good = true;
        // break;
      }
    }
    // if (good)
    //   break;
  }

  // if (A > r || B < l || gcd(A / G, B / G) != 1) {
  O(-1, -1);
  // } else {
  // O(A, B);
  // }

  // ll A = G * ((l + G - 1) / G);
  // ll B = G * (r / G);
  //
  // if (A > B) {
  //   O(-1, -1);
  // } else {
  //   O(A, B);
  // };
}
