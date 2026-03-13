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

// grossly misunderstood the question as something like having all multiples present/constructed in b
// and somehow minimizing the number of elements in b
// instead of having all multiples present in a itself again (reflexive)

// optimizations that removed TLE
//  instead of checking over each divisors from a mapping of possible remaining multiples
//  check from all the possible multiples by querying a map if it exists (the key)
//  use map to record visited or not (erasing elements from set is too slow)

void solve([[maybe_unused]] ll T)
{
    READ(n, k);
    map<ll, bool> a1; // per editorial, visited (internally ordered)
    INC(i, n)         // n
    {
        ll a1i;
        cin >> a1i;
        a1[a1i] = false; // logn
    }
    // b itself and number of multiples remaining
    unordered_set<ll> b;
    // ll total_r = 0; // we know a's are gauranteed to be within [1,k]
    auto a1it = a1.begin();
    while (a1it != a1.end())
    {
        ll a1i = a1it->first;
        if (b.count(a1i) == 0 && !a1[a1i])
        {
            b.insert(a1i);

            for (int i = a1i; i <= k; i += a1i)
            {
                if (a1.count(i) == 0)
                {
                    OUT(-1);
                    return;
                }
                else
                {
                    // a1.erase(i); // removes the new divisor from the set
                    a1[i] = true;
                }
            }

            // total_r += k / a1i - 1;
            // a1.erase(a1.begin()); // removes the new divisor from the set
        }

        a1it = next(a1it);

        // while (a1.size() > 0)
        // {
        //     bool why_complicated = true;
        //     // remove multiples of pre-existing smaller divisors of a
        //     // for (auto &[el, r] : b)
        //     for (auto &el : b)
        //     {
        //         ll a1i = *a1.begin();
        //         if (a1i % el == 0)
        //         { // an element from a is divisible by previous smaller a
        //             total_r--;
        //             why_complicated = false;
        //         }
        //     }

        //     if (why_complicated)
        //     {
        //         break;
        //     }
        //     else
        //     {
        //         a1.erase(a1.begin());
        //     }
        // }

        // the next *a1.begin() is not a multiple of any pre-exsiting smaller divisor a
    }

    // if (total_r > 0)
    // {
    //     // still remaining multiples missing
    //     OUT(-1);
    //     return;
    // }

    cout << b.size() << endl;
    for (auto &el : b)
    {
        cout << el << " ";
    }
    cout << endl;
}