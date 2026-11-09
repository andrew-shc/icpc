#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>

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
  ios_base::sync_with_stdio(true);
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

// TRUE FALSE TEST
// every mutually-exclusive adjacent pairs of questions are ALWAYS different
//      guaranteed to be ==50%
// each pairs will either be ALL correct or ONE correct >= 75%
// this means randomly guessing the first option
//  i

void solve() {
  READ(t);
  INC(_tt, t) {
    vll pspace;
    INC(c, 1000) { pspace.push_back(c); } // 0-499 and 500-999
    INC(i, 100) {
      string ans = "X";
      random_shuffle(pspace.begin(), pspace.end());
      bool cond = pspace[0] <= 499;
      if (cond) {
        OUT('T');
        ans = "T";
      } else {
        OUT('F');
        ans = "F";
      }
      // monte carlo estimator???
      READ_S(resp);
      if (resp == ans) {
        if (cond) {
          OUT('F');
        } else {
          OUT('T');
        }
      } else {
        if (cond) {
          OUT('T');
        } else {
          OUT('F');
        }
      }
      READ_S(resp_idgaf);
    }
    // OUT(pspace[0]);
  }
}
