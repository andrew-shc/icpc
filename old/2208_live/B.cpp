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

void solve([[maybe_unused]] ll T)
{
    READ(n, k, p, m);
    // READ_VLL(a, n);

    ll cost_before = 0;
    ll cost_p = 0;
    ll cost_after = 0;

    // bool p_taken = false;
    bool p_taken_within_k_initially = p < k;
    bool one_kept = false;
    vll a; // maintains k-1 length (where the kth el always gets added and removed on a different index)
    // vll b;
    INC(i, n)
    {
        ll ai;
        cin >> ai;

        if (i == p - 1)
        {
            cost_p = ai;
            // p_taken_within_k_initially = i < k;
        }
        else if (i >= k - 1) // if k == n (ie the entire length is within the window) => p_taken_within_k_init = true and cost_after & before = 0
        {
            a.push_back(ai);

            // BUG: this is net negative of 1 (-1 each time) and @p (we have net 0 already) just like the net 0 # of el changed below
            //   no but if p is within k keep once at most
            if (p_taken_within_k_initially && !one_kept)
            {
                one_kept = true;
                continue; // dont take extra elements (k element originally at this point becomes k-1 when p<k)
            }
            if (i < p - 1)
            {
                cost_before += *min_element(a.begin(), a.end());
                a.erase(min_element(a.begin(), a.end()));
            }
            else
            { // i>p-1
                cost_after += *min_element(a.begin(), a.end());
                a.erase(min_element(a.begin(), a.end()));
            }
        }
        else
        { // ????????????????????/
            a.push_back(ai);
        }
        // if (i <= k)
        // {
        // }
        // else
        // { // i > k
        // }
    }

    // if p_taken_within_k_initially => no cost before
    ll win_cards_num = 0;
    if (cost_before + cost_p <= m)
    {
        win_cards_num++;
        m -= cost_before + cost_p;

        // cost_after + cost_before + cost_p
        win_cards_num += m / (cost_after + cost_before + cost_p);

        OUT(win_cards_num);
    }
    else
    {
        OUT(0);
    }

    // if (p_taken_within_k_initially && cost_p < m)
    // {
    //     win_cards_num++;
    //     m -= cost_p;
    // } else
}