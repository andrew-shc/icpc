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

// remember, we gotta connect them but not exceeding the 3-rule
// O.1: only possible shapes (assuming they meet the connectivity requirements)
/*

  nil   dot   line staircase square
 ..... ..... ..... ..... .....
 ..... ..... ..... .*... .....
 ..... ..*.. ..*.. .**.. .**..
 ..... ..... ..*.. ..**. .**..
 ..... ..... ..... ..... .....

*/

//      O.1.1: if there is a square, then the only fill celled is the one and only square
//      O.1.2: if there is a staircase, there can be at most one staircase
//          O.1.2.1: a staircase consists of two lines at same slope but off by 1 vertically (or horizontally)
//      O.1.3: if there is no square, don't make a square

// basic facts: quadratic fine, connected on four faces only (no corners)
// O.3: if any cells fail the 3-rule, return NO

// comment this doesnt seem to be that hard?

void solve([[maybe_unused]] ll T)
{
    READ(n);
    vector<pair<ll, ll>> pos;

    ll square_checker[n] = {0};
    bool has_square = false;

    // ll filled = 0;
    INC(row, n)
    {
        READ_S(s);

        INC(col, n)
        {
            if (s[col] == '#')
            {
                square_checker[col]++;
                pos.push_back(make_pair(col, row)); // (x,y)
                if (col > 0 && square_checker[col] == 2 && square_checker[col - 1] == 2)
                {
                    has_square = true;
                }
            }
            else if (square_checker[col] > 0)
            {
                square_checker[col] = 0;
            }
        }

        // filled += count(s.begin(), s.end(), '#');
    }

    if (has_square)
    {
        if (pos.size() == 4)
        {
            OUT("YES");
        }
        else
        {
            OUT("NO");
        }
        return;
    }
    if (pos.size() <= 1)
    { // 0 (just add 1 #),1 (auto satisfies) #'s
        OUT("YES");
        return;
    }
    if (pos.size() == 2)
    { // 2 filled cell between can be a single line of any slope
        // on the faces, at most one distance away
        // on the corners, any distance away

        // ll m = (pos[0].second - pos[1].second) / (pos[0].first - pos[1].first);
        if (abs(pos[0].first - pos[1].first) + abs(pos[0].second - pos[1].second) <= 1)
        { // on the faces, at most 1 unit away
            OUT("YES");
            return;
        }
    }

    // all the special cases removed to reduce the problem to just fitting two lines of m=+/- 1 (pos or neg slope)
    // + additional observation: these two lines are one unit apart and same slope (which constitutes a valid staircase)

    // pick an initial filled cell called C (creating an m=+1/-1 slope line set by C called C line)
    //      => check how many cells lies on the C line offset by 1
    //      => if all the cell (pos.size()) lies on one of the two in either the pos or neg C line => works; otherwise, no

    ll c0x = pos[0].first;
    ll c0y = pos[0].second;

    // y = x + b => y-x = b_pos, b_pos +/- 1
    // y = -x + b => y+x = b_neg, b_neg +/- 1

    ll b_pos = c0y - c0x;
    ll b_neg = c0y + c0x;

    ll bucket_cl_pos_top = 0;
    ll bucket_cl_pos_equ = 0;
    ll bucket_cl_pos_btm = 0;
    ll bucket_cl_neg_top = 0;
    ll bucket_cl_neg_equ = 0;
    ll bucket_cl_neg_btm = 0;

    for (auto &[x, y] : pos)
    {
        if (y - x == b_pos + 1)
            bucket_cl_pos_top++;
        if (y - x == b_pos)
            bucket_cl_pos_equ++;
        if (y - x == b_pos - 1)
            bucket_cl_pos_btm++;

        if (y + x == b_neg + 1)
            bucket_cl_neg_top++;
        if (y + x == b_neg)
            bucket_cl_neg_equ++;
        if (y + x == b_neg - 1)
            bucket_cl_neg_btm++;
    }

    if (bucket_cl_pos_top + bucket_cl_pos_equ == pos.size() ||
        bucket_cl_pos_btm + bucket_cl_pos_equ == pos.size() ||
        bucket_cl_neg_top + bucket_cl_neg_equ == pos.size() ||
        bucket_cl_neg_btm + bucket_cl_neg_equ == pos.size())
    {
        OUT("YES");
    }
    else
    {
        // failed to model any possible lines
        OUT("NO");
    }
}