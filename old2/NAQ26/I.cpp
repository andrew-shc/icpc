#include <bits/stdc++.h>

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

// O.1: if there exists a constraint that requires a>b (where the later a must
// be performed befoore the earlier b is impossible to meet the required order 1
// to n)

//
//
//
// 13423421
// 1342 <-- no constraints within these 4 uniquely-identified constraints ==>
// can come in any order
// 12 <-- consider this case, even if lets say
//                      1 3
//                      2 3
//                          that wouldnt work since we just say first do 2 then
//                          do 1 (since they all meet the requirement of before
//                          3)
// H.1: every element needs adjacent constraints???
//
//
//                  1 3
//                  2 4
//
//                      2,1 go first (bad)
//                      then 4,3 (also bad)
//
//                      even with 1,2 to enforce 1,2
//                          it can still result in 1,2,4,3
//

// O.1: every elements needs to be constrained (up to n-1 constraints)
// per H.1: IMPL
//
//      constraints = n-1
//      if an adjacent pair is found, --

void solve() {
  READ(t);
  INC(_tt, t) {
    READ(n, m);
    ll constraints = n - 1;
    INC(_i, m) {
      READ(a, b); // assume a!=b
      if (a > b) {
        constraints = -1;
      } else if (constraints != -1) { // ~~a < b~~, check adjacent pairs as long
                                      // the CONSTRAINTS ARE VALID (all a<b)
        if (a + 1 == b) {             // adjacent pairs
          constraints--;
        }
      }
    }
    OUT(constraints);
  }
}
