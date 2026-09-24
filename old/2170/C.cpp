#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
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
    ((std::cout << args << " "), ...) << std::endl;
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
    ios_base::sync_with_stdio(false);
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

// O.1: scatter plot of (x=qy+r,y) with 0<r<y grouped by q=1,2,3,... reveals that
//      each region grouped by q with r-cone are mutually exclusive (each q produces unique set of qy+r)
//          the r-cone (defined where qy+r where r=1...y-1)
//      since the right part of each r-cone will likely first hit the k-limit, lower q gets higher r
//          O.1.1: THE NEXT Q will START OFF FROM the LAST REMAINING HIGHEST r (hence, two-pointer)
// O.1.2: technically speaking, all r works given any y (already bounded by 1<=r).
//          it's bounded on the right (higher r-val) when it reaches the k-limit => start from the k-limit
// O.1.3: higher q only reduces the right bound of r... do we even need higher q's?
//     O.1.3.1: REMEMBER WE ARE TRYING TO MAXIMIZE OPERATIONS (there are finite qs)
// O.1.4: don't worry about y<x, 1<=r and y in the numerator guarantees the inequality works

// ~~~~~~~~~~~~~~~~~~~~~~~
//          O.1.2: if the current r doesn't work, it has already passed the r-cone => don't try the next r (monotonic)
//              (wont try binary search)

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    READ_VLL(q, n);
    READ_VLL(r, n);

    // nlogn
    sort(q.begin(), q.end());
    sort(r.begin(), r.end());

    ll qi = 0;
    ll ri = n - 1;
    ll max_ops = 0;

    while (ri >= 0 && qi < n)
    {
        // ll y = 2; // must be 2, y=1 => no r (other than 0) exists

        ll y = r[ri] + 1; // also to make the process quicker, start from a valid y given r

        // however, if it works, we don't need to go higher. if it doesn't (only by k-limit => next r)
        //                      r no longer working by k-limit => higher q does not get any better
        // so really y = r[ri]+1 is the only real option.

        // while (true)
        // {
        if (q[qi] * y + r[ri] <= k)
        {
            // found valid q,r pair
            ri--;
            qi++;
            max_ops++;
        }
        else
        {
            // exceeded the k-limit
            // next r
            // keep q
            ri--;
        }
        //     y++;
        // }
    }

    OUT(max_ops);
}