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

void solve([[maybe_unused]] ll T)
{
    ll n;
    string s;
    cin >> n;
    cin >> s;

    // bool zero_prev = true;
    // bool zero_prevprev = true;
    ll max_one = 0;
    ll min_one = 0;
    ll delta_one = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '1')
        {
            max_one++;
            delta_one++;

            if (i >= 2 && s[i - 2] == '1' && s[i - 1] == '0')
            {
                max_one++;
                delta_one++;
            }
        }
        else if (i >= 1 && s[i - 1] == '0' && s[i] == '0')
        {
            // a break in 1s
            if (delta_one <= 2)
            {
                min_one += delta_one;
            }
            else
            {
                // delta one minus # of optimal 0s
                min_one += delta_one - (delta_one - 1) / 2;
            }

            delta_one = 0;
        }
    }
    // a break in 1s at the end ( we don't care if its one or two zeros)
    //  actually always compute it at the end
    if (delta_one <= 2)
    {
        min_one += delta_one;
    }
    else
    {
        // delta one minus # of optimal 0s
        min_one += delta_one - (delta_one - 1) / 2;
    }

    // for (auto &c : s)
    // {

    //     DBGLN("=");
    //     DBGLN(min_one, max_one, delta_one, zero_prev);
    //     if (c == '1')
    //     {
    //         max_one++;
    //         delta_one++;

    //         if (zero_prev && !zero_prevprev)
    //         {
    //             max_one++;
    //             delta_one++;
    //         }
    //     }
    //     else if (c == '0' && !zero_prev)
    //     {
    //         zero_prev = true;
    //     }
    //     else if (c == '0' && zero_prev)
    //     {
    //         zero_prevprev = true;
    //         zero_prev = true;
    //     }
    //     else
    //     {
    //         // c == 0 && zero_prevprev

    //         if (delta_one <= 2)
    //         {
    //             min_one += delta_one;
    //         }
    //         else
    //         {
    //             // delta one minus # of optimal 0s
    //             min_one += delta_one - (delta_one - 1) / 2;
    //         }
    //     }

    //     DBGLN(min_one, max_one, delta_one, zero_prev);
    // }
    // if (!zero_prev)
    // {
    //     if (delta_one <= 2)
    //     {
    //         min_one += delta_one;
    //     }
    //     else
    //     {
    //         // delta one minus # of optimal 0s
    //         min_one += delta_one - (delta_one - 1) / 2;
    //     }
    // }

    cout << min_one << " " << max_one << endl;
}