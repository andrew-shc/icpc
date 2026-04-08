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
    // ios_base::sync_with_stdio(false);
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

// rephrase: just make x equal to n given the available operations

// O.1: can we do a certain set amount of operations that makes all x equal to certain constant z
//          and work our way from z to n???
//      O.1.1: setting 0 is not possible due to their case restrictions/constraints
// O.2: worst case on digits... S(S(10^9-1)) = S(9*8) = 7+2 = 9
//          so 2 ops of digits to bring any x to between 1 and 9

// strat
// let z=1

// given 1<=x<=10^9
//  1<=y=S(S(x))<=9 (2 ops)

//  (if y is 1 already, we can ignore it; it'll just be else all the way down)
//  if [ADD -5] y-5:
//      if [ADD -2] y-2:
//         if [ADD -1] y-1: Z
//         else: Z
//      else:
//         if [ADD -1] y-1: Z
//         else: Z
//  else:
//      if [ADD -3] y-3:
//         if [ADD -1] y-1: Z
//         else: Z
//      else:
//         if [ADD -2] y-2: Z
//         else:  (y can still be 2)
//              if [ADD -1] y-1: Z
//              else: Z

// 4 ops total ensuring y is 1 (the z)
// then
// ADD n-1 (since x=1, x=1+(n-1)=n)
// !

// problem, on the 2nd sum, there can be things like 64 can happen... which means we need 3 digits ://
// consider
// S(88 888 888) = 8*8 = 64
// S(64) = 6+4 = 10
// S(10) = 1

// so now given x within 1 to 9, how to do this under 3 operations??? and an additional op to make x->n
//      note: n can be prime so don't try thinking you can multiply your way through (has to be add likely)
// more brute force!! (common its just 9 distinct numbers left)
// 1 = (just itself)
// 2 = 2
// 3 =       3
// 4 = 2,2
// 5 =           5
// 6 = 2,    3
// 7 =             7
// 8 = 2,2,2
// 9 =       3,3
// the execution path =>
// x -> /2 -> /3 -> /5 -> /7

// if we do ADD -5 (can we do it within 2 ops??)
// 1 =
// 2 = 2
// 3 =     3
// 4 = 2 2
// 5 =       5
// 6 = 2   3
// x -> /2? -> /3?
// wait... dude, we can just skip the remaining case and deduct that from the final summation!!!

// 1 = (just itself)
// 2 = 2
// 3 =       3
// 4 = 2,2
// 5 =           5
// 6 = 2,    3
// 7 =             7
// 8 = 2,2,2
// 9 =       3,3
// the execution path
// x -> /2 -> /3? -> /5?  (else, assume x=7 instead of x=1)
//       |     \-> /3?
//       \-> /2? -> /3?
//            |
//            \->  /2?

// per editorial / last hint

// after second digit summation x can be at most 16
// why???
// let's just assume thats the case for now we can do binary search like as follows

// -8? -> -4? -> -2? -> -1? ->
// guarantees 1 regardless in (4 ops)

// per editorial full solution
// it is at most 16 since  IT DOESNT EVEN EXPLAIN
// with at most 10^9 with the largest being 10^9-1 (9999 9999)
// how does one even get 16 from that after 2nd sum???

// S(9+7 or 8+8 or 7+9)=16
// S(9999999) = 97
// S(99999999) = 88 (9*8)
// S() = 79

// bruh 10^9 means 9 zeroes, doesn't mean 9 digits including 1 which would then result in 8 zeros
// so 9*9 exists with it being 81, so 79 exists as the largest 2nd-order digit sum (i.e., 16)

void solve([[maybe_unused]] ll T)
{
    READ(n);
    OUT("digit");
    READ(discard);
    OUT("digit");
    READ(discard3);
    // OUT("digit");
    // READ(discard4);

    OUT("add -8");
    READ(discardA);
    OUT("add -4");
    READ(discardB);
    OUT("add -2");
    READ(discardC);
    OUT("add -1");
    READ(discardD);

    // now the x is between 1 and 9 (limit to 3 ops)
    // now brute force
    // OUT("div 2");
    // READ(respA);
    // if (respA)
    // {
    //     OUT("div 2");
    //     READ(respA);
    //     if (respA)
    //     {
    //         OUT("div 2");
    //         READ(respA);
    //         if (respA)
    //         { // 8?
    //         }
    //         else
    //         { // 4?
    //         }
    //     }
    //     else
    //     {
    //         OUT("div 3");
    //         READ(respA);
    //         if (respA)
    //         { // 6?
    //         }
    //         else
    //         { // 2?
    //         }
    //     }
    // }
    // OUT("div 3");
    // READ(respA);
    // if (respA)
    // {
    //     OUT("div 3");
    //     READ(respA);
    //     if (respA)
    //     { // 9?
    //     }
    //     else
    //     { // 3?
    //     }
    // }

    // OUT("div 5");
    // READ(respA);
    // if (respA)
    // { // 5?
    // }
    // else
    // { // its not /2,/3,nor /5... so it must be /7? but there's still /1....
    // }

    // OUT("add -5");
    // READ(respA);
    // if (respA)
    // {
    // }
    // // now x is within 1 to 5
    // OUT("add -3");
    // READ(respB);
    // if (respB)
    // {
    // }
    // // now x is within 1 to 3
    // OUT("add -1");
    // READ(respC);
    // if (respC)
    // {
    // }
    // // now x is within 1 to 2
    // OUT("add -1");
    // READ(respD);
    // if (respD)
    // {
    // }
    // now is is within 1 to 1 (i.e., x is 1)

    // OUT("add -5");
    // READ(respA);
    // if (respA)
    // {
    //     OUT("add -2");
    //     READ(respB);
    //     if (respB)
    //     {
    //         OUT("add -1");
    //         READ(respC);
    //         if (respC)
    //         { // -5-2-1=-8 (for x=9)
    //         }
    //         else
    //         { // -5-2=-7 (for x=8)
    //         }
    //     }
    //     else
    //     {
    //         OUT("add -1");
    //         READ(respD);
    //         if (respD)
    //         { // -5-1=-6 (for x=7)
    //         }
    //         else
    //         { // -5=-5 (for x=6)
    //         }
    //     }
    // }
    // else
    // {
    //     OUT("add -3");
    //     READ(respE);
    //     if (respE)
    //     {
    //         OUT("add -1");
    //         READ(respF);
    //         if (respF)
    //         { // -3-1=-4 (for x=5)
    //         }
    //         else
    //         { // -3=-3 (for x=4)
    //         }
    //     }
    //     else
    //     {
    //         OUT("add -2");
    //         READ(respG);
    //         if (respG)
    //         { // -2=-2 (for x=3)
    //         }
    //         else
    //         {
    //             OUT("add -1");
    //             READ(respH);
    //             if (respH)
    //             { // -1=-1 (for x=2)
    //             }
    //             else
    //             { // (for x=1)
    //             }
    //         }
    //     }
    // }

    // now x=1

    cout << "add " << n - 1 << endl;
    READ(discard2);
    OUT("!");

    READ(resp);
    return;
}