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

// rephrasing: we want find at least two elements where they are NOT a co-prime of each other.
// O.1: if every elements are co-prime of each other, we can only increase each element's value to make any
//          2 elements not a co-prime of each other
// sieve? find factors? find frequency of factors across elements?

// wait if the intial condition is not satisfied, we can just have 1 even and 1 odd and add +1 to the odd?
//   if there are 0 even (and all mutually co-prime), add +1 to any 2 odds => gcd of 2?
// H.2: is this optimal? counter-example possible where all odds but you just need 1 ops?
//      take 7, 13  => 8,14 is not optimal BUT 7,14 is (with 1ops insteead of 2)
//      DISPROVEN NOT OPTIMAL
// H.3: brute-force? add 1, check any satisfied. add 1 at another odd, check any satisfied?
//      its doable in a reasonable amount of time
//      Q.3.1: how does one find gcd>1 for any two numbers?
//      O.3.2: each element has a list of factors >1 (we just need an existence of it per element)
//              and if any factors >1 gets hit twice across elements => condition of gcd is satisfied

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_VLL(a, n);
    READ_VLL(b, n); // each increment always has a cost of 1

    // 3*n(sqrt n)

    // at least 2 elements
    // if both are even gcd>1 exists (namely gcd==2)
    // if one odd and other is even and no gcd>1, make *any* odd as even

    // the only hard case:
    // if two odds and gcd==1, 1st make one of odds an even and check per position. if no gcd>1, convert *any* 2nd odd.
    // iterate at each location where we convert that one odd to even and check
    // a hashmap of factors to frequency across element (not by factors frequency within an element / existence per element)
    // ~~~~~ no we still need hashmap~~~~but since we're really just manipulating by existence, we dont need hashmap, just go back to sets
    // ~~~~~ no we can just set ~~~~ where a set per element represents an increase freq. of a factor (we dont care about decrease in freq.)

    // 1 set for all aggregate factors (assume to all exist only within one element)
    // another 1 set per element for all the factors it will additionally add
    // if these elements intersect => cost =1
    // if no elements intersect => cost =2

    ll evens = 0;
    for (auto &el : a)
    {
        if (el % 2 == 0)
        {
            evens++;
        }
    }
    if (evens >= 2)
    {
        OUT(0);
        return;
    }

    DBGLN("+++++", evens);

    // INC(cost, 2 - evens)
    // {
    // DBGLN(cost);

    bool conversion_done = false;
    unordered_set<ll> f1;
    vector<unordered_set<ll>> vf1;

    for (auto &el : a)
    {
        unordered_set<ll> fi;
        unordered_set<ll> vf; // set for factors when the element is incremented by 1

        ll ai = el;
        ll ai1 = el + 1;

        if (el % 2 == 1 && !conversion_done)
        {
            // if element is odd => make it even to prepare for the next iteration (this is last time we'll copy the value within this it.)

            // !!!!!  we got to find a way to optimally find the number to convert even to odd

            el++;

            conversion_done = true;
        }

        for (int i = 2; i * i <= ai; i++)
        {
            while (ai % i == 0)
            {
                ai /= i;
                fi.insert(i);
                if (f1.count(i) == 1)
                { // previous elements has the same factor
                    OUT(0);
                    return;
                }
            }
        }
        if (ai > 1)
        {
            fi.insert(ai);
            if (f1.count(ai) == 1)
            { // previous elements has the same factor
                OUT(0);
                return;
            }
        }

        for (int i = 2; i * i <= ai1; i++)
        {
            while (ai1 % i == 0)
            {
                ai1 /= i;
                if (fi.count(i) == 0)
                { // new factors included that wasnt there before
                    vf.insert(i);
                }
            }
        }
        if (ai1 > 1)
        {
            if (fi.count(ai1) == 0)
            { // new factors included that wasnt there before
                vf.insert(ai1);
            }
        }

        vf1.push_back(vf);
        f1.merge(fi);
    }

    if (evens == 1)
    { // no same factor found but 1 even existed already
        OUT(1);
        return;
    }
    else
    {
        // at this point, there 0 evens. we can use the vf1's to selectively find odd elements to increment to even
        //      NOTE: incrementing even to odd to find shortcut, but at that point you can just find another odd to convert to even
        //              and if there are no odds left to convert to even, that means 2 evens
        // going back...
        // if any element matches, there is an odd that can make gcd>1 at cost of 1. else, cost=2 (since we already checked if gcd>2 exists regardless of evenness)

        for (auto &el : vf1)
        {
            for (auto &f : el)
            {
                if (f1.count(f) == 1)
                { // elements intersect, an element has a factor that is also present in the global
                    OUT(1);
                    return;
                }
            }
        }
    }
    // }

    OUT(2);

    // OUT(2 - evens); // when two elements are converted from odd to even => gcd=2 must exist between these two elements
}