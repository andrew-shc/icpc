#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

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

// rephrase: answer is over the space of number of *good* unique subsets of indices

// ~~~~~~ O.1: n!+1 (the max answer / including the empty set)
//      no permutation (this suggests we have to pick subset of n-length but order doesnt matter), think in chooses nCr???
//      both permutation and choose requires a 2nd parameter about # of elements to choose, but we want all possible elements always
// O.1: 2^n (whether to flip/arrange at each crosses)
// O.2: if a subset S is good, its inverse is also good (symmetry)
//      O.2.1: input constraint => at least 2 good subset
//      O.2.2: 2^(k+1) where k is the number of parallel-crosses
///         parallel crosses can be thought of as the index at the end of each parallel crosses have
//          2 choices of prior subsegments that satisfies the non-descending condition (which we means given an initial good subset
//               we can alter the existence of an index of a set giving us additional unique arrangements)
// O.3:

/// honeslty just gonna wing it and check editorial if my observation is valid

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);
    READ_VLL(b, n);

    if (n == 1)
    {
        OUT(2);
        return;
    }

    ull good_subsets = 1;    // by O.2.1
    ll parallel_crosses = 1; // 1 initial parallel-crosses from input constraint
    INC(i, n - 1)
    {
        ll arrangements = 0;
        // by O.2.1: at least 1 arrangement is possible at every quad
        if (a[i] <= a[i + 1] && b[i] <= b[i + 1])
        { // parallel
            arrangements++;
        }
        if (a[i] <= b[i + 1] && b[i] <= a[i + 1])
        { // cross
            arrangements++;
        }

        if (arrangements == 2)
        {
            parallel_crosses++;
        }
    }

    DBGLN(parallel_crosses);
    INC(i, parallel_crosses)
    {
        good_subsets = good_subsets * 2 % MOD;
    }

    OUT(good_subsets % MOD);
}

/*

2
7
1 2 3 4 5 6 7
1 2 3 4 5 6 7
7
1 1 1 1 1 1 1
1 1 1 1 1 1 1


128  // it's not 2^x, it's n! remember?
128

// should test for integer limits also

1
70
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1



*/
