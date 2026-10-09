#include <bits/stdc++.h>
#include <unordered_map>

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
//  -4  3  0 -4 -4 -1 -4  1 -3 -2 -2 -1
//   .  .  .  .  .  .  .  .  .  .  .  .
//   1  2  1  2  1  2  3  4  3  4  3  4
//         x  y  x  y  x  y
//
//   1     1     1
//      x     x     x
//            y     y     y
//                  z     z     z
//                     a     a     a
//                        b     b     b
//
//   pre-compute triad sum??
//
//   .  .  .  .  .  .  .  .
//
//
// REMEMBER, WE ONLY CARE 2 DIFFERENT TRIADS AT A TIME (UNORDERED)

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n); // >=6
  IVLL(a, n);
  vll triad_sum; // KEY PROPERTY: same as the original array and cannot use any
                 // elements twice unless 4-elements of spacing between the
                 // first pair and the next pair (within a pair of first and
                 // next)
                 // OR it's within the spacing so like 0-element between or
                 // 2-element
                 // MORE SIMPLY =>  0,2,>=4-element spacing starting from 0
                 // available pair combination (if duplicates at these indices)
                 // => (=0,+1)
                 //    (=0,+3)
                 //    (=0,+5)
                 //    (=0,>5)
                 //    => ORDER MATTERS (no re-arranging for simplification) BUT
                 //    AVOID QUAD SOLN.
                 //    honestly fuck this hash map of indices????????
                 //
                 //    extension of the pair config
                 //
                 //    (+1,+2)
                 //    (+1,+4)
                 //    (+1,+6)
                 //    (+1,>6)
                 //    => if =1 => 1
                 //    0 1 2 3 4 5 x x 8 9 - - -
                 //    * + . + . + x x + + + + +
                 //      * + . + . x x + + + + +
                 //        * + . + . x + + + + +
                 //
                 //        can i just brute force it with 2x10^5??? ==> TLE
                 //
                 //    (+2,+3)
                 //    (+2,+5)
                 //    (+2,+7)
                 //    (+2,>7)
                 //
                 //
                 //    consider [0,1,2,7]
                 //    assume no constraints, we can pair with up to
                 //    0,1   0,2xx 0,7
                 //    1,2   1,7
                 //    2,7
                 //    = 3(3+1)/2 = 6
                 //    like a gaussian sum over the length of the vector
  //    but since we KNOW the CONSTANT amount of pairs to avoid, we can find a
  //    CORRECTION TERM  => -1 correction term on (+0,+2) (+0,+4)
  II(i, n - 4) { triad_sum.PB(a[i] + a[i + 2] - a[i + 4]); };
  unordered_map<ll, vll> triad_sum_indices;
  II(i, triad_sum.size()) {
    // if (triad_sum_indices.count(triad_sum[i]) == 0) {
    //   triad_sum_indices[triad_sum[i]] = {};
    // }

    triad_sum_indices[triad_sum[i]].PB(
        i); // for each key, match for +1,+3,+5,>5
            // creates empty VLL auto if key doesnt exist
  }
  DBG_ITER(triad_sum);
  ll unique_unordered_pairs = 0;
  for (const auto &[_k, v] : triad_sum_indices) {
    DBGLN(_k);
    DBG_ITER(v);

    ll sum_total_pairs = (v.size() * (v.size() - 1)) / 2;
    // vll correction_term(v.size(), 0);
    ll correction_term = 0;
    II(i, v.size()) { // avoid +2,+4
      // check if the later 2 indices includes v[i]+2
      if (i + 2 < v.size() && v[i + 2] == v[i] + 2) {
        // correction_term[i + 2]--;
        correction_term--;
      } else if (i + 1 < v.size() && v[i + 1] == v[i] + 2) {
        // correction_term[i + 1]--;
        correction_term--;
      }
      if (i + 4 < v.size() && v[i + 4] == v[i] + 4) {
        // correction_term[i + 4]--;
        correction_term--;
      } else if (i + 3 < v.size() && v[i + 3] == v[i] + 4) {
        // correction_term[i + 3]--;
        correction_term--;
      } else if (i + 2 < v.size() && v[i + 2] == v[i] + 4) {
        // correction_term[i + 2]--;
        correction_term--;
      } else if (i + 1 < v.size() && v[i + 1] == v[i] + 4) {
        // correction_term[i + 1]--;
        correction_term--;
      }
    }

    DBGLN(sum_total_pairs, correction_term);

    unique_unordered_pairs += sum_total_pairs + correction_term;

    // for (ll i = 0; i < v.size(); i++) {
    //   for (ll j = i; j < v.size(); j++) {
    //     if (v[j] - v[i] == 1 || v[j] - v[i] == 3 || v[j] - v[i] >= 5) {
    //       unique_unordered_pairs++;
    //     }
    //   }
  }
  O(unique_unordered_pairs);
}
