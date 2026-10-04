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

//
//
// 0123456789
// 0
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// 12
// 23
// 34
// 45
// 56
// 67
// 78
// 89
// 123 - 789
// 1234 - 7894
// 123456789 - 123456789 <== always stops here
// 1234567899 - continues forever??? ==> -1 (since the digit must be strictly
// increasing exactly by one but above that special number that cannot meet the
// requirements ever)

void solve() {
  READ(t);
  INC(_tt, t) {
    READ(n); // n>=1
    if (n > 123456789) {
      OUT(-1); // actually never reaches i think from the contraint
    } else {
      dll d; // digits from first to last ( in this order -->)
      while (n >= 1) {
        d.push_front(n % 10);
        n /= 10;
      } // ends the moment a 0 reached
      if (d.size() == 1) {
        OUT(d[0]);
        continue;
      }

      ll selected_starting_digit = d[0];
      ll digit_requirement = d[0];
      ll ending_number = 0;

      // ~~~~~purpose, either current selected starting digit work OR the next
      // one work

      // 119
      // 111119 -> 111123 (wouldn't work) -> 123456
      // go up until the LAST DIVERGENCE (123456)
      //      in this case, the 2nd digit????
      //              potential counter example:
      //                    111159 --> 123456 (nope) 234567 (yes)
      //                              ^
      //                             0 divergence => at most 0 divergence later
      //                             elements (can support <0 divergence)
      //      IMPL
      //
      //            ALL 0-divergence => works as is
      //            <=0 divergence with >0 divergence AFTER a ==0 divergence
      //            (tight) =>
      //                    move the whole thing up
      //            <=0 divergence with >0 divergence => generate from the
      //                    starting digit as is
      //
      //
      //                    divergence ONLY from the 2nd element
      //
      //
      //       divergence:
      //           D/1    x <= <= <= <= <= <= => as is (or re-generate from x)
      //           D/2    x <=  <  >  >  >  > => re-generate from x
      //           D/3    x  < ==  >  >  >  > => re-generate from x+1 ~~~~~~~
      //           WRONG D/4    x ==  <  >  >  >  > => per D/2 D/5    x  >  >
      //           .....      ==> re-generate from x+1 D/6    x  < ==  >  per
      //           D/3 the == is rigid and should be detected if there's any <
      //           before == to carry the > to the < before ==
      //  ****ACTUALLY TREAT x as 0 divergence

      // REAL IMPL: if [=0, >0] divergence ==> re-gen from x+1 (the only case to
      // regen from x+1)
      //            if [<0, >0] divergence ==> re-gen from x
      //              if [<0, ==, ==, ==, >0] ==> re-gen from x (regardless of
      //              how many >0 after it so instant end)

      ll prev_divergence =
          d[0] -
          digit_requirement; // think the d array as starting from the left

      bool below = false;
      digit_requirement++;
      // INC(i, d.size())
      for (ll i = 1; i < d.size(); i++) {
        ll divergence =
            d[i] -
            digit_requirement; // sometimes, digit_requirement becomes 10 which
                               // means all current digit have to be -1 and
                               // depending on previous divergence, might
                               // require the whole hting shifted up usually
                               // (because prev digit_requirement would be 9 and
                               // unless divergence is <0; otherwise prev_div ==
                               // 0 and current must be -1 and increase)
        // DBGLN(i, prev_divergence, divergence);
        if (prev_divergence == 0 && divergence > 0) {
          selected_starting_digit++;
          break;
        } else {
          // divergence: [<,>] or [<,=] is fine
        }
        if (divergence < 0) {
          below = true;
          break;
        }

        // if (digit_requirement == d[i]) {       // fine
        // } else if (digit_requirement < d[i]) { // automatic next
        //   selected_starting_digit++;
        //   break;
        // } else { // (below) try to fit to the current increment (keep the
        //          // initial i)
        //   if (digit_requirement >= 10) { // automatic next
        //     selected_starting_digit++;
        //     break;
        //   }
        // }
        prev_divergence = divergence;
        digit_requirement++;
      }

      // however, IF the selected starting digit is more than (10 - d.size()) =>
      // increase d and reset selected starting digit to 1
      ll d_size = (ll)d.size();
      if (selected_starting_digit >
          10 - d.size()) { // should never reach below 0, and 10 is always >
                           // 10-d.size()
        d_size++;
        selected_starting_digit = 1;
      }

      INC(d_size_cnt, d_size) {
        ending_number +=
            selected_starting_digit * (ll)(pow(10, d_size - d_size_cnt - 1));

        // 10 to the power of d_size-1

        selected_starting_digit++;
      }

      OUT(ending_number);
    }
  }
}
