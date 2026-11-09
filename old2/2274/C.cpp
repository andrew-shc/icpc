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
//
//
//
// 1            1
// 1 1          2
// 1 1 1        3
// 1 1 1 1      4
// 1 1 1 1 1    5
//
// oranges  | bags
// 1        1
// 2        2 or 1 1
// 3        1 2            (1 1 1 and 3 bad)
// 4        1 1 2 good     1 3 bad (4 bad 2 2 bad)
// 5        1 1 1 2 == 2 3 OK (5 bad 1 4 bad)
// 6        1 2 3 good 2 4 bad (6 bad 1 5 bad 3 3 bad)
//
// ~~~~
// ~~ ==> if odd, 1 off from center
// ~~ ==> if even, 2 off from center
//~~~~
//
//
// sum_k c_k = n
// sum_k k_i = n
//
// min max_i i*c_k
// ~~~~~~~
//
//
// optimization problem? constrained multivar gradient?
//
// suppose for each i-th bag we have b_i count of oranges.
// then, we have k counts of bags where b_i=complicated. (k_j is the value
// corresponding to each counts to determine WHAT is the counter counting)
//      for j=1..n, k_j represents number of b_i's that are j (there can be
//      multiple b_i's)
//          i.e., COUNTing the numbers of bags that have a certain COUNT of
//          oranges
//
// then, for a constrained multi-variable gradient opt. we have the following:
//
//      domain: ~~ vector k=<k_1,...,k_n>
//              vector b=<b_1,...,b_n>  (the number of oranges in each i-th bag)
//      constraint: g(b)=n ==> sum b_i = n
//      objective: min max_i i*c_i
//          => min max_unduplicated(i) b_i*k_{j(i)}
//          (because of the min/max nature => we want b_i*k_{j(i)} to be equal
//          of each other for each count k_j and a mapping j(i) to the
//          individual bags)
//
//                  how do we max b_i*k_{j(i)} each to each other?
//                  for j=1..n and i=1..n
//
// oh yes the other day the problem supports floats but this is integer...
// no (constrained) gradient optimization
//
// n=5
//
//
//          5      3        4
// c_i*i = 5*1; 3*1,1*2; 1*1,2*2
//
// the c_i and i of c_i*i should fit in an xy=c curve.
//
// where say c_i=f(i)  1/i?????????
//
// or i=f(c_i)
//
// but discretized somehow
//
// O(n),O(nlogn),O(n^2)????
//
// n=9
//
// c_i=1 2 3 4 5 6 7 8 9
//     1 3
//     2 6
//     4 9
//     5
//     7
//     8
//
// or,
//     * * *
//     * *
//     * *
//     *
//     *
//
// chatgpt confirms binary search on answer O(logn)
//
// with the following O(n) formula (following the xy=c curve)
//
// sum_i i*c_i <= k
//
//  because we're doing B.S. on k, we should just try to test if we can maintain
//  an error at most k by maximally setting c_i=k and i=1 as the initial step
//  (remember, we have n oranges to distribute)
//  so the whole thing basically becomes a TEST
//
//      n-i*c_i
//
//      1.  n-k1=r1
//      2. r1-k2=r2 s.t. k2 <= k1 (we let the k be the largest)
//      3. etc..
//
//      but importantly is this monotonic? and optimal?
//          we assume optimality (by setting the cost that WE want)
//          but is it monotonic?
//              if it fails, does that many it will always fail if we continue
//              decreasing the cost?
//
//  per chatgpt
//      for every combinations i*c_i <= k
//              ==> c_i <= floor(k/i)
//              ==> maximum c_i amount of i bags (for a total max c_i*i oranges)
//              ==> compute the max possible sum_i i*floor(k/i) and TEST if its
//              >= n (figured this out mightself)
//
//   NOTICE: while we have a f(k) to TEST if f(k) works or not and shows f(k) is
//           monotonic over k (because as k decreases, k1<k2 =>
//           i*floor(k1/i)<=i*floor(k2/i), clearly the sum would decrease or
//           stay the same w.r.t. TESTING n)
//           but we FURTHER test by testing on n
//           test f(k) => test n (what is like a basic problem fact/assumption
//           becomes the star of the show)
//
//
// ~~~~ one important observation:
//      if say you have 2 counts of 5 (max=10)
//          it is better to have 1 count of 6, 1 count of 4 (max=6)
//          or even just 1 count of 4, 1 count of 3, 1 count of 2, 1 count of 1
//          (max=4)
//
//          or eveb 1 count of 3, 1 count of 2, 3 count of 1 ??
//
//      ~~~~
//
//

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);

  ll l = 0;
  ll h = n; // n >= 1
  ll working_k;
  while (l <= h) {
    ll k = l + (h - l) / 2;

    // BINARY SEARCH TEST for k
    ll n_supported = 0;
    for (ll i = 1; i <= k; i++) {
      n_supported += i * (k / i);
    }

    if (n_supported >= n) {
      // TEST = true, try lower k
      h = k - 1;
      working_k = k;
    } else {
      // TEST = false, try higher k
      l = k + 1;
    }
  }
  // assume k is defined
  // AND assume k results in exactly n

  vll a;
  ll bag_ind = 1;
  // O(n)? must be (since we expect |a| = n)
  // but will this produce an array of length n?
  ll n_remaining = n;
  for (ll i = working_k; i >= 1; i--) {
    // i counts of k/i
    // no k/i counts of bags with i
    // => we want k/i bags with i oranges inside it

    // this better be EXACTLY n
    // NONONONO ~~~ this is EXACTLY n since we start with the lowest denominator
    // we can ensure it is exactly n (EASILY) by reduce any numbers after
    //      because at the EOD the B.S. test uses floor to determin validness
    //      but now we want exactness

    // i * (working_k / i) >= n
    // ==> i >= n / (working_k / i)
    //      since naively optimally working_k <= n, and i-- & i<= working_k
    //      so (working_k / i) >= 1
    //      but the min(n_remaining, i) should handle it if n runs out
    II(j, working_k / i) {
      II(jj, min(n_remaining, i)) { a.PB(bag_ind); }
      bag_ind++;
      n_remaining -= i;
    }

    // actually, according to chatgpt we do not need n_remaining
    // and it becomes very clear since at the beginning with i=1, floor division
    // is division

    // II(j, i) { a.PB(k / i); }
  }

  O(working_k);
  OIT(a);

  // ll c = 0;
  // vll a;
  //
  // O(c);
  // OIT(a);
  ;
}
