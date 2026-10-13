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

// prefix sum
#define PS(v_ps, v_in)                                                         \
  vll v_ps(v_in.size() + 1, 0);                                                \
  for (ll i = 1; i < v_in.size() + 1; i++) {                                   \
    v_ps[i] = v_ps[i - 1] + v_in[i];                                           \
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

#define IS(s)                                                                  \
  string s;                                                                    \
  cin >> s;

#define IVLL(a, n)                                                             \
  vll a;                                                                       \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai;                                                                     \
    std::cin >> ai;                                                            \
    a.push_back(ai);                                                           \
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

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, k);
  IVLL(a, n);
  // alice wins if mexk(A) != mexk(B) (fewer than k times)
  // 0 0 1 1 1 3
  // Bob can optimally win by keeping or copying Alice's move
  //
  // if Alice takes card i Bob takes card i
  // eventually => same MEXk
  // however, if Alice takes the remaining card i, (and Bob cannot take it)
  // => then Alice has that one extra card i, but it does nothing if the amount
  // of card with i-value is <k amount (Mex does not change)
  //
  // in other words, in S, if the # of card with value i is ==2k-1, Alice has
  // the advantage (or else Bob can copy it and we're back to square one)
  //
  // AND by the laws of MEX, every card with value <i must have ==2k-1 times
  //
  // ACTUALLY, we just need to have it like this
  // >=2k,>=2k,>=2k until ==2k-1 (Alice wins)
  // lets call *=2k-1
  // >*,>*,>* until =* (Alice wins)
  // if
  // <* => no point in continuing (Bob wins)
  //      Alice cannot have an advantage
  //
  ST(a);

  ll j = 0;
  II(i, n) {
    // include 0
    ll l = 0;
    while (true) {
      if (j >= n) {
        break;
      }

      if (a[j] == i) {
        l++;
        j++;
      } else {
        break;
      }
    }
    if (l < 2 * k - 1) {
      O("NO");
      return;
    } else if (l == 2 * k - 1) {
      O("YES");
      return;
    } else { // l > 2*k-1
      continue;
    }
  };
  // if it is always >*
  // Bob can always copy Alice's choice and both gets to keep >=k cards
  O("NO");
}
