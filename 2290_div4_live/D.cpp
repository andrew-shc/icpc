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
  vpll ap;                                                                     \
  for (ll i = 0; i < n; i++) {                                                 \
    ll ai, bi;                                                                 \
    std::cin >> ai >> bi;                                                      \
    ap.push_back({ai, bi});                                                    \
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
// basically you want to make the vector reflection-invariant
//      and find any values that maps to a key and decrement it
//
// clearly max_ops = 25
//
// also if odd ignore the middle element
//
// you do a sort of like a two pointer and find the largest and find how many
// times it takes to make them match to the smallest of the pair
//
// clearly, in cases like
//      bbde
//
//      where two pairs b<->e and b<->d
//
//          we can just make e,d->b
//
//      zzde?
//      z,e  and z,d
//
//      z must be both d and e
//
//      z must be d (and e can be converted to d)
//
//
//      so basically for any pairs or any connections (graph????)
//      we want to find the minimum char that satifies all
//
//      we have a charmap of say
//          vector<char> of 26 chars -> min char
//
//          min_ops = sum of the differences for each charmap
//
//      say z,e and z,d
//
//      we find z must be d
//      (how do we find e must be d??)
//
//      we just replace the character mapping for that to be z???
//          no reverse map the z (before it) to e??
//
//      also be careful with cases like
//
//      zzwwyycaabbc
//
//      its graphs...
//      z <-- c
//      z <-- b (c <-- z)
//      w <-- b
//      w <-- a (b <-- a)
//      y <-- a
//      y <-- c (a <-- c)
//
//      all characters starts with mapping to itself
//      if it finds a pair that is smaller, it should map to the smaller
//      if it finds a pair that is bigger, the bigger should map to the smaller
//
//      at the end, find until the lowest character is found
//
//      then, for each character compute the difference (operations) needed to
//      reach to the target
//
//      then, compute it with a "dot product" against the frequencies of each
//      characters
//
//
// dijkstra on char mapping????
//
// dsu on characters???
//
// we can just join these cycles easily by pointing to the same lower characters
//
// just do it honestly
//
// MST???
//
// like greedy towards the nearest lowest character???
//
//  a,c   b,d
//
//  a,c   b,c
//
//  a,b   b,b
//
//  a,a   a,a
//
//
//  vs
//
//
//  a,c   b,d
//  a,b   b,d
//  a,a   a,d
//
//  abdc
//  abdb
//
// NOTICE: it crosses path <==> bad? (but also makes it run in less ops??)
//
//          like cascading down
//
//          (if paired)
//
//          if we do this what about cases like
//
//          aaza   ???
//
//          how do we ensure a<-z???
//
//          boolean/flag 1-cost path?
//
//          boolean as a way to merge paths???
//
//          a true ==> +1 cost
//
//          and crossing path is greedy
//
// MISREAD QUESTION: replace ALLLLLLLLLLLL OCCURENCES (counts as 1 ops)

// LLONG_MAX, LLONG_MIN
const ll MOD = 998244353;

void solve([[maybe_unused]] ll T) {
  //
  // START ACTUAL CODE
  //
  ;
  I(n);
  IS(s);

  vll a;
  II(i, n) { a.PB(s[i] - 'a'); }

  vll mapping(26, 0);
  II(i, 26) { mapping[i] = i; }

  DBGLN("===");
  DBG_ITER(mapping);

  vll freq(26, 0);

  II(i, n) { freq[a[i]]++; }

  // find the first-ordered mapping
  // n/2 works since we can ignore the middle one if its odd
  II(i, n / 2) {
    // pairs = { a[i],  a[n-1-i] }

    // case: zzzyx => 1 (when it should be 2 clearly)
    // iti s getting overwritten
    //
    // need to check if a[i] < mapping also (and for other case also)
    //
    // if mapping[a[n-1-i]] < a[i]
    //      then it should NOT be written to something higher
    // otherwise:
    //
    // oh way this is supposed to be compared with mapping on ONE of the sides?
    //
    // in this sense if the two pairs are already mapped to something lower but
    // their current representation in the identity-space is higher then don't
    // change it clearly

    if (a[i] < mapping[a[n - 1 - i]]) {
      mapping[a[n - 1 - i]] = a[i];
    } else if (mapping[a[i]] > a[n - 1 - i]) {
      mapping[a[i]] = a[n - 1 - i];
    } // if same (==), doesn't matter (status quo)

    // if (a[i] < a[n - 1 - i]) {
    //   mapping[a[n - 1 - i]] = a[i];
    // } else if (a[i] > a[n - 1 - i]) {
    //   mapping[a[i]] = a[n - 1 - i];
    // } // if same (==), doesn't matter (status quo)
  }

  DBG_ITER(mapping);

  // resolve the first-ordered mapping to the lowest
  II(i, 26) {
    ll cur = mapping[i];
    while (mapping[cur] != cur) {
      cur = mapping[cur];
    }
    // continues when mapping[cur] == cur
    mapping[i] = cur;
  }

  DBG_ITER(mapping);

  vector<bool> bool_map(26, false);
  // first one 'a' is always false

  II(i, 26) {
    // mapping[i] -> the lowest denominator (inclusive)
    // II(j, mapping[i] + 1) { bool_map[j] = true; };

    if (i == 0) {
      continue;
    }
    for (ll j = i - 1; j >= mapping[i]; j--) {
      bool_map[j] = true;
    }
  }
  // bool_map[0] = false;

  DBG_ITER(bool_map);

  ll min_ops = 0;
  /*   II(i, n) { min_ops += a[i] - mapping[a[i]]; } */
  // II(i, 26) { min_ops += i - mapping[i]; }

  II(i, 26) { min_ops += (bool_map[i] ? 1 : 0); }

  O(min_ops);
  ;
}
