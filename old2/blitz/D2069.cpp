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
//
// CLARIFICATION:
//      we assume we ALWAYS want to perform AN operation
//      in order to convert the string to a palindrome
//      <- find the MIN POSSIBLE LENGTH to achieve palindrome
//
// P.1: if string s is already a palindrome, we can do 0-length
//          => 0
// P.2: by the input assumption of always ABLE TO BE converted to a palindrome
//          => string s is at most a shuffle away from palindrome
//              (no need to check for existence of a character)
//          AND there must be EVEN #s for each unique character of string s
//
//
// O.1: given each unique character of a character SET:
//          ensure half of its amnt is on one side and the other half is on the
//                  other side
//
//     O.1/1: if they are, we just need to re-order AT MOST one of the halves
//            if not, we would have to re-order past the halves
//
//     O.1/2: per O.1/1, if all chars are split in halves,
//              1. splice into two halves
//              2. reverse one of the halves
//              3. find the min. span of the differences
//              4. compute the length and output
//
//            otherwise,
//              ???
//
//              dp on halves??
//
//
//
// ~~~acbacbab
//~ a
// ~ c
//  ~ b
//   ~ a
//     ~c
//      ~b
//       ~a
//        b
//
//
// === STUCK ON cases where there are more certain characters on one of the
// halves ===
//
//
//
//!!! binary search on answer (with the domain or the string limited to portions
// when the palindrome pairs becomes different)
//
//  b/c of the symmetric properties of the ANSWER (palindrome)
//
//  we can do a binary search (on both sides? so like O(2nlogn)?)
//  on the length required to make the string possibly palindrome
//
//  freq map?
//
//  also the length m must be fixed to the first differing "palindrome" pairs
//
//  and the key differences is the prefix because as observed before sometimes
//  we just need to shuffle within the first half
//
//  technically, can't this be done with building a symmetric freq map on the
//  two partition?
//
//  if different, needs to cross middle-point
//  if same, no need to cross the middle-point
//
//  but this only checks on the middle-point and can easily be extended to other
//  points
//
//
//
//!! (per chatgpt)
//!                 given every possible substring length we have to satisfy two
//!                 constraints
//!     also another observation:
//!         we only have 26 possible letters as the input hence this side would
//!         be constant. this supports the usage of a freq map (which is
//!         inherently additive which does not care about prior order)
//!
//!      CONSTRAINT 1.
//!
//!         for every outside remaining characters, there must be as much of
//!         those within the selected substring length (w/o caring about the
//!         order via the usage of things like freq map)
//!
//!      CONSTRAINT 2.
//!
//!         for every OUTSTANDING/REMAINING characters,
//!             (especially past the middle-point)
//!
//!         there must be even amount of them
//!
//
//      additionally, we have two-ways of approaching this by using
//      prefix/suffix (i.e., one of them might exclusively have a better option
//      from an exhaustive case-by-case POV) but also we can check prefix/suffix
//      simulatenously since we only care about minimizing the length itself
//      (which the prefix/suffix are invariant of if done simulatenously)
//
//  so the 2ptr impl is easier to understand but the binary search is cleaner to
//  impl (less chance for bugs)
//
//  so we have to restrain ourselves from impelmenting a prefix freq map for
//  easier impl that equally works within the given the standard O(nlogn)
//  constraint
//

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  IS(s); // even-lengthed

  while (s.size() >= 2 && s[0] == s[s.size() - 1]) {
    s.erase(0, 1);
    s.pop_back();
  }

  // s.size()==0 messes up
  if (s.size() == 0) {
    O(0);
    return;
  }

  // to ensure all different pairs are at least included
  // (the easy part, the hard part is the minimal length needed after the middle
  // part becomes nice or after)
  ll min_index_possible = 0;
  II(i, s.size() / 2) {
    if (s[i] != s[s.size() - 1 - i]) {
      min_index_possible = i;
    }
  }

  // restrict to pairs that needs to be changed
  array<ll, 26> whole{};
  DBG_ITER(s);
  II(i, s.size()) {
    // if (s[i] != s[s.size() - 1 - i]) {
    whole[s[i] - 'a']++;
    // }
  }
  DBG_ITER(whole);

  // directly from chatgpt (apparently we need to mannually/directly check
  // pair-wise)
  auto check = [&](ll m, bool suffix) -> bool {
    ll n = s.size();
    ll l = suffix ? n - m : 0;
    ll r = l + m; // exclusive

    array<ll, 26> freq{};

    // Count all characters available for shuffling
    for (ll i = l; i < r; i++) {
      freq[s[i] - 'a']++;
    }

    // Process every mirrored pair
    for (ll i = 0; i < n / 2; i++) {
      ll j = n - 1 - i;

      bool in_i = (l <= i && i < r);
      bool in_j = (l <= j && j < r);

      if (!in_i && !in_j) {
        // Both positions are fixed
        if (s[i] != s[j]) {
          return false;
        }
      } else if (in_i && !in_j) {
        // Must match the fixed character at j
        if (--freq[s[j] - 'a'] < 0) {
          return false;
        }
      } else if (!in_i && in_j) {
        // Must match the fixed character at i
        if (--freq[s[i] - 'a'] < 0) {
          return false;
        }
      }
    }

    // Remaining characters must form internal pairs.
    // This check is redundant under the problem's guarantees,
    // but keeping it makes the logic explicit.
    for (ll c = 0; c < 26; c++) {
      if (freq[c] % 2 != 0) {
        return false;
      }
    }

    return true;
  };

  // binary search on the proposed substring length
  // ll lo = 0;
  ll ans = -1; // while loop runs at least once with guaranteed valid for at
               // least once
  ll lo = min_index_possible + 1; // -> convert to lengths
  ll hi = s.size();               //  - 1;  remember in lengths (1@)
  ll m;
  DBGLN(lo, hi, s.size());
  while (lo <= hi) {
    m = lo + (hi - lo) / 2;

    // bool valid = true;
    // bool valid = false;

    // check prefix validity
    bool p_valid = true;
    array<ll, 26> p_freq{};
    II(i, m) {
      p_freq[s[i] - 'a']++;
      if (i < m - 1) {
        continue;
      }
      II(c, 26) {
        if ((2 * p_freq[c] - whole[c]) < 0) {
          p_valid = false;
        }

        // if ((2 * p_freq[s[i] - 'a'] - whole[s[i] - 'a']) < 0) {
        //   valid = false;
        // }
      }
      // if (whole[s[i] - 'a'] - 2 * p_freq[s[i] - 'a'] < 0) {
      //         valid = false;
      //       }
      // II(c, 26) {
      //   // if (whole[c] - 2 * p_freq[c] < 0 &&
      //   //     ((2 * p_freq[c] - whole[c]) % 2 == 1)) {
      //   // if ((whole[c] - 2 * p_freq[c] < 0) &&
      //   //     ((2 * p_freq[c] - whole[c]) % 2 == 1)) {
      //   if (whole[c] - 2 * p_freq[c] < 0)
      //     // remember whole[c] is even
      //
      //     // whole[c]-p_freq[c] < p_freq[c]
      //     // p_freq[c]-(whole[c]-p_freq[c]) % 2 == 1
      //     // ^^         ^^ the characters to still reserve
      //     // ^^                 !! but the character to reserve also
      //     decreases
      //     //                       as we continue to march to the right..
      //     //                       (but this is what the -p_freq[c] is for)
      //     // ^^
      //     // the current total count of character the
      //     // difference yields outstanding character not required by the
      //     outside
      //     //
      //     // ~~~~~~~~ there's a huge problem, it assumes with every new
      //     // ~~~~~~~~ character
      //     //
      //     // if we include the odd-th character c, we still need to reserve 1
      //     // to make sure its position is fixed to the other end
      //     // because it cannot form a 2nd (or another) pair also
      //     //
      //     //
      //     // chatgpt just took-back and said this constraint is redudant
      //     (???)
      //     //
      //     // so anyways we only need to check there's enough.. that's all!
      //     //
      //     // whether the inside is even or not can be thought of as:
      //     // if even: always work arbitrary decide s.t. it will always work
      //     // if odd: the odd one out would just be fixed to whatever its
      //     outside
      //     // also...??
      //
      //     // at the current amnt whole[c] (after prior deduction)
      //     //      do we still have enough the outside of the c to take the c
      //     //      inside?
      //     //
      //     // if there's not enough outside c, we look inside and check if
      //     // there's even amount if not => BAD
      //     //
      //     // but how can we check and what if we're not over the middle
      //     point??
      //     //    for every character we march over the middle-point (per
      //     chatgpt)
      //     //        the character get's recorded as extraneous and will be
      //     //        checked for evenness (in its entirety)
      //     //    in another word,
      //     //          we only start to check for evenness once we march over
      //     the
      //     //          evenness
      //     valid = false;
      // }
      // if ((whole[c] <= p_freq[c]) && (p_freq[c] % 2 == 1)) {
      //   // so now all the counts of c is inside, if the count of such c is
      //   odd
      //   // => bad
      //   valid = false;
      // }
    }

    // check suffix validity
    array<ll, 26> s_freq{};
    bool s_valid = true;
    // DD(i, m) {
    string zz = "abcdefghijklmnopqrstuvwxyz";
    DBG_ITER(zz);
    DBG_ITER(whole);
    II(i, m) {
      // s_freq[s[i] - 'a']++;
      DBG_ITER(s_freq);
      s_freq[s[s.size() - 1 - i] - 'a']++; // stupid bug
      if (i < m - 1) {
        continue;
      } // we only check if its valid at the VERY END
      II(c, 26) {
        if ((2 * s_freq[c] - whole[c]) < 0) {
          s_valid = false;
        }

        // if ((2 * s_freq[s[i] - 'a'] - whole[s[i] - 'a']) < 0) {
        //   valid = false;
        // }

        // if (whole[s[i] - 'a'] - 2 * s_freq[s[i] - 'a'] < 0) {
        //   valid = false;
        // }
      }
    }

    p_valid = check(m, false);
    s_valid = check(m, true);

    DBGLN(s_valid, p_valid);
    if (s_valid || p_valid) {
      // go for smaller
      DBGLN("GOOD", lo, hi, m);
      ans = m;
      hi = m - 1;
    } else {
      DBGLN("BAD", lo, hi, m);
      lo = m + 1;
    }
  }
  O(ans);
  //   ll start_diff = -1;
  //   ll end_diff = -1;
  //   II(i, s.size() - 1) {
  //     if (s[i] == s[s.size() - i - 1]) {
  // if(start_diff == 0)
  //     } else {
  //     }
  //   }
  ;
}
