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

// rephrase: 2^k , 2^k => x, 2^(k+1)-x  (symmetric)
// Op1: c/2 , v+c/2
// Op2: c+v/2 , v/2

// example results
//      c/4, v+c/2+c/4
//      c/2+(v+c/2)/2 = v/2+3c/4 , (v+c/2)/2 = v/2+c/4

// O.1: 2^k is even
// O.2: Since 2^(k+1) is even, Chocola and Vanilla must have both evens or both odds
//      O.2.1: => the final operation can be even or odd but INTERMEDIATE operations must
//                  have both start with even (if any number is odd, that's the final op)
// O.3: an operation yields both ODDs if the person's amount of cake only has a factor of 2 left
// O.4: after 1 ops => halves are present, after 2 ops => quarters are present, after n ops => 1/(2^n) are present

// brute force?

// x = 1101
// 10000
// 10000

// 11000
//  1000

//  1100
// 10100

// another case

//  1111111110
//          10
// if we halve the top and add it to the bottom
//   111111111
//  1000000001

//  1111101110
//          10
//     -->
//   111110111
//   111111001

// per 0.2.1, we cant do any more ops (so beware of the odd at the end)

// O.5.1: >>1 (for halving)
// O.5.2:

// per editorial: backtracking

//  1101

// claude:

// another key observation: since we start with exponentials of 2
//          halving and summing is a matter of increasing or decreasing the exponent
// another key observation: if a number is < 2^k, the last operation had the corresponding person
//          of the number give AWAY (since we start 2^k each and the opposing operation will always result in >2^k)

void solve([[maybe_unused]] ll T)
{
    READ(k, x);

    ull chocola = x;
    ull vanilla = (1ULL << (k + 1ULL)) - x;
    ull half = 1ULL << k;

    vll ops;
    // backtracking iteration (simple reverse greedy)
    while (chocola != vanilla)
    {
        if (chocola < half)
        {
            // previously, chocola MUST HAVE gave half away to vanilla
            vanilla -= chocola;
            chocola *= 2;
            ops.push_back(1);
        }
        else
        {
            chocola -= vanilla;
            vanilla *= 2;
            ops.push_back(2);
        }
    }

    reverse(ops.begin(), ops.end());

    OUT(ops.size());
    OUT_ITER(ops);
}