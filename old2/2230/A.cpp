#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = std::vector<ll>;
using dll = std::deque<ll>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;

const ll NEG = (long long)-4e18;
const ll MOD = 998244353;

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
#define DBLOCK if (false)
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

void solve(ll T);

int main() {
  /////////////////////////////////////////////////////////////////////
  //// comment out the sync when working with interactive problems ////
  /////////////////////////////////////////////////////////////////////
  ios_base::sync_with_stdio(false);
  /////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////

  cin.tie(NULL);
  cout.tie(NULL);

  ll T = 1;

  cin >> T;

  ll t = T;
  while (t--) {
    solve(T - t);
  }

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

// start: 1003
//   end: 1037 (confusion of the orderig of the comparisons and the mult.
//   factor)

// m=ax+by  // minimize this
// n=x+3y
//
// systems of linear eq. has one min. (at the single intersection) and we want
// the min amnt of money => m=a(n-3y)+by => z
//
// even more easily, if 3xindividual key > group key => greedily maximize group
// keys otherwise, just use individeual key
// counter-example, when 2xindividual key > group key => group key until 1
// remaining
//                       1xindividual key > group key => group key all the way

// maximize individual keys if 3 * a <= b
// maximize group keys if 3 * a > b
//  if n%3 == 1
//      last one should use individual key if a <= b
//  if n%3 == 2
//      last one should use individual key if 2a <= b

void solve([[maybe_unused]] ll T) {
  READ(n, a, b); // individual ,group

  // we canNOT put the n modulo conditionals for the ends in the beginning since
  // merely a<b does not tell us if 3*a<b (which means maximize individuals)
  // actually if a>b then it n/3 should round up ==>

  // observation: a<b, 2a<b, 3a<=b, 3a>b, 2a>=b, a>=b

  // if (n < 3) { // 1<=n
  //   if (a < b && (n % 3) == 1) {
  //     OUT(b * (n / 3) + a);
  //   } else if (2 * a < b && (n % 3) == 2) {
  //     OUT(b * (n / 3) + 2 * a);
  //   }
  // }

  if (3 * a > b) { // maximize group keys UNLESS
                   // 3a>b but 2a?b and 1a?b
    if (a < b && (n % 3) == 1) {
      OUT(b * (n / 3) + a);
    } else if (2 * a < b && (n % 3) == 2) {
      OUT(b * (n / 3) + 2 * a);
    } else {                  // 3a>b (and at any remainder)
      OUT(b * ((n + 2) / 3)); // ceil div if a>b
    }
  } else { // 3 * a <= b ==> 2*a <= b ==> 1*a <= b (obviously)
           // 1a <= 2a <= 3a <= b
    OUT(n * a);
  }

  /*   if (3 * a <= b) {        // maximize individual keys
    } else if (2 * a <= b) { // maximize group keys but if n%3 == 2 and 2*a <= b
                             // then use individual keys and so on
    } else if (a <= b) {

    } else { //
    } */

  /*   if (3 * a > b) {
      OUT(n / 3 * b + (n % 3) * a);
    } else if (2 * a > b) {

    } else if (a > b) {
    } else { // a <= b
      OUT(n * a);
    } */
}
