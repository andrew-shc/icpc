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

// REMEMBER: ITS A PERMUTATION, NOT 1 to n (IE, ANY *ORDER* OF INTEGERS FOR 1..n)

// O.1: at least n ops to cover all the 0s (any 0 still remaining is a missed opportunity to maximize the sum)
// O.2: after applying n, at least each number from 1...n has to occur at least once (incld the lower sub-optimal numbers)
// H.3: col-ops for all n and do n/2 row-ops for the upper portions of the col-ops (where they're all <=n/2)
//          is this THE way to maximize the sum of all numbers in the matrix????
// testcase suspiciously small => easy observations? for a 1600???? (although its 2024)

//          is there a better more optimal construction???
//              since every ops is in terms of rows/cols, we got to think of it in terms of rows/cols => sums of rows/cols
//              now given an initial n col-ops (the other way works also) => from the last row to first row, it goes from n*n to n*1
//              now, at a certain row, it becomes a row sum of <=n*n/2 (remember, the row below is n*(n/2+1)=n*n/2+n>=n*n/2+n/2).
//                  which we can apply a row-op that can yield row-sum of n(n+1)/2=n*n/2+n/2>=n*n/2
//          is there any other combination of ops or permutation that yields better results????
//              is there any secret implied assumption thats not been taken care of????
//                  any other permutation mixes up, preventing a nice compact grouping of the best-half and the worst-half where we can replace the worst-half with something better
//                  any other ordering of the types of ops, preventing a compact ordering that can replace the more worse value from the initial placement with something better (in terms of row/col-sum)
//  i think this is the best way intuitively... not sure if this is even provable

// binary search on answer? dp on answer?
// n<=500, so 2*n <= 1000

// checked WA2 => there seems to be some inaccuracy
//           oh yes of course, if we do -n/2 and +n/2, if n is odd, what happens to the 1?? (in this case, either option works; but we'll just put the one for the row ops since thats easier to impl)
//              if n is odd, it will be just incorporated as an additional one for the col-ops and still leaving the upper half as n/2
//              so the source of error is somewhere else.......... (a better way??)

// per editorial (HINT ONLY): its like an overlapping rows + cols
//      do the last col, then do the next last col, next last row..... purely constructive man....
// 2*n ops
// s = 1 * (2*1-1), 2 * (2*2-1), 3 * (2*3-1), 4 * (2*4-1), ..., n * (2*n-1) = sum of i*(2*i-1)  ~~~~~~~~~~~~ = 2n(n+1)/2-n = n(n+1) - n

void solve([[maybe_unused]] ll T)
{
    READ(n);

    // k=n col-ops + n/2 row-ops

    vll p;
    p.push_back(2);
    p.push_back(0);
    INC(i, n)
    {
        p.push_back(i + 1);
    }

    ll s = 0;
    INC(i, n)
    {
        s += (i + 1) * (2 * (i + 1) - 1);
        // s += n * (n + 1) - 1;
    }

    OUT(s, 2 * n);
    INC(i, n)
    {
        p[1] = n - i;
        p[0] = 2;
        OUT_ITER(p);
        p[0] = 1;
        OUT_ITER(p);
    }

    // n [ n(n+1)/2 - (n/2)(n/2+1)/2 ] + (n/2) [ n(n+1)/2 ]
    // top-half of col-ops   +   n/2 rows of row-ops
    // n*n+n/2 - n*n/(2*2*2) - n/(2*2) + n*n*n/2 + n*n/(2*2)

    // ll offset = 0; // n % 2;
    // ll s = n * ((n * (n + 1)) / 2 - ((n / 2) * (n / 2 + 1)) / 2) + (n / 2 + offset) * ((n * (n + 1)) / 2);
    // // if n is odd, the middle n/2+1 yields n*(n/2+1)=n*n/2+n/2, but compared to n*(n+1)/2=n*n/2+n/2, its the same so no-op
    // OUT(s, n + n / 2);
    // INC(i, n)
    // { // col ops
    //     // vll out;
    //     // out.push_back(2);
    //     // out.push_back(i + 1);
    //     // // 1 to n
    //     // out.insert(out.end(), p.begin(), p.end());

    //     p[1] = i + 1;
    //     OUT_ITER(p);
    // }
    // INC(i, n / 2 + offset)
    // { // row ops (lower half rows)
    //     p[0] = 1;
    //     p[1] = i + 1;
    //     OUT_ITER(p);
    // }

    // output c,i,p1...pn   k times
}