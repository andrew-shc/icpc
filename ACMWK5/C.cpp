#include <bits/stdc++.h>
#include <climits>
#include <unordered_set>

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
  vpll a;                                                                      \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai, bi;                                                                 \
    std::cin >> ai >> bi;                                                      \
    a.push_back({ai, bi});                                                     \
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

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IS(t);

  // set<char> cipher;
  map<char, char> decipher;
  map<char, char> reverse;

  // char[26] cur =
  // string cur = "abcdefghijklmnopqrstuvwxyz";
  string unused = "abcdefghijklmnopqrstuvwxyz";
  // unordered_
  set<char> unused_set(unused.begin(), unused.end());
  // ll cur_ind = 0;

  // if (t[0] == 'a') {
  //   swap(cur[0], cur[1]);
  // }
  II(i, n) {
    if (decipher.count(t[i]) == 0) {
      ll cur_ind = 0;
      // while (unused_set.count('a' + cur_ind) == 0 ||
      //        (('a' + cur_ind) == t[i])) {
      //
      // consider:
      // ba
      //
      // s[]  t[]
      // a -> b
      // b ->
      // c -> a
      //
      // cba
      //
      // a?
      // a -> c
      // b -> a?
      // c -> b
      // d -> a?
      //
      // First, we always go from the earliest to the last for each next
      // cahracter (base optimal) without duplicates (unused character)
      //
      // ~~~THEN, for each next unused character `c` ~~~
      //
      // THEN, from the earlist to the
      // latest character c for a->z (compared to the UNIQUE'D input character
      // t[i]): (greedy)
      //
      //     we take c IF
      //          1. c is unused (cannot re-use an already used character)
      //          2. t[i] != c (cannot self-reference)
      //          3. t[i] (as a key) is unused
      //
      //
      //
      //  except when z is reached
      //
      //    c i
      //
      //    just do loop detection
      // while ((unused_set.count('a' + cur_ind) == 0) ||
      //        (reverse.count(t[i]) > 0) || (('a' + cur_ind) == t[i])) {
      //   // DBGLN(cur_ind, (char)('a' + cur_ind), t[i]);
      //   cur_ind++;
      // }

      while (true) {
        DBGLN("OUTER", (char)('a' + cur_ind));
        // while (unused_set.count('a' + cur_ind) == 0 || cur_ind < 25) {
        while (unused_set.count('a' + cur_ind) == 0 && cur_ind < 25) {
          cur_ind++;
        }
        DBGLN("POST", (char)('a' + cur_ind));

        // cur_ind = last unused character OR 'z'
        // test loop detection
        // by the logic of loop detection, 'z' will always be reached w/o loops
        // (where 'z' will get a freebie of having loops)
        // and also means every alphabet is mapped and no longer needs to run
        // through this again
        // actually z might be pre-maturely reached
        // it should be whenever the last character is filled

        if (decipher.size() == 25) {
          // just needs to add the 26th now w/ loops (for certain)
          break;
        }

        // this also checks for self-loop
        bool looping = false;
        char ending = t[i];
        char current = 'a' + cur_ind;

        // DBGLN(ending, current);
        // DBG_MAP(decipher);
        while (true) {
          if (current == ending) {
            looping = true;
            break;
          }

          if (decipher.count(current) == 0) {
            // no loop => cur_ind good
            break;
          } else {
            current = decipher[current];
          }
        }

        // DBGLN(looping);
        if (!looping) {
          break;
        }
        // if looping at least manually increase the index...
        cur_ind++;
      }

      // DBGLN("==", cur_ind, (char)('a' + cur_ind), t[i]);

      // cur_ind works
      decipher[t[i]] = 'a' + cur_ind;
      // reverse['a' + cur_ind] = t[i];
      unused_set.erase('a' + cur_ind);
      // unused_set.erase(t[i]);
      // decipher[t[i]] = cur[cur_ind];
      // cur_ind++;
    }
  }

  string s = t;
  II(i, n) { s[i] = decipher[t[i]]; }
  O(s);
  ;
}
