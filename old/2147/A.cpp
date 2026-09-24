#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

const long long NEG = (long long)-4e18;

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

// rephrase:
//      you are given two number line x & y
//      you increase x and y in an alternating fashion starting with x
//      you want the increment to match the the final x & y-pos with each subsequent step increasing in length
//      x,y>0

// consider x=5,y=3
// 1,3,4... any more optimal or alternative steps? => optimal step is not just increasing the length by the minimum (ie 1)

// consider x=60,y=35  // smaller steps
// 10,15,20,25,30
// 1,35,59 <--?

// O.1: geometrically, you can never reach x==y since y0>x0 and x1>y0 suggesting the slope can never be =1 (didnt say x==y is impossible).
//      (what a useless observation)

// per editorial

// you guess the cases and that other edge cases are impossible :(((

// but important insight: k>3 jumps/moves can always be reduced to the base cases
// proof: given ANY possible jumps to (x,y) via...
//      x1<y1<x2<y2<x3<y3<x4<y4
//      since x3<y3 => x3+x4 < y3+x4
//      since x4<y4 => x3+x4 < y3+y4 (and hence, the last two steps can be merged, same thing can be applied with x is at the end)
//      reducing to the 3 base cases shows that case x==y and other edge cases fails.

// SUMMARY: START PROVING CONSTRUCTIVE GREEDY ON A (THE GREEDY UNINTUITIVE THAT IS SIMPLE)
//      THIS PROBLEM A CANNOT BE RELIED ON SIMPLE OBSERVATIONS LIKE O.1,
//      CONSIDER PROVING PER EDITORIAL
//          IN THIS CASE, WE START WITH PROVING FOR ALL POSSIBLE CASES AND REDUCE IT DOWN TO FEW BASE CASES THAT JUST REQUIRES
//          CONDITION CHECKING

void solve([[maybe_unused]] ll T)
{
    READ(x, y);

    if (x == 0 || y == 0)
    {
        OUT(1);
    }
    else if (x < y)
    { // strat go x, then go y
        OUT(2);
    }
    else if (x - 1 > y && y >= 2)
    { // strat put x with 1, then put y, then put the remaining of x
        OUT(3);
    }
    else
    { // if x-y=1 => impossible?, x==y => impossible???? how do i prove them????
        OUT(-1);
    }
}