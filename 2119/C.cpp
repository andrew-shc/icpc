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

// lexicographically smallest means earlier elements are smaller and if there are a superset array that also satisfies
//          pick the smallest one (the subset one)
// additionally, we are restricting the length to n

// rephrase: each element has a lower bound l and upper bound r and we want to find the smallest kth element of the n-lengthed array

// O.1: XOR ith bit = 1 (when there are odd 1s), 0 (when there are even 1s)
// O.2: AND ith bit = 1 (only when all bits are 1s)
// O.3: for a given ith bit across elements, AND <=> XOR only when they're all 1s (with odd amount of them)
//              or at least a 0 is present and there are even 1s (i.e., even 0s if n is even or odd 0s if n is odd)
//      O.3.1: only when all n is odd and every element at the ith bit is 1
//              OR if n is even there are even 0s (>=2, ==0 => & results in 1); if n is odd there are odd 0s (>=1)
// O.4: the condition is checked *independently* at each bit i
// O.5: & and ^ operations are commutative (symmetric) in any order even for satisfying the condition
//          => sorting is available to us (from smallest to largest); but also preferably find a way to find the smallest integer
//              first and slowly go to larger integer until we find n integers
//          => probably the latter option is the most viable (l,r,n are very huge)
//          => from l to r

// strat:
//  given n, if n is odd => every bit should be 1 (no 0s) or have odd amount of 0s (>=1) => odd amounts of 0s or zero amount of 0s
//           if n is even => every bit should have even amount of 0s (>=2)

// O.6: if n is odd  => we can have all 0s or 1s at   every bit index
//      if n is even => we can have all 0s       at certain bit index, but even 1s must be present (not all 1s) at the remaining bit index
//                                                               i.e., even 0s or even 1s at every index (except all 1s and no 0s)
//      O.6.1: given n is odd, we can pick any integer between l and r (inclusive) and repeat that n times
//              but since we want the smallest, we can just pick l and repeat that n times
//      O.6.2: given n is even, we can pick the smallest, the l, even times and find the next element along l to r twice
//                  (guaranteeing even 1s or even 0s at every bit index)
//          O.6.2.1: impossible when the range of l to r is only 1
//          O.6.2.2: impossible when n is 2 (all 1s at certain bit index or all 0s at all bit index) (recall 1<=l<=r)
//      O.6.3: since n>=4 is possible, we can always pick the element l and just have the last 2 element be element l+1...?
//              ==> !!!!!~~~~~~~ we have to guarantee all bit indices that has been all 1s are flipped to 0
//                  consider 00001010111010 (l)
//                last 2 els 00010000000000 works (so any integer greater than the double of l works as long it also ensures every all 1-bits are stopped)
//                           00010101000101 works
//                           00010000000001 works
//              how to find the smallest integer x between l<=2*l<=x<=r that satisfies the above condition?
//          O.6.3.1: if r < 2*l => impossible, if r >= 2*l, 2*l is an option that always exist
//      Q.6.4: is there more optimal solution? by definition of lexicographically smallest, the above is the best/optimal per the special ordering required

// refined strat:
//      n is odd  => answer always l
//      n is even => answer always l for k <= n-2 and the specially found smallest integer for k==n-1,n

// refined strat II:
//      n is odd  => l
//      n is even => for k <= n-2: l, for k==n-1,n: 2*l (except r<2*l or n==2)

// per test case
//      if l<=r<2*l:
//          we have to find arrays that are lexicographically larger....
//              consider 00001010111010 (l)  (if we repeat each number twice from the back)
//                       00001010111100
//                       00001011000000
//                       00001100000000
//          yes i was correct, but its not 2*l, its the largest 1-bit x2
//          i.e., log2(l), ceil it, then exponetiate it by 2 so exp(ceil(log2(l)))

void solve([[maybe_unused]] ll T)
{
    READ(n, l, r, k);

    if (n % 2 == 1)
    {
        OUT(l);
    }
    else
    { // n is even
        DBGLN(n, l, r, k, (ll)exp2(ceil(log2l(l))));
        DBGLN(exp2(ceil(log2l(l))), ceil(log2l(l)), log2l(l), l);

        if (n == 2)
        {
            OUT(-1);
        }
        else if (r < (ll)exp2(ceil(log2l(l + 1))))
        // +1 because if l happens to be exactly on the 2 to the power of, it will choose that again when
        // we need to choose different number for the last 2 element
        // (we ALWAYS want the next exponent)
        {
            OUT(-1);
        }
        else if (k <= n - 2)
        {
            OUT(l);
        }
        else
        { // k == n-1,n
            OUT((ll)exp2(ceil(log2l(l + 1))));
        }
    }
}