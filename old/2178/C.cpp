#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

const long long NEG = (long long)-4e18;

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

// start: 14:00
//   end:

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);

    // per editorial

    // MAJOR OBSERVATION: the operation chosen for each child between the first and the unchosen one
    //      are INDEPENDENT of each other
    // think of it like this:
    //      ai is negative? remove on op.2 (-) as a 2nd element
    //      ai is positive? remove on op.1 (+) as a 1st element
    //          MAJOR OBSERVATION: we don't care about a0 (always be added regardless unless the unchosen one)
    //              any future elements that utilizes op.1 will always yield the optimal result of removing a pos. el.
    //              despite not immediately removing the element of interest (i.e., delayed)

    vll before(1, 0);
    deque<ll> after(1, 0);

    // uc for unchosen
    for (int uc = 1; uc < n; uc++)
    {
        if (uc == 1)
        {
            before.push_back(before.back() + a[uc - 1]);
        }
        else
        {
            before.push_back(before.back() + abs(a[uc - 1]));
        }
    }
    for (int uc = n - 2; uc >= 0; uc--)
    {
        after.push_front(after.front() - a[uc + 1]);
    }

    DBGLN(T);
    DBG_ITER(a);
    DBG_ITER(after);
    DBG_ITER(before);

    ll maxX = before[0] + after[0];
    for (int uc = 1; uc < n; uc++)
    {
        maxX = max(maxX, before[uc] + after[uc]);
    }

    OUT(maxX);

    // ll dp[n + 1][n + 1]; // pick 1st vs pick 2nd (in order)
    // vll finalX;

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n - i; j++)
    //     {
    //         if (i == 0 && j == 0)
    //         {
    //             continue;
    //         }

    //         // pick 1st option vs pick 2nd option
    //         dp[i][j] = max(dp[i - 1][j] + a[i], dp[i][j - 1] + a[j]);
    //     }
    // }
}