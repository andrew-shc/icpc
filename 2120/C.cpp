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

// rephrase: can we find a tree with n nodes s.t. each node's smallest-labelled ancestor (including itself)
//           sums to m? (given any arbitrary root node)
//           where each node is arbitrary labelled 1 to n (uniquely once)

// O.1: smallest sum is n (where we let the root be 1 letting each n nodes' divineness be 1)
// O.2: largest sum is n(n+1)/2 since going from largest node to the smallest, the next node
//          has to be one less, and we can't place that lesser node in front of a greater node
//              (since then the greater node will have a lower divineness)
//          so we add next node successively (as a child or as a sibling) in a decreasing order
//              => n,n-1,n-2,3,2,1
// O.3: given a skinny tree, n,n-1,n-2,etc... if we swap any two adjacent elements like n,n-2,n-1,etc..
//          the divineness of n-2 stays the same while the divineness of n-1 becomes n-2 (i.e., lost one divineness)
//          so we can finely reduce the total divineness of a tree (i.e., proof by roughly induction)
// O.4: per O.1,O.2: any m not in [n,n(n+1)/2] is impossible and (per O.3) any m in the interval is possible.
// O.5: per O.1,O.2,O.3: we can simplify the problem to a skinny tree (strict 1 parent 1 child relationship)

// (assuming a is the largest and z is the smallest)
//  a,b,c,d,e  m
//  a,c,b,d,e  m-1
//  a,c,d,b,e  m-2
//  a,c,d,e,b  m-3
//   ^^ scrap the above try again with a

// where x is that max and m is what we want
//             a-> b-> c-> d->
//  a,b,c,d,e  x
//  b,a,c,d,e  x-1
//  b,c,a,d,e  x-2 x-1
//  b,c,d,a,e  x-3 x-2 x-1
//  b,c,d,e,a  x-4 x-3 x-2 x-1 => (15 max)-4-3-2-1 = (15 max)-10 = 5 (the min)

// x-4-3-2-1 = m
// -4-3-2-1 = m-x
// 4+3+2+1? 4+3+1? = x-m
// easier way?

// since there are n nodes, we can try starting with the largest node (current node y)
//       and see if putting it at the end meets m or not which will reduce it by (y-1) or gain by y-1
// the moment reduction exceeds x-m (the needed reduction), we can finely place where the the node y should be
// and fill the rest in order

// ->->->->->
// a,b,c,d,e
// b,c,d,e,a -4
// c,d,e,b,a -3
// d,e,c,b,a -2
// e,d,c,b,a -1

// then we can serialize the output from the vector as a[0] being root and printing as a[0] a[1] ; a[1] a[2] ; etc..

void solve([[maybe_unused]] ll T)
{
    READ(n, m);

    ll x = (n * (n + 1)) / 2;
    if (n <= m && m <= x)
    {
        if (n == 1)
        {
            OUT(1);
            return;
        }

        ll a[n] = {}; // the skinny tree (all 0)
        ll reduction_needed = x - m;
        ll last_node;
        for (ll y = n; y >= 2; y--)
        { // current node y
            last_node = y;
            if (reduction_needed - (y - 1) > 0)
            { // the current node y is not enough to reduce the divineness to the needed number m
                reduction_needed -= y - 1;
                a[y - 1] = y;
            }
            else if (reduction_needed - (y - 1) < 0)
            { // the incoming node y is enough but overshoots the needed reduction
                a[reduction_needed] = y;
                break;
            }
            else
            { // reduction matched on the gaussian summation basis (right enough)
                // that's when the incoming node y JUST MATCHED nicely with the reduction needed BUT HASN"T BEEN ADDED YET
                a[y - 1] = y;
                break;
            }
        }

        ll cnt = last_node - 1;
        for (ll &el : a)
        {
            if (el == 0)
            {
                el = cnt;
                cnt--;
            }
        }

        OUT(a[0]);
        INC(i, n - 1)
        {
            OUT(a[i], a[i + 1]);
        }
    }
    else
    {
        OUT(-1);
    }
}

/*

3
1 1
1 2
1 3

1
-1
-1

*/