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
  I(n, k);
  IV(a, n);
  ll ind_i = -1;
  ll ind_j = -1;
  ll el_needed = -1;

  // sorted => -1
  // a: 4 3 2 1 0
  // f: 0 0 0 0 5 (we want to maximize the k-th largest one)
  //
  // k=1 => always -1
  // k=2 => if f==n-2 ==> always -1
  //        otherwise ==> move the 0 to the beginnnig?
  //
  // O.1: with single operation, we can ONLY maximally increase by 1 by sorting
  //      it incrementally

  if (k == 1) {
    O(-1);
    return;
  }

  ll largest_kth_max_mex = -1;
  // shhould start with the default ordering (no-op)
  ll default_kth_max_mex = 0;
  vll f;
  II(ii, n) {
    if (a[ii] == default_kth_max_mex) {
      default_kth_max_mex++;

      // count is O(n)
      while (count(a.begin(), a.begin() + ii, default_kth_max_mex) > 0) {
        default_kth_max_mex++;
      }

      // after the jump in MEX
      // then we can start placing them
      // f.PB(default_kth_max_mex);
    }
    // II(jj, ii) {}
    // if (ii == 0 && f.size() == 0) {
    // if no f is submitted yet
    f.PB(default_kth_max_mex);
    // start from somewhere
    // }
  }
  if ((ll)(f.size() - k) < 0) {
    largest_kth_max_mex = f[0];
  } else {
    // DBGLN(f.size() - k, f.size(), k);
    largest_kth_max_mex = f[f.size() - k];
  }

  // excluding kth
  II(i, n) {
    for (ll j = i + 1; j < n; j++) {
      vll local = a;
      swap(local[i], local[j]);
      vll f; // monotonic btw (we can easily make it unique)

      // running mex
      ll running_mex = 0;
      II(ii, n) {
        // if (a[i] == running_mex) {
        // if (*max_element(a.begin(), a.begin() + i) == running_mex) {
        //   running_mex++;
        // }
        if (local[ii] == running_mex) {
          running_mex++;

          // count is O(n)
          while (count(local.begin(), local.begin() + ii, running_mex) > 0) {
            running_mex++;
          }

          // after the jump in MEX
          // then we can start placing them
          // f.PB(running_mex);
        }
        // II(jj, ii) {}
        // if (ii == 0 && f.size() == 0) {
        // if no f is submitted yet
        f.PB(running_mex);
        // start from somewhere
        // }
      }

      // swapped i,j
      // we have the f
      // we get k
      // k is 1@
      // we take f[f.size()-k]
      // if(f.size()-k<0) {
      //   // we take the smallest element??
      // }
      //
      // OK we assume f is n (and is monotonic)
      //
      // it says k-th largest so we assume if f is like f=[1, 100]
      // 2nd or 100th largest element would all be 1

      ll kth_max_mex = 0;
      if ((ll)(f.size() - k) < 0) {
        kth_max_mex = f[0];
      } else {
        // DBGLN(f.size() - k, f.size(), k);
        kth_max_mex = f[f.size() - k];
      }
      DBGLN(i, j, kth_max_mex, largest_kth_max_mex, f.size(), k);

      if (largest_kth_max_mex < kth_max_mex) {
        ind_i = i + 1;
        ind_j = j + 1;
        largest_kth_max_mex = kth_max_mex;
      }
    }

    // if (i < n - k && a[i] <= n - k) {
    //   // good
    // } else if (i < n - k && ind_i == -1) {
    //   ind_i = i + 1;
    // } else if (ind_i != -1 && i >= n - k && a[i] == n - k + 1) {
    //   // because of ==, this can remain -1 which means move all the way to
    //   end ind_j = i + 1; break;
    // }

    // k=1 fine (at the end)
    // k=n fine (whenever 0 is reached or actually when 0 is in the beginning
    // only any 0 outside of 1st index means there will be 0 at the beginning
    // which is unoptimal)
    //
    // k=1 fine (we ALWAYS/INVARIANT get MEX=n at the end)
    // k=n fine (we get MEX=1 in the beginning => MEX>=1 and after)
    // k=n-1 (we get MEX=2 in the 2nd index => MEX>=2 and after)
    // k=2   (we get MEX=n-1 in the second to the last index)
    //
    // fuckign comptue MEX at every index?
    //
    //
    // MEX=1..n (array sorted)
    // MEX=0,n (array sorted opposite way)
    //          5 4 3 2 1 0
    // MEX=0,1,n-1,n (array sorted by one more?)
    //
    //
    //          5 4 3 2 0 1
    //       f: 0 0 0 0 1 6 (brute force it)
    //
    //      if k wants 2nd largest
    //              6 is the largest
    //              5 is impossible (requires [0 1 2 3 4] ~~ordering~~ somewhere
    //              before)
    //
    //              we can swap 1 and 5 but then there's a fucking 5 that makes
    //              a 6 (the end becomes 6 but the element before comes 5)
    //
    //       f: 0 0 0 0 5 6 (but notice if k=n-1 then it would decrease)
    //
    //       f only goes up
    //
    //       the last el of f is always n
    //
    //       0
    //
    //       f: 1 2 3 4 5 6 (sorted)
    //       (we swap 1 element => 1-unordered)
    //          0 1 2 3 4 5
    //          1 0 2 3 4 5
    //          1 2 0 3 4 5
    //          1 2 3 0 4 5
    //          1 2 3 4 0 5
    //          1 2 3 4 5 0
    //       f: 0 2 3 4 5 6
    //       f: 0 0 3 4 5 6
    //       f: 0 0 0 4 5 6
    //       f: 0 0 0 0 5 6
    //       f: 0 0 0 0 0 6
    //
    //          0 1 3 2 4 5
    //          0 1 3 4 2 5
    //          0 1 3 4 5 2
    //
    //       f: 1 2 2 4 5 6
    //       f: 1 2 2 2 5 6
    //       f: 1 2 2 2 2 6
    //
    //
    //      so we can have cases like
    //       f: 1 2 3 4 5 6 (if we want k=2, we get 5)
    //
    //       or (if we increase the elements)
    //       f: 1 2 3 4 5 5 7
    //       f: 1 2 3 4 5 6 7
    //
    //       we do n^2 for swaps
    //       we do n for linear pass to compute MEX?
    //       find k-th largest MEX in f
    //       record the swap if the computed k-th largest MEX is larger than
    //       previous k-th largest MEX
    //
    //       BRUTE FORCE!!
    //
    //       that's assuming we only need 1 ops if 2ops is impossible
    //
    // MEX=0,n (1 is notably missing)
    //
    // 1<k<n weird
    //

    // if (a[i] != i) {
    //   // first unordered
    //   // can be anything
    //   // ind_j must be the original i (which must exist as out of ordered)
    //   //
    //   // el_needed = i;
    //   if (ind_i == -1) {
    //     ind_i = i + 1;
    //     el_needed = i;
    //     // ind_j = n;
    //     // break;
    //   } else if (a[i] == el_needed) {
    //     ind_j = i + 1;
    //     break;
    //   }
    // }
  }

  if (ind_i == -1) {
    O(-1);
  } else {
    // by the properties of swap, if one is out of index, ind_j must exist
    O(ind_i, ind_j);

  }
  // O(-1);
  ;
}
