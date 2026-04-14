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

#define INC(i, n) \
    for (ll i = 0; i < n; i++)

#define DEC(i, n) \
    for (ll i = n; i >= 0; i--)

#define OUT_ITER(a)                 \
    {                               \
        for (auto &el : a)          \
        {                           \
            std::cout << el << " "; \
        }                           \
        std::cout << std::endl;     \
    }

template <typename... Args>
void cout_vars(Args... args)
{
    ((std::cout << std::fixed << std::setprecision(10) << args << " "), ...) << std::endl;
}
#define OUT(...) \
    cout_vars(__VA_ARGS__)

#define READ_S(s) \
    string s;     \
    cin >> s;

#define READ_VLL(a, n)         \
    vll a;                     \
    for (ll i = 0; i < n; i++) \
    {                          \
        ll ai;                 \
        std::cin >> ai;        \
        a.push_back(ai);       \
    }

template <typename... Args>
void read_vars(Args &...args)
{
    (std::cin >> ... >> args);
}
#define READ(...)   \
    ll __VA_ARGS__; \
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

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// END MACROS ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void solve(ll T);

int main()
{
    /////////////////////////////////////////////////////////////////////
    //// comment out the sync when working with interactive problems ////
    /////////////////////////////////////////////////////////////////////
    ios_base::sync_with_stdio(false);
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////

    cin.tie(NULL);
    cout.tie(NULL);

    ll T = 1;

    cin >> T;

    ll t = T;
    while (t--)
    {
        solve(T - t);
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// START ACTUAL CODE ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

// start:
//   end:

// rephrase: given a list of *distinct* ai, you can +d (for any arbitrary non-negative d)
//              => get the two ai's that produces the largest gcd

// P.0: the array a is orderless and unique (set/unordered_set)

// O.1: since each elements are distinct, the largest GCD possible for any given two elements
//      is when y=2x s.t. gcd(x,2x) = x
//      i.e., the second element is the double of itself
//          O.1.1: this means the largest element has try be the twice of any other previous element
//          O.1.2: but does not have to be the largest element also....
// O.2: the largest GCD possible for given two elements from the entire array a:
//          is when the difference x-y (x larger, y smaller) is the largest, allowing gcd(x+d,y+d)=x-y where

// strat
//  if there exists an element that is <= the half of the largest (or 2*smaller <= the largest)
//      => output the element + d (where d=largest - 2*smallest)
//  if all the remaining elements are larger than the half of the largest
//      =>

// H.3: its the largest - smallest (the largest difference)
//          consider ai is the smallest and aj is the largest of an array
//              or    x                      y
//      GCD(d+x,d+y) = y-x (s.t. y>x)
//      this suggests
//          y-x|d+x and y-x|d+y
//          (y-x)k=d+x, (y-x)l=d+y
//          yk-xk=d+x, yl-xl=d+y
//          yk-x(k+1)=d, y(l-1)-xl=d
//          yk-x(k+1) = y(l-1)-xl
//          yk-xk-x=yl-y-xl
//          0=yl-y-xl-yk+xk+x
//          0=x-y+xk-xl+yl-yk
//          0=x-y+x(k-l)+y(l-k)
//          0=x(k-l+1) + y(l-k-1)
//          0=x(k-l+1) - y(k-l+1)
//              if x == y (largest), then we can add infinite amount of d to get infinitely large GCD
//              if x != y, 0=x(k-l+1) - y(k-l+1)=(x-y)(k-l+1)
//                  to satisfy this constraint, k-l+1=0
//                      k=l-1
//                  additional requirements, we need to have d>=0, so additional constraints below
//                      yk-x(k+1)>=0, y(l-1)-xl>=0 (solve for k,l)
//                      yk-xk-x>=0 => yk-xk>=x => k(y-x)>=x => k >= ceil( x/(y-x) )
//                      yl-y-xl>=0 => l(y-x)>=y =>             l >= ceil( y/(y-x) )
//
//                  which proves *existence* of d nonetheless where we can find a GCD of y-x always given the largest and the smallest
//  what about higher GCD like y-x+1?
//      idk just by intutiont, it's not

// greatly helped from observing the given testcases

// per editorial

// gcd(a,b)=c => a and b are multiples of c => we want gcd(a+d,b+d)=diff (i.e., a+d and b+d should be multiples of diff)
//      hence, we chose d s.t. a+d is multiple of diff, and b+d=a+diff+d=a+d+diff is clearly also multiple of diff
//          => d = (-x) mod diff
//              this means how much number want to add to x s.t. x becomes a next multiple of diff
//      and we are asked for the best gcd, so we find the max(a) and min(a) something like that

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    sort(a.begin(), a.end());

    OUT(a[n - 1] - a[0]);
}
