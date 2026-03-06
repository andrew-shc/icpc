#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef std::vector<ll> vll;

const long long NEG = (long long)-4e18;

#ifdef DEBUG
#define _GLIBCXX_DEBUG
#define _GLIBCXX_DEBUG_PEDANTIC

// Enhanced DBG macro with variable = value format, strings print directly
#define DBGLN(...)                                  \
    do                                              \
    {                                               \
        _dbg_print_vars(#__VA_ARGS__, __VA_ARGS__); \
        std::cout << std::endl;                     \
    } while (0)

// DBG with no newline
#define DBG(...)                                    \
    do                                              \
    {                                               \
        _dbg_print_vars(#__VA_ARGS__, __VA_ARGS__); \
    } while (0)

// Helper to split variable names
std::vector<std::string> _split_vars(const std::string &names)
{
    std::vector<std::string> result;
    std::string current;
    int depth = 0;

    for (char c : names)
    {
        if (c == ',' && depth == 0)
        {
            size_t start = current.find_first_not_of(" \t");
            size_t end = current.find_last_not_of(" \t");
            if (start != std::string::npos)
            {
                result.push_back(current.substr(start, end - start + 1));
            }
            current.clear();
        }
        else
        {
            if (c == '(' || c == '[' || c == '{')
                depth++;
            if (c == ')' || c == ']' || c == '}')
                depth--;
            current += c;
        }
    }

    size_t start = current.find_first_not_of(" \t");
    size_t end = current.find_last_not_of(" \t");
    if (start != std::string::npos)
    {
        result.push_back(current.substr(start, end - start + 1));
    }

    return result;
}

// Print value based on type - strings print directly, others with variable name
template <typename T>
void _dbg_print_single(const std::string &name, T &&t)
{
    if constexpr (std::is_same_v<std::decay_t<T>, std::string> ||
                  std::is_same_v<std::decay_t<T>, const char *>)
    {
        std::cout << t; // Print string directly
    }
    else
    {
        std::cout << name << " = " << t; // Print with variable name
    }
}

template <typename T>
void _dbg_print_values(const std::vector<std::string> &names, int index, T &&t)
{
    if (index < names.size())
    {
        _dbg_print_single(names[index], std::forward<T>(t));
    }
}

template <typename T, typename... Args>
void _dbg_print_values(const std::vector<std::string> &names, int index, T &&t, Args &&...args)
{
    if (index < names.size())
    {
        _dbg_print_single(names[index], std::forward<T>(t));
        if (sizeof...(args) > 0)
            std::cout << ", ";
    }
    _dbg_print_values(names, index + 1, std::forward<Args>(args)...);
}

template <typename... Args>
void _dbg_print_vars(const std::string &var_names, Args &&...args)
{
    auto names = _split_vars(var_names);
    _dbg_print_values(names, 0, std::forward<Args>(args)...);
}
#define DBG_ITER(arr)                                              \
    do                                                             \
    {                                                              \
        _Pragma("GCC diagnostic push")                             \
            _Pragma("GCC diagnostic ignored \"-Wshadow\"")         \
                std::string _dbg_name = #arr;                      \
        cout << std::setw(8) << std::right << _dbg_name << " = ["; \
        bool _dbg_first = true;                                    \
        for (auto &_dbg_x : arr)                                   \
        {                                                          \
            if (!_dbg_first)                                       \
                cout << ", ";                                      \
            cout << _dbg_x;                                        \
            _dbg_first = false;                                    \
        }                                                          \
        cout << "]" << endl;                                       \
        _Pragma("GCC diagnostic pop")                              \
    } while (0)
#else
#define DBGLN(...)
#define DBG(...)
#define DBG_ITER(arr)
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

// 10:33a-11:03a (slept a little in between / ie micro sleeps)

void solve([[maybe_unused]] ll T)
{
    ll n, h, l;
    cin >> n >> h >> l;

    ll mx = max(h, l);
    ll mn = min(h, l);

    ll region1 = 0; // if num is <= mn (can form pairs in region1 & region2)
    ll region2 = 0; // if num is between mn (exclusive) and mx (inclusive) (can form pairs only with other region 1)

    vector<pair<ll, ll>> vpll;
    for (int i = 0; i < n; i++)
    {
        ll ai;
        cin >> ai;
        if (ai <= mn)
        {
            region1++;
        }
        else if (ai <= mx)
        {
            region2++;
        }
    }

    if (region1 >= region2)
    {
        cout << region2 + (region1 - region2) / 2 << endl;
    }
    else if (region1 < region2)
    {
        cout << region1 << endl;
    }
}