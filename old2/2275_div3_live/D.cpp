#include <bits/stdc++.h>
#include <climits>

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
//
// O.1: IF a<b<c => always go down (cannot go up) => NOP
//      O.1/1: IF NOT => some operation moves the unit up => DO IT
// O.2: since each LAB goes +/-1 (== NO TRADEOFFS TO CONSIDER BETWEEN LABS)
//          ==> pick the smallest lab
//
// IMPL:
//      PICK THE WORST LAB
//      IF THE WORST LAB ALWAYS GO DOWN (a<b<c per O.1)
//          => THATS THE MIN (S)
//      IF THE WORST LAB CAN GO UP (O.1/1)
//          => INCREASE IT UNTIL +1 AGAINST THE 2ND WORST LAB
// 10^18 requires O(n) soln or even O(1) or O(logn)
//
// O.3: IF a>b OR a>c OR b>c (per O.1/1) => STATIONARY STATUS
//          SINCE a>b => c++
//                a>c => b++
//                b>c => a++
//                (does not affect the original inequality)
//
//                and S is based off of SUM of a+b+c
//
// IMPL:
//      sort the lab by worst to best (compute their S_i)
//      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ find [O.1] labs
//
//      if [O.1] LAB EXIST: // best min we can do (but still depends on k)
//          find the worst [O.1] lab
//          k* = compute the number of operators for more worse labs to catch up
//          to AT the S_i of the worst [O.1] lab
//
//          if(k* <= k) {
//              O([O.1] lab's S_i)
//          } else {  // since k < k* => how much of the available operations
//                          maximiize S
//              // by squares (do it in code)
//              O([O.1])
//          }
//      else:
//          maximize it
//
// NOTE: 0 case do exist also (e.g., 5 5 5 => cannot increase or decrease => NOP
//                                  both ways => O.1)
// entire model wrong:
//
//  a=b=c and a<b<c can get out just by making one of the elements lower so that
//  there's a positive difference to get that lab back up
//  .............
//
//  DP? since there would be a decision factor (e.g., -k** on the amount to make
//  that lab go positive delta again and would it be worth it)
//
// so a=b=c => truly NOP reduce the O.1 case to this a=b=c
// a<b<c => depends (decision factor)
//      investment needed before positive delta:
//          min(b-a, c-b, c-a)+1
//
//          incomplete
//              a<b => c-- until either b>c or a>c => b>c or a>c
//                      => min(b-c,a-c)+1
//              b<c => a-- until either a>b or a>c => b<a or c<a
//                      => min(a-b,a-c)+1
//              a<c => b-- until either b>c or a>b => c<b or a>b
//                      => min(b-c,a-b)+1
//
//                  => min(min(min(b-c,a-c),min(a-b,a-c)),min(b-c,a-b))+1
//
//           INCOMPLETE INCOMPLETE
//              => just think of it like this, a<b<c means any element can
//              decrease once (AND ONLY DECREASE NOT INCREASE)
//
//      investment required since it's one way to moving up
//          like a ditch at the end before the increase to the next level
//
//
//
// key error on WA2
//
// when you decrease by investment, the si has to be decreased also... twice...
// should the order be changed?
// no, because sometime we might not want to invest in it and just leave it at a
// temporarily higher minimum (no tradeoffs i believe or decision factor to
// consider)

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, k);
  vll si;                     // of each lab
  ll si_stop = LLONG_MAX;     // worst O.1 lab's si
  bool si_stop_exist = false; // whether they exist
  vll investment_needed;      // activates whenever we are trying to raise the
                              // minimum level

  vpll aaaaaaaaaaa;
  II(i, n) {
    I(a, b, c);
    // if (T == 7807) {
    //   O(a, b, c);
    // }
    if (a == b && b == c) {
      si_stop_exist = true;
      si_stop = min(si_stop, a + b + c);
    } else {
      si.PB(a + b + c);
      if (a <= b && b <= c) {
        investment_needed.PB(min(b - a, min(c - b, c - a)) + 1);
        // dont get confused again... we only care about the sign offset +/-1
        // DBGLN(a, b, c);
        // DBGLN(b - c, a - c, a - b, a - c, b - c, a - b);
        // DBGLN(min(b - a, min(c - b, c - a)) + 1);
        // investment_needed.PB(
        //     min(min(min(b - c, a - c), min(a - b, a - c)), min(b - c, a - b))
        //     +
        //    1);

        aaaaaaaaaaa.PB({a + b + c, min(b - a, min(c - b, c - a)) + 1});
      } else {
        investment_needed.PB(0);
        aaaaaaaaaaa.PB({a + b + c, 0}); // why did i write, 1??????
      }
    }
    // if (a > b || a > c || b > c) {
    //   si.PB(a + b + c);
    // } else { // either all 0s or some are negatives => NOP => O.1
    //   si_stop_exist = true;
    //   si_stop = min(si_stop, a + b + c);
    // }
  };
  // if (T != 7807) {
  //   return;
  // }

  ST(si);
  ST(aaaaaaaaaaa); // sort by si (.first)

  II(i, aaaaaaaaaaa.size()) {
    si[i] = aaaaaaaaaaa[i].first;
    investment_needed[i] = aaaaaaaaaaa[i].second;
  }

  DBGLN(si_stop_exist, si_stop);
  DBG_ITER(si);
  DBG_ITER(investment_needed);

  if (si_stop_exist) {
    // si_stop not in the vll si, but we try to reach every element within vll
    // si to be AT si_stop (so si_stop is the true min)

    // si_stop can be at the very end (not included)

    if (si.size() == 0) {
      O(si_stop);
      return;
    } else if (si_stop <= si[0]) {
      O(si_stop);
      return;
    }

    ll prev_si = 0;
    ll investment_accrued = 0;
    II(i, si.size()) {
      if (i == 0) {
        prev_si = si[0];
        investment_accrued += investment_needed[0];
        continue;
      }

      ll cur_si = si[i];
      if (prev_si - cur_si == 0) {
        investment_accrued += investment_needed[i];
        continue;
      }

      ll width = i;
      ll height = cur_si - prev_si;

      if (width * height + investment_accrued * 2 <=
          k) { // enough operations to cover it
        k -= width * height + investment_accrued * 2;
        investment_accrued =
            0; // chatgpt pointed it out of this error bruh <<<<<<<<<<<<<<
        // however, if si_stop is whithin prev_si to cur_si => output si_stop
        if (prev_si <= si_stop && si_stop <= cur_si) {
          O(si_stop);
          return;
        }
      } else if (investment_accrued * 2 <= k) {
        // either the limited amount of k ops restrict it first or, if si_stop
        // is within range, it stops first
        ll new_min = prev_si + (k - investment_accrued * 2) / width;
        if (prev_si <= si_stop && si_stop <= cur_si) {
          if ((si_stop - prev_si) <=
              (k - investment_accrued * 2) /
                  width) { // si_stop is less than or AT the
                           // potential height k/width can add
            O(si_stop);
            return;
          } else { // despite si_stop being in range, k/width is smaller and
                   // limited k ops shortened the whole thing before si_stop is
                   // reached handled at later cases
          }
        }
        O(new_min);
        return;
      } else {
        O(prev_si); // no need to check for si_stop
        return;
      }

      prev_si = cur_si;
      investment_accrued += investment_needed[i];
    }

    // remember, si_stop is excluded from the elements
    // also this assumes si_stop is at the very end
    ll width = si.size(); // AFTER MANY WA2 THIS IS THE LIKELY BUG, SINCE
                          // the si_stop is excluded this needs a +1
                          // (assumed to be at the end AT THIS POINT)
    // ~~~ actually no this excludes the si_stop which is assumed to be at the
    // end..
    ll new_min;
    if (investment_accrued * 2 <= k) {
      new_min = min(si[si.size() - 1] + (k - investment_accrued * 2) / width,
                    si_stop);
    } else {
      new_min = min(si[si.size() - 1], si_stop);
    }
    O(new_min);
    return;

  } else {
    ll prev_si = 0;
    ll investment_accrued =
        0; // slowly accrue on same/duplicate levels until the main min level
           // is able to be raised (which it resets)
    for (ll i = 0; i < si.size(); i++) {
      // if (i < si.size() - 1) {
      //   if (si[i] == si[i + 1]) {
      //     // if the si of the current is same as the next, move onto the next
      //     to
      //     // simplify problem
      //     continue;
      //   }
      // }

      if (i == 0) {
        prev_si = si[0];
        investment_accrued += investment_needed[0];
        continue;
      }

      ll cur_si = si[i];
      if (prev_si - cur_si == 0) {
        // duplicates and nothing interest, we need to land on the RISING
        // edge of the next (i.e., the START/FIRST of the next group of
        // elements if duplicates exist)
        investment_accrued += investment_needed[i];
        continue;
      }

      // since this is working on the rising edge (no +1)
      ll width = i;
      ll height = cur_si - prev_si;

      // BEGIN

      if (width * height + investment_accrued * 2 <= k) {
        k -= width * height + investment_accrued * 2;
        investment_accrued = 0;
      } else if (investment_accrued * 2 <= k) {
        ll new_min =
            prev_si + (k - investment_accrued * 2) /
                          width; // how many heights the remaining k can take to
                                 // raise the prev_si equally
        O(new_min);
        return;
      } else { // investment_accrued > k
        O(prev_si);
        return;
      }

      // END

      prev_si = cur_si;
      investment_accrued += investment_needed[i];

      // assume this is the last of the si (if there are duplicates)
      // width: i+1
      // height: cur_si-prev_si
      //      actually we can check for duplicates when cur_si-prev_si == 0
    }

    // there's a return in there, but if still running here means there's still
    // k>0 left

    ll width = si.size();
    ll new_min;
    if (investment_accrued * 2 <= k) {

      new_min = si[si.size() - 1] + (k - investment_accrued * 2) / width;
    } else { // investment*2 > k  ==> no point in using k to add and optimize
             // (investment taking too much)
      new_min = si[si.size() - 1];
    }
    O(new_min);
    return;
  }
}
