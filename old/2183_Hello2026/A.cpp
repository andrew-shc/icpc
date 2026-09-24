#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef std::vector<ll> vll;
typedef std::deque<ll> dll;

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

// start: 16:02
// end: 16:34

void solve([[maybe_unused]] ll T)
{
    DBGLN(T);
    ll n;
    cin >> n;

    bool all_one = true;
    bool zeros_left = false;
    bool zeros_right = false;
    for (int i = 0; i < n; i++)
    {
        ll ai;
        cin >> ai;
        all_one &= ai == 1;
        if (i == 0)
        {
            zeros_left = ai == 0;
        }
        if (i == n - 1)
        {
            zeros_right = ai == 0;
        }

        DBGLN(i, all_one, zeros_left, zeros_right);
    }

    DBGLN(all_one, zeros_left, zeros_right);

    if (all_one)
    {
        cout << "Alice" << endl;
        return;
    }
    if (zeros_left && zeros_right)
    {
        cout << "Bob" << endl;
    }
    else
    {
        cout << "Alice" << endl;
    }

    // 0 = Alice wins
    // 1 = Bob wins

    // if all ai is 1, then Alice wins in one step
    // if any ai is 0 (otherwise), Alice must try to make it all 1
    //   if a group of 0 is on the left or right or neither, pick the opposing side (or any side)
    //     with the rest except the other end make it into 1 1 (Alice must win)
    //   if groups of 0s are on both ends.... next round must contain a 1 and a 0 (or risk becoming 1 <-- Bob wins)
    //     --> however, if 1 & 0 must exist next round optimally, Bob must win
}