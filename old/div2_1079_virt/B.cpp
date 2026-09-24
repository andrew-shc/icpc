#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

#define DBG(...)                                     \
    do                                               \
    {                                                \
        std::cout << "[" << #__VA_ARGS__ << "] = ["; \
        _dbg_print(__VA_ARGS__);                     \
        std::cout << "]" << std::endl;               \
    } while (0)

template <typename T>
void _dbg_print(T &&t) { std::cout << t; }

template <typename T, typename... Args>
void _dbg_print(T &&t, Args &&...args)
{
    std::cout << t << ", ";
    _dbg_print(args...);
}
#define DBG_ITER(arr)           \
    do                          \
    {                           \
        cout << #arr << " = ["; \
        bool _dbg_first = true; \
        for (auto &x : arr)     \
        {                       \
            if (!_dbg_first)    \
                cout << ", ";   \
            cout << x;          \
            _dbg_first = false; \
        }                       \
        cout << "]" << endl;    \
    } while (0)

using namespace std;

void solve(ll T);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll T = 1;

    cin >> T;

    while (T--)
    {
        solve(T);
    }

    return 0;
}

void solve(ll T)
{
    ll n;
    cin >> n;

    vector<ll> p;
    vector<ll> a; // reduced version of a

    for (ll i = 0; i < n; i++)
    {
        ll pi;
        cin >> pi;
        p.push_back(pi);
    }
    for (ll i = 0; i < n; i++)
    {
        ll ai;
        cin >> ai;
        if ((i == 0) || (a.back() != ai))
        {
            a.push_back(ai);
        }
    }

    ll p_counter = 0;
    bool failed = false;
    for (auto &ai : a)
    {
        while (p[p_counter] != ai)
        {
            p_counter++;

            if (p_counter >= n)
            {
                failed = true;
                break;
            }
        }

        if (failed)
            break;
    }

    if (failed)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
    }
}