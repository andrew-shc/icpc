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

// O.1: clearly if the sum of distances to move (sum of ai) is less than the distance between p & q => impossible
// Q.2: is there a case where if the sum of the distance is greater than the min. required distance... it is impossible??
//      ..this is on a Euclidean plane (i.e., real number is real; real number exists!)
//      O.2.1: if there's only 1 move and that move is larger than the min. req'd dist. => impossible
//          O.2.1.1: in fact, 1 ai requires that single ai == the req'd dist
//          O.2.1.2: 2 ai => no one side larger than the sum of the other distances + min req'd distance
//          O.2.1.3: 3 ai => ...
// O.3: [MAJOR OBSERVATION] if we treat the line between p<->q as a side of a polygon (including just 2-point polygon)
//      => a list of ai is valid as long no single side is larger than the sum of the other side
//

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ(px, py, qx, qy);
    READ_VLL(a, n);

    // work in squares (to avoid fractionals)
    // WRONG.... when summing the roots vs the summing the squares produce different result in comparison
    //          (only works when we are comparing only two numbers directly)
    // consider 1 1 2
    //      technically wouldve worked, but with squares its 1 1 4 which suggests it doesnt work

    // what we can do is multiply the elements by 10, and have the root be multipled 10...
    //      doing the truncation now can results in error at the boundary again at 0 and 9

    // actually, we only need to compare 1-side (namely >=), not equality, hence this should work fine.

    vector<ld> ald;
    for (ll &el : a)
    {
        ald.push_back((ld)el);
    }
    ald.push_back(sqrtl((px - qx) * (px - qx) + (py - qy) * (py - qy)));

    sort(ald.begin(), ald.end());

    ld second_largest = 0;
    INC(i, n)
    {
        second_largest += ald[i];
    }

    if (second_largest >= ald[n])
    {
        OUT("YES");
    }
    else
    { // if the sum of the sides excluded the largest is less than the largest => impossible
        OUT("NO");
    }
}