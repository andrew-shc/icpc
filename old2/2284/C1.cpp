#include <algorithm>
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
//
// to make an array not digusting
//
// ensure for ALL indices i,j
//      gcd(bi,bj) >= min(bi,bj)
//
//      ==> gcd(bi,bj) == min(bi,bj)
//      ==> bi divides bj OR bj divides bi
//      ==> every elements must be mutually divisible with itself and others
//          (or multiples of others)
//
//          MULTIPLES OF itself OR DIVISIBLE BY the other element
//
//      ==> one example: make all elements equal to z s.t. gcd(ai,z-ai)=1 for
//                       all i
//
// restrictions:
//  we can only increase the elements with only its coprime
//      INCREASE/ADD only
//  ensure the sums of such increases are not greater than the sum of the
//  original elements
//
//
//  the smallest element sets the spacing for the rest
//
//
//~~~~~~~~~~~~~~~~~~~~~~^^^ gcd can be 1
//
//
//  since gcd can either be 1 or min(bi,bj)
//      ==> there are mutually exclusive groups of mutually divisible/multiples
//      of each other (and between these groups, there are absolute no shared
//      prime factors)
//
//
// wait just make all numbers even???
//   +1 => gcd(ai,1) always 1
// ~~~~
//
// checked on the CURRENT value of a[i]
//
//
//
// think in prime factors
//
//
// given a,
//
// ensure all the prime factors of b are either different across groups or
// multiples/divisibles on b itself within a group
//
// notice: if a pair is not multiples/divisibles and yet does not have an
// entirely different set of prime factors => how do we make that larger integer
// have an entirely different set or become multiples/divissibles?
//  => if it has some shared factors with the other elements in the pair, then
//  it requires the elements to take at least 2 operations because the increment
//  must be a coprime of itself but to reach multiples of the smaller integer
//  the (DIRECT) incremenet woudl be NOT a coprime
//
//  => greedily increment TO the next largest unqiue prime?
//     x+y = next prime call p => gcd(x,y)=1??? bezouts ident??
//
//     for gcd(a,b)=1
//          => ax+by = 1 (there exists some integers x,y)
//
//
//     suppose a+q=p (q is the increment)
//
//
//     clearly, prime => coprime to all (except p and 0 obv.)
//          gcd(a,p)=1, gcd(q,p)=1
//
//          so just find the next prime?
//
//          gcd(a,q)=?
//
//          among a,q,p
//
//          can we find gcd(a,q)>1?
//
//          suppose gcd(a,q)>1
//              this is just the same reasoning as before
//              it would suggest p would have a gcd>1 on one of them or both?
//              (prob both)
//
//              <=> ??
//
//              so just find the coprime
//
//              in other words,
//                  finding an x s.t. gcd(ai,x)=1
//                  ==> ai+x will NOT be disgusting to all other
//
//                  (as long as ai+x is unique?)
//
//                  we just dont want partially similiar prime factors => either
//                  a subset/superset X-OR entirely different prime factors
//
// also because of meeting the rquiremnt of the summation
// we also need to have x<ai (gcd(ai,k*ai)=ai) so might as well x<ai
//
// heuristics?
//
// if ai is small there's not a lot of option to add coprimes => multiples (risk
// of going past the sum reqr)
//
// if ai is larger there's a lot of options to add
// coprimes => towards primes??
//
// and checked only on the CURRENT value?O?
//
//
// we can still INTERALLY do multiple operations
//
// just ensure the resulting increment is coprime to itself
//
// so first we can try making all numbers even
//
// clearly,.... power of 2s???
//      nonononono coprime
//
//
// find the smallest disgusting number
//      clearly, it cannot be incremented to the other number in the digusting
//      pair
//
//      but incremented to other number in the arrays that it is coprime to?
//
//      if all the other elements have a gcd>1, clearly there all multiples
//      against something but that something is not present in the array
//
//      cycle the mods against some number??
//      ~~~if there are no elements the disgusting number is coprime to... make
//      it a
//
//
//!!! from the comments, it is nearest prime brother
//      also duplicate primes are fine so its really just finding the NEXT
//      greater prime (greedily)
//          naively: n*sqrt(n)=n^(3/2)
//              n*sqrt(n) is fine with 2s limit
//              can we do that??
//
//          how do we find this???
//
//          pre-generate all prime numbers up to 10^9??
//          => nlogn (no n^2 no it is logn if we continue) ??
//          we're not going back to 1???
//          but we have to check for earlier factors again and again
//
//
//          THE COMPLEXIT IS ACTUALLY sqrt(n)*ln(n)
//
//          where ln(n) is the average truncated linear pass by the observation
//          of average gap between the prime numbers while sqrt(n) because we
//          only need to check that much w.r.t. factors
//
//
//          but this overall would be O(nsqrt(n)lnn)
//
//          unless we do binary search on pre-generated prime nnubers so
//          O(sqrt(n)lnn + nlogn)
//
// recall the empirical spacing of prime numbers is ln(current number)
//
//
//
// or jsut find the max and find the next prime and have all integers add up to
// that prime..

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IV(a, n); // 2<=a[i]

  // ll mx = *max_element(a.begin(), a.end());
  // ll next_prime = -1;
  //
  // for (ll x = mx; x < 2 * mx; x++) {
  //   bool prime = true;
  //
  //   for (ll f = 2; f * f <= x; f++) {
  //     if (x % f == 0) {
  //       prime = false;
  //     }
  //   }
  //   if (prime) {
  //     next_prime = x;
  //     break;
  //   }
  // }
  //
  // vll b(n, 0);
  //
  // II(i, n) { b[i] = next_prime; }

  // vll primes = {1, 2, 3, 5, 7};
  //
  // // DBGLN("HELLO?");
  //
  // // at scale, O(lnn) < O(n) by prime number theorem
  // // which empirically gaurantees a prime number exists between a[i] and
  // // <2*a[i]
  // //
  // // O(lnn) ~~empirically~~ by proof actually
  // //
  // // but O(n) here (which is fine with O(nsqrt(n)))
  // //      and O(lnn) space
  // for (ll x = 11; x <= 1'000'000'000; x += 2) {
  //   // x1,x3,x7,x9
  //   if (x % 5 == 0)
  //     continue;
  //
  //   // O(sqrt(n))
  //   //
  //   // if f*f==x, then x is clearly not prime
  //   //      which is all the more reason to use <= not <
  //   bool prime = true;
  //   // for (ll f = 2; f * f < x; f++) {
  //   for (ll f = 2; f * f <= x; f++) {
  //     if (x % f == 0) {
  //       prime = false;
  //       break;
  //     }
  //   }
  //
  //   DBGLN(x, prime);
  //
  //   if (prime) {
  //     primes.PB(x);
  //   }
  // }
  //
  // DBGLN("PRIMES!");
  //
  vll b(n, 0); // not disgusting

  II(i, n) {
    // binary search on primes (we could've just done it directly)

    // ll L = 0;
    // ll R = primes.size();
    // ll good_m = -1;
    // while (L <= R) {
    //   ll m = L + (R - L) / 2;
    //   if (primes[m] < a[i]) {
    //     L = m + 1;
    //   } else {
    //     // primes[m] >= a[i]
    //     good_m = m;
    //
    //     R = m - 1;
    //   }
    // }
    //
    // b[i] = primes[good_m];

    // DBGLN(a[i], b[i]);

    if (a[i] == 2) {
      b[i] = 2;
      continue;
    }

    // at scale, O(lnn) < O(n) by prime number theorem
    // which empirically gaurantees a prime number exists between a[i] and
    // <2*a[i]
    //
    // O(lnn) ~~empirically~~ by proof actually
    for (ll x = a[i]; x < 2 * a[i]; x++) {
      // O(sqrt(n))
      //
      // if f*f==x, then x is clearly not prime
      //      which is all the more reason to use <= not <
      // bool prime = !(x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0);
      // for (ll f = 2; f * f < x; f++) {
      bool prime = true;
      // if (!prime) {
      //   continue;
      // }
      // for (ll f = 11; f * f <= x; f += 2) {
      for (ll f = 2; f * f <= x; f++) {
        if (x % f == 0) {
          prime = false;
          // break;
        }
      }

      if (prime) {
        b[i] = x;
        break;
      }
    }

    // guaranteed
  }

  // II(i, n) {
  //   // for (ll x = a[i]; x * x < 2 * a[i]; x++) {
  //   //   if () {
  //   //   }
  //   // }
  //   // if (a[i] == 1) {
  //   // }
  // }

  // II(i, n) {
  //   if (a[i] % 2 == 0) {
  //     b[i] = a[i];
  //   } else {
  //     b[i] = a[i] + 1;
  //   }
  // }

  OIT(b);
  ;
}
