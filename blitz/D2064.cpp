#include <algorithm>
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
// CLARIFICATION: TO ITS LEFT means STRiCTLY ADJACENT OF ITS LEFT
//
// quadratic???
// has to be sub-quadratic (linear or log-linear or faster)
//
//      pre-compute the a[]'s somehow?
//
// for each x (of queries)
//
// x0 ^ x1 ^ x2 ^ x
//
// by the constraint sum of n,q will not exceed 4x10^5
//
// common sense: we have to read each elements anyways linearly so at least we
// must be able to do another linear pass for each query
//
//      actually, they just only gave us a single linear array
//      so we have to find a sub-quadratic soln. actually
//
// we can just compute the prefix XOR
//
// P.1: XOR is associative
//
// ~~~ KEY OBSERVATION (failed observation)
// ~~~ O.1: if 0 < x == y: x ^ y == 0
// ~     if 0 < x < y: x ^ y < y
// ~     if 0 < y < x: x ^ y < x
//
//
// === STUCK, HOW TO FIND A SUB-QUADRATIC / O(logn) or O(1) check per query ===
//
//      O(logn).....
//
//      sort the queries????
//      keep the index also??
//
//      but this assumes monotonocity works
//
//      is it monotonic?
//
//      another observation:
//          if we did the prefix XOR, the incoming x's corresponding bit-th
//          place (bit-th place with a 1) would merely shift the CHANGE in
//          parities earlier
//
// === STILL STUCK ON HOW TO FIND A SUB-QUADRATIC SOLN ===
//
//
//!!!!! EDITORIAL
//!!!!!         PARAGRAPH 1-2
//
//          again, its the msb apparently.
//          if all the values from the right (to left) has the MSB (so far)
//          smaller than x, clearly by the observation of XOR, the MSB of the
//          original x will NOT change until another value with equal MSB come
//          in (then we must shift down OR unless it interacts with multiple
//          bits which is likely)
//
//              PARAGRAPH 3
//          why log(x) times????????? (yes we want, but how???)
//          how log(X) times???
//
//          hypothetical impl.:
//              we record the MSB of every integer
//
//              when an equal MSB is reached [1 1],
//                  check further down until [0 1]
//                  if at any point [1 0] is reached, terminate
//
//              remember, [0 1] is fine but [1 0] is bad where [new weight,
//              running XOR's value]
//
//      (**)    we also would have to keep track of all the changes to the
//              value's smaller places (after [0 1])
//
//         how would range query XOR sum work??? (to make it log(x)??)
//
//         so actually we can keep track all of the change from (**) from our
//         own prior observation of using "range-query XOR" or the prefix XOR as
//         observed before (w/o editorial), so it's a matter of just keeping
//         track of it (implmentation heavy) where we shift down to the next
//         bit-th place at most log(W) times!
//
//         and we can simplify/reduce the implementation by using some 2D-DP to
//         combine the prefix XOR with some indexer
//
//         both the prefix and the indexer can be done before the queries!

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n, q);
  IVLL(a, n); // w

  // vll pxor_a(n, 0);
  vll pxor_a(n + 1, 0);
  pxor_a[n - 1] = a[n - 1];
  ll max_wx = 0;     // ==> we actually need to record the q separately
  max_wx = a[n - 1]; // <<< bug/runtime-error (after several fucking FUCKING
                     // ROUNDS OF CHATGPT)
  DD(i, n - 1) {
    pxor_a[i] = a[i] ^ pxor_a[i + 1];
    max_wx = max(max_wx, a[i]);
  }
  IVLL(x, q); // cin does not care EOL vs spaces
  DBG_ITER(x);

  max_wx = max(max_wx, *max_element(x.begin(), x.end()));

  // INDEXER
  // optimally can just use a SPACE of O(nlogW)
  // NOTICE how SPACE complexity is no longer linear

  // n x log(max(all of w_i,x))
  // ==> time complexity of CONSTRUCTION will be O(nlog(W))
  // notice this 2D"DP" abstractss away the actual computation required for the
  // underlying values but merely--in a rough brute-force way--just redirects
  // the path to search
  //      this also abstracts the query as levels of logs instead of individual
  //      queries or exhaustive linear choices
  ll W = ((ll)log2(max_wx)) + 1; // need to include 0
  vector<vll> indexer(W, vll(n, 0));
  II(i, n) {
    DD(w, W) {
      if (0 < i) {
        if ((ll)log2(a[i]) == w) {
          indexer[w][i] = i;
        } else {
          indexer[w][i] = indexer[w][i - 1];
        }
      } else {
        // i==0
        indexer[w][0] = 0;
      }
      if (w < W - 1) {
        indexer[w][i] = max(indexer[w][i], indexer[w + 1][i]);
      }
    }
  }

  vll scores;
  II(qi, q) {
    ll w = (ll)log2(x[qi]);

    // ~~~ i is the index you LAST ate slime??
    // i is the first index you have NOT eaten the slime
    ll i = n - 1;
    while (i >= 0) {
      i = indexer[w][i];

      // indexer tells us the next index should be i
      // something weird is happening at i
      // do some "special computation" to check for any conditions

      // pxor_a is 1@ so +1 is fine
      if (a[i] > (pxor_a[i + 1] ^ x[qi])) {
        // too large
        // don't eat the slime at i => i
        break;
      } else if (a[i] == (pxor_a[i + 1] ^ x[qi])) {
        // exactly 0 (cannot continue but still include the current)
        // eat the slime at i but don't eat the slime at i-1 => i-1
        // unless it stops at 0 at the last index (but that means dont eat the
        // slime at 0, so let the -1 stay) if (i > 0) {
        //   i--;
        // }
        i--;
        break;
      } else {
        // because of the else-if condition, log2 will never be log2(0)==-inf

        // continue with a new w
        w = (ll)log2(pxor_a[i] ^ x[qi]);
        i--; // ensure to keep the indexer moving

        // this is basically saying please check if we cannot eat the slime
        // starting at index i-1?|
        // indexer will move the index further down as needed
        // but if i-- is -1 (or like we have shown the i==0 is edible then just
        // break it for simplicity sake)

        // if (i > 0) {
        //   i--;
        // } else {
        //   break;
        // }

        // ~~~~and assume we can still eat the slime at i-1
      }
    }
    // if i==-1. it just means eat all
    // if i==0, don't eat one of them
    // so its not max(n-i,n) but n-i-1
    // or max (which we could've just done min for the earlier version)
    scores.PB(max(n - i - 1, 0LL));
    // scores.PB(max(n - i, n));
  }
  OIT(scores);

  // vector<vll> indexer(n, vll(W, 0));
  // vector<vll> indexer(W, vll(n + 1, 0));
  //
  // // II(w, W) {
  // // II(i, n) {
  // II(i, n + 1) {
  //   // go from back to start
  //   // II(i, n) {
  //   DD(w, W) {
  //     // if (i != 0) {
  //     if (0 < i && i < n) {
  //       // (we actually do need some of the actual computation during
  //       // construction as in reference to the prefix XOR)
  //       //
  //       // if the MSB of the w is greater than the current prefix XOR
  //       //  find the earlier index (==> [w][i] = [w][i-1])
  //       // otherwise
  //       //  set the index to the current prefix XOR (==> [w][i] = i)
  //       //      for further computation to decide how many levels to go down
  //       (in
  //       //      w)
  //       //
  //       // ADDITIONALLY, by the properties of XOR,
  //       //      we can do range-query XOR as same as prefix sum because XOR
  //       //      simulatenously describes the ABSOLUTE PARITIES of that bit-th
  //       //      place and the DELTA PARITIES of that bit-th places
  //       //
  //       // so, to find the xor of say from i to i+2 (inclusive)
  //       // we just do prefix_xor[i+2]^prefix_xor[i-1] (since we want to
  //       include
  //       // the i-th number also)
  //       //
  //       // and XOR is symmetric unlike range-query summation (because of
  //       // subtraction)
  //       //
  //       // wait but this needs/assumes the table is constructed
  //       // ~~~~(if we're trying to range query to the front)
  //       //
  //       // how did we do this independently of prefix again?
  //       //
  //       // ~~~but we're range-querying
  //       //
  //       // NONONONON we just check if (ll)log2(a[i]) == w
  //       //
  //       // if so, then assign it =i
  //       // OTHERWISE,
  //       //      re-use the old index (to skip all the redudant will-be eaten
  //       //      slimes AT THE LEVEL w)
  //       //
  //       //
  //       //
  //       // special consideration
  //       //
  //       // if the current condition is met, then all lower msb's
  //       // should take the higher msb's index (because it's also another
  //       // condition where it could be too large)
  //       //
  //       // remember, this table is just a way to check for computation and a
  //       one
  //       // good fact is that it either terminates immediately or move down AT
  //       // LEAST 1 place (reinforcing the logW complexity)
  //
  //       // if (pxor_a[] ^ pxor_a[]) {
  //       // if ((ll)log2(a[i]) != w + 1) {
  //       if ((ll)log2(a[i]) != w) { // since 0..=w we need W+1
  //         indexer[w][i] = indexer[w][i - 1];
  //       } else {
  //         indexer[w][i] = i;
  //       }
  //     } else if (i == 0) {
  //       indexer[w][i] = i;
  //     } else { // i==n
  //       indexer[w][i] = indexer[w][i - 1];
  //     }
  //
  //     // because of this, w should be in the inner loop and w is reversed
  //     if (w == W - 1)
  //       continue;
  //     indexer[w][i] = max(indexer[w][i], indexer[w + 1][i]);
  //   }
  // }
  //
  // vll score;
  //
  // II(qi, q) {
  //   // ll i = n - 1;
  //   ll i = n;
  //   /*     ll w = (ll)log2(pxor_a[i + 1] ^ x[qi]); */
  //
  //   // special, we start with x itself or rather
  //   ll w = (ll)log2(x[qi]);
  //
  //   // while (true) {
  //   while (w >= 0 && i > 0) {
  //     // if w==0:
  //     //        no more levels to explore (w==0 is a sentinel value to denote
  //     //        end of bit-th place since we're doing it 1@)
  //     // if i==0:
  //     //        it's at the very beginning and you simply can't go much
  //     beyond
  //     //        it
  //     //
  //     // if we draw a graph of w=f(i)
  //     //
  //     // w==0 case is when the function graph pre-maturely hits the 0-line
  //     // (i.e., cannot eat all the slimes)
  //     //
  //     // while i==0 means the x can eat all the slimes with still a large
  //     value
  //     // of x still remaining at i==0 (as in despite w>0)
  //     //
  //     // there are cases we're it loops back even when w>0 i>0 (it seems
  //     like)
  //     //
  //     // when it pre-maturely ends (i>0) with a high value (w>0) which is in
  //     the
  //     // cases when during the middle we suddenly increase the weights
  //     //
  //     // but with the new dp = max(dp, dp[w+1])
  //     // this should be handled where w would drop to 0 then (no w would not
  //     // drop; we need to check for the value itself also)
  //
  //     // DBGLN(w, i, indexer[w - 1][i]);
  //     // w = (ll)log2(qi);
  //     // since we changed the pxor_a to include a 0 at the n'th index
  //     // so at the start the computation will be consistent and stay the same
  //     // (elegant)
  //     // w = (ll)log2(pxor_a[i] ^ x[qi]);
  //     // if (w == 0) {
  //     //   break;
  //     // }
  //     //
  //     // per chatgpt: sir, log2(1)==0=w btw (0 is not useless)
  //     // i = indexer[w - 1][i - 1] + 1; // ~~~~ 0@ -> 1@ (do it within pxor)
  //     //                                // now its 0@->1@
  //     i = indexer[w][i - 1] + 1;
  //
  //     // while (w >= 0) {
  //     //   if (i == indexer[w][i]) {
  //     //     w--;
  //     //   } else {
  //     //     break;
  //     //   }
  //     // }
  //
  //     // DBGLN(a[i], pxor_a[i + 1] ^ x[qi]);
  //     // the other missing special computation
  //     // if (a[i] > (pxor_a[i + 1] ^ x[qi])) {
  //     if (a[i - 1] > (pxor_a[i] ^ x[qi])) {
  //       // if (a[i] > (pxor_a[i] ^ x[qi])) {
  //       // i = -1; // denotes we cannot eat the last element
  //       // i++; // we cannot eat the last element (return to the best case
  //       from
  //       // before)
  //       // but i is already 1@
  //       break;
  //     }
  //     // otherwise, w WILL go down (not stay the same)
  //     // because whenever the next i the indexer provides it is EITHER
  //     //      a higher msb
  //     //      OR, the current running x reached to another w with same msb
  //     //
  //     //      we actually want pxor_a[i] because we need the w to go down
  //     //        oxor_a is still 0@ with just a 1-padding at the end (that's
  //     the
  //     //        way to think)
  //     // w = (ll)log2(pxor_a[i + 1] ^ x[qi]);
  //     // w = (ll)log2(pxor_a[i] ^ x[qi]);
  //     // w = ((pxor_a[i - 1] ^ x[qi]) > 0) ? (ll)log2(pxor_a[i - 1] ^ x[qi])
  //     :
  //
  //     // since now w=0 is actually valid value itself we have to do something
  //     // when the XOR=0
  //     //
  //     // in the case of XOR=0, it can still eat the current slime because
  //     wi==wj
  //     // in this case (no i++) but it also cannot continue since 1<=wi by the
  //     // input assumption
  //     if ((pxor_a[i - 1] ^ x[qi]) == 0) {
  //       i--; // because i is 1@ we need to show we take the current index
  //       break;
  //     }
  //     w = (ll)log2(pxor_a[i - 1] ^ x[qi]);
  //
  //     // 0; problem, even though we move w down, we have initialized the
  //     table
  //     // in a way that if indexer calls i AT w, then for any k=1..=w will
  //     also
  //     // call i at that i so we need to i--
  //     if (i > 0)
  //       //
  //       i--;
  //     // in other words, the only case when i becomes 0 is when it is able to
  //     // eat ALL slime
  //     DBGLN(w);
  //     // ll skip_i = indexer[w][i];
  //     // always stop for THE COMPUTATION at ever index from idnexer
  //
  //     // (ll) log2(pxor_a[skip_i] ^ x[i]);
  //   }
  //
  //   // assumes we reached the end or w is prematurely 0
  //   // we now just have an 1@i
  //
  //   // score.PB(pxor_a[i] ^ x[qi]);
  //   // score.PB(n - i - 1);
  //   score.PB(n - i);
  //   // score is the # of slimes eaten not the XOR of whatever
  //   // i is already 1@ while n (length) is 1@
  //   // now i is 0@
  //   //
  //   // anwer is still wrong
  //   // what does i mean here?
  //   //
  //   // in the begininning i==n-1,
  //   //      represents no slimes eaten
  //   //  at the end if i==0,
  //   //          represents all slimes were eaten (INCLUSIVE)
  //   //
  //   //          clearly i is 0@ and we do need -1 but it is better thought of
  //   as
  //   //          n-1 - i rather than n-i - 1 but the score still skips some...
  //   //
  //   //          but, despite n-1, i==0 means 1 slimes were eaten
  //   (inclusitivity)
  //   //          so it should be score=n-i <<<<
  //   //
  //   //          but be careful,
  //   //          sometimes i==0 is set WITHOUT EVEN running the loop
  //   (untested)
  //   //          so need the loop to be i>=0
  //   //              check for case.....
  //   //              no its better to have a sentinel alue i==n to represent
  //   no
  //   //              slimes taken yet
  //   //
  //   //              this requires modifications to the initialization of the
  //   //              table and the rest
  //   //
  //   //              so,
  //   //                      score=n-i
  //   //
  //   //                      but modify the table to start at n itself
  //   //                      AND start the loop at i=n
  // }
  //
  // OIT(score);

  // vll qs;
  // II(_q, q) {
  //   I(x);
  //
  //   ll score = 0;
  //
  //   // O(0);
  //
  //   qs.PB(score);
  //   // output the hypothetical score
  // };
  // OIT(qs);
}
