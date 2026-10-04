#include <bits/stdc++.h>
#include <cmath>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

const long long NEG = (long long)-4e18;

#define INC(i, n) for (ll i = 0; i < n; i++)

#define DEC(i, n) for (ll i = n; i >= 0; i--)

#define OUT_ITER(a)                                                            \
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
#define OUT(...) cout_vars(__VA_ARGS__)

#define READ_S(s)                                                              \
  string s;                                                                    \
  cin >> s;

#define READ_VLL(a, n)                                                         \
  vll a;                                                                       \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai;                                                                     \
    std::cin >> ai;                                                            \
    a.push_back(ai);                                                           \
  }

template <typename... Args> void read_vars(Args &...args) {
  (std::cin >> ... >> args);
}
#define READ(...)                                                              \
  ll __VA_ARGS__;                                                              \
  read_vars(__VA_ARGS__)

#ifdef DEBUG
#include "debug.h"
#else
#define DBGLN(...)
#define DBG(...)
#define DBG_ITER(arr)
#define DBG_MAP(map_var)
#endif

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// END MACROS
///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void solve();

int main() {
  /////////////////////////////////////////////////////////////////////
  //// comment out the sync when working with interactive problems ////
  /////////////////////////////////////////////////////////////////////
  ios_base::sync_with_stdio(false);
  /////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////

  cin.tie(NULL);
  cout.tie(NULL);

  solve();

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// START ACTUAL CODE
///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

// start:
//   end:

const ld EPS = 0.000001;

// n breaks
// each break i lasts ti
// total of p pushups over ALL n breaks
// MINIMIZE units of stress over all breaks
// x^2/s for each break, each break how many x pushups to do till p is reached
// (but minimize units of stress)
//
// if all ti are same, always want to average them out
// if some tis are larger.... how much x within the differing tis till they
// equal?
//
//      x1^2/s1 = x2^2/s2
//
//
//
//
//      min sum_i x_i^2/s_i ==> find the point where all x_i^2/s_i are equal to
//      each other...
//
//      which means ==> x_i/sqrt(s_i) are equal to each other
//      where sum x_i = p
//            x_i/sqrt(s_i)  s_i has a limited sub-inverse impact on x_i
//
//            sqrt(si)/sqrt(si) to be equal to each other COULD work
//            x_i*sqrt(si)/sqrt(si) would work even better
//                  => sum x_i = p
//                  => [x_i*sqrt(si)]^2/si
//                  ==> min number of stress units he will feel at the most
//                  minimum
//
//                  wait what is x_i?
//
//                  sqrt(si)/p?
//
//                  ==> si*p^2/si => p^2
//                  but sqrt(si)/p == p??
//
//                  wait p/sqrt(si) ???
//
//                  p*sqrt(si)????
//                  xi^2/si
//
//                  what makes sum_i xi = p while also making xi^2/si equal to
//                  each other
//
//
//                  sum s_i or sqrt(si) to get Z
//                  sum_i p*(s_i/Z or sqrt(z_i)/Z) = p
//                  but also sum [p*sqrt(si)/Z]^2/si == sum p/Z^2 (which
//                  we only care about equality) ==> the min element is p/Z^2
//                  where Z = sum of sqrt(si)
//
// nononono go back
//                                              Z=sum of p*sqrt(s_i)?? or just
//                                              sum of (sqrt_si)??
//                  sum_i p*sqrt(s_i)/Z = p
//                  sum_i [p*sqrt(s_i)/Z]^2/s_i = sum_i p^2s_i/(Z^2*s_i) = sum_i
//                  p^2/Z^2
// 3 1
// 1 1 1
// 1 / 3???? Z = sqrt(1)+.+. = 3
//
//
//
//
// sum_i p*sqr(z_i)/Z p sum_i sqrt(z_i)/Z = p  (since sum_i sqrt(z_i)/Z = 1
// where Z = sum of
//                              sqrt(z_i)??? and p is constant)
//
//    suppose x_i = p sqrt(z_i)/Z
//    then, sum_i (p * sqrt(z_i) / Z )^2/s_i = p * sum_i z_i / (Z^2*s_i) where
//    z_i = s_i
//                                           = p * sum_i 1/Z^2 = p/Z^2

void solve() {
  READ(t);
  INC(_tt, t) {
    ll n;
    ld p;
    cin >> n >> p;
    // READ(n, p);
    READ_VLL(t, n);
    ld sum = 0;
    DBGLN(p);
    DBG_ITER(t);
    DBGLN(sqrtf64((ld)t[1]));
    INC(i, n) { sum += sqrtf64((ld)t[i]); }
    DBGLN(sum, p * p, (ld)(sum * sum), (p * p) / (sum * sum),
          n * (p * p) / (sum), p / (sum * sum));

    ld sum_ans = 0;

    OUT((n * p * p) / (sum * sum));
  }
}
