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

// O.1: if there is a group of >=2 rabbits => always a valid arrangement (create a 2-loop and have all side rabbits point to it)
// O.2: if there is a pair of 1-rabbit groups separate by a pair of flower-potted pots => valid
//      O.2.1: if a 1-rabbit group separated by a pair of flower still remains (if their is a chain of them) => invalid
//          O.2.1: if there's a 1-rabbit group at the border that could've formed a pair => form a pair => valid
//          O.2.2: rephrase: allow a single unit 1-rabbit "pair" at the border
// O.3: if a 1-rabbit group is separated by two-lengthed potted pots => that rabbit always invalid
//      O.3.1: separate the cases into subgroups of pair-chains (where at most 1-lengthed potted pots separate them)

// my solution feels so brute force and un-elegant. if this passes, editorial better provides a better more elegant way

// redo
// O.4: if xx00xx, regardless if we can form a pair on either side, 00 always work as a wildcard
//   O.4.1: all >=2 rabbits group can be shortened to a wildcard group (i.e. W)
//   O.4.2: border can be thought of as a wildcard (can be standalone also)

//  W101W   (yes)
//  1101010111 (no)
//  1101W10111 (works; in fact if (# of Ws to replace pre-existing 0) > 0 all works)
// (MAJOR OBSERVATION) O.5: if a W is present in a pair-chain, regardless the amount of pair => always work

void solve([[maybe_unused]] ll T)
{
    READ(n);
    READ_S(s);

    if (n <= 2)
    {
        OUT("YES");
        return;
    }

    bool W_present = false; // W present in the current chain group
    ll zeros = 0;
    for (int i = 2; i < n; i++)
    {
        if ((s[i - 2] == '1' && s[i - 1] == '0' && s[i] == '1'))
        {
            zeros++;
        }
        else if ((s[i - 2] == '0' && s[i - 1] == '0' && s[i] == '1') ||
                 (s[i - 2] == '1' && s[i - 1] == '0' && s[i] == '0') ||
                 (s[i - 2] == '0' && s[i - 1] == '0' && s[i] == '0') ||
                 ((s[i - 2] == '0' && i == 2) || (s[i] == '0' && i == n - 1)))
        {
            W_present = true;
        }

        if ((s[i - 2] == '0' && s[i - 1] == '1' && s[i] == '1') ||
            (s[i - 2] == '1' && s[i - 1] == '1' && s[i] == '0') ||
            (s[i - 2] == '1' && s[i - 1] == '1' && s[i] == '1'))
        { // new chain group

            if (!W_present && (zeros % 2 == 1))
            {
                OUT("NO");
                return;
            }

            W_present = false;
            zeros = 0;
        }
    }

    // treat the end as another chain group
    if (!W_present && (zeros % 2 == 1))
    {
        OUT("NO");
        return;
    }

    OUT("YES");
    return;

    // bool partial_2len = false; // rabbit with 2 1's behind
    // // ~~~~~ default to true if there's only one rabbit that's also happen to be at the end
    // // DBGLN("???", s, n);
    // for (int i = 2; i < n; i++)
    // {
    //     // DBGLN(((s[i - 2] == '0' && s[i - 1] == '1' && s[i] == '1') && partial_2len));
    //     // DBGLN(i, s[i - 2], s[i - 1], s[i], partial_2len);
    //     if ((s[i - 2] == '1' && s[i - 1] == '1' && s[i] == '0') ||
    //         (s[i - 2] == '1' && s[i - 1] == '0' && s[i] == '1' && i == 2))
    //     {                        // rabbit!
    //         partial_2len = true; // implicitly includes when its the last 3 (border 0 is fine)

    //         // DBGLN("A");
    //     }
    //     else if (s[i - 2] == '0' && s[i - 1] == '1' && s[i] == '0')
    //     { // rabbit pair!
    //         // treat the pair as filled ONLY when the first 0 is not the initial 0 (since initial 0 can serve dual purpose to be used as a pair or by itself)
    //         if (i != 2)
    //         {
    //             s[i - 2] = '1'; // <-- for visualization purposes
    //             s[i] = '1';     // <-- important part
    //         }
    //         partial_2len = false;
    //         // DBGLN("B");
    //     }
    //     // rabbit adjacent of each other will always be available to us (they form 2-loop or bigger loop with a pair)
    //     else if ((s[i - 2] == '0' && s[i - 1] == '0' && s[i] == '1') ||
    //              (s[i - 2] == '1' && s[i - 1] == '0' && s[i] == '0') ||
    //              (s[i - 2] == '0' && s[i - 1] == '0' && s[i] == '0'))
    //     {
    //         partial_2len = false;
    //         // DBGLN("C");
    //     }
    //     else if (((s[i - 2] == '0' && s[i - 1] == '1' && s[i] == '1') && partial_2len) ||
    //              (s[i - 2] == '1' && s[i - 1] == '0' && s[i] == '1' && (((i == n - 1) && partial_2len))))
    //     {
    //         OUT("NO");
    //         return;
    //     }
    // }

    // OUT("YES");
    // return;
}

/*

8
3
000
3
001
3
010
3
011
3
100
3
101
3
110
3
111

8
4
0000
4
1111
4
0110
4
0101
4
1010
4
1011
4
1101
4
1001

3
6
110011
8
11100111
8
11000011


10
10
1111111111
10
0000000000
10
0101010101
10
1010101010
10
0101010111
10
1010101011
10
1101010111
10
1010101111
10
1101010011
11
10101011001



*/