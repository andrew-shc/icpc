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
    // strat: 1st pick every jump (sum finite max) then pick the highest delta
    ll n, x;
    cin >> n >> x;

    dll delta;
    dll finite_max; // max jump traversal before the first rollback
    // ll finite_max_all = 0;
    // vll as;
    // vll bs;

    // if (T == 8673)
    //     cout << n << "-" << x << "-";

    for (int i = 0; i < n; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;

        // if (T == 8673)
        //     cout << "|" << a << "-" << b << "-" << c << "-";

        ll d = b * a - c;
        if (d > 0)
        {

            // if there are multiple max deltas, weird things happen
            //   if the magic associated with the FIRST max delta has b=1 (no finite max)
            if (b != 1)
            {

                delta.push_front(d);
                // as.push_back(a);
                // bs.push_back(b);
                finite_max.push_front((b - 1) * a);
            }
            else
            {
                delta.push_back(d);
                // as.push_back(a);
                // bs.push_back(b);
                finite_max.push_back((b - 1) * a);
            }
        }
        x -= (b - 1) * a;
    }

    if (x <= 0)
    {
        // without any rollbacks we are able to reach to x
        cout << 0 << endl;
    }
    else
    {
        // now we have used (b-1) attempts for each jump magic

        if (delta.size() == 0)
        { // no positive delta == any future jumps will only decrease
            cout << -1 << endl;
        }
        else
        {
            // if there's even one => possible

            // somehow balance between highest deltas and highest finite max
            // find the highest finite max <-- will be our final action
            // find the highest delta <-- for reaching to the end

            ll max_fm = *max_element(finite_max.begin(), finite_max.end());
            ll max_d = *max_element(delta.begin(), delta.end());
            ll max_d_fm = finite_max[distance(delta.begin(), max_element(delta.begin(), delta.end()))];
            // ll max_d_b = bs[distance(delta.begin(), max_element(delta.begin(), delta.end()))];
            // ll max_d_a = as[distance(delta.begin(), max_element(delta.begin(), delta.end()))];
            // bool same = distance(delta.begin(), max_element(delta.begin(), delta.end())) == distance(finite_max.begin(), max_element(finite_max.begin(), finite_max.end()));
            // if different, try max delta vs same element (if same element works, we can conserve one rollback)
            // ll max_fm_same = finite_max[distance(delta.begin(), max_element(delta.begin(), delta.end()))];

            // based off of the solution... why not this?
            // i see, if its different finite max thats larger, we would pick that, but it's already picked
            // from the initial removal (we accidentally assumed rollback wont be applied since it was used once
            //   but in reality we are using it twice then)
            // ll strat_max = ((x - max_fm + max_d_fm + max_d - 1) / max_d) + (same ? 0 : 1);

            ll strat_same = ((x + max_d - 1) / max_d);

            DBGLN(x, max_fm, max_d_fm, max_d);
            DBGLN(x, max_d);
            // DBGLN(strat_max, strat_same);

            // cout << min(strat_max, strat_same) << endl;
            cout << strat_same << endl;

            // number of rollbacks from largest delta
            //  find the rollbacks as if we didnt apply the finite maxes as before
            // the >0?1:0
            //  convert the floor to ceil
            // +1 for always using SINGLE largest finite max (since we all used b-1 attempts)
            //  but no +1 if the max finite max is the same skill as for the max delta
            //  since it was included as +max_d_fm when finding the factors of rollback
        }
    }

    // // no positive deltas
    // if (delta.size() == 0)
    // {
    //     if (x <= finite_max_all)
    //     {
    //         cout << 0 << endl;
    //     }
    //     else
    //     {
    //         cout << -1 << endl;
    //     }
    // }
    // else
    // {
    //     ll max_d = *max_element(delta.begin(), delta.end());
    //     ll max_i = distance(delta.begin(), max_element(delta.begin(), delta.end()));
    //     ll max_a = as[max_i];
    //     ll max_b = bs[max_i];

    //     cout << x / max_d + ((x % max_d) > (max_b - 1) * max_a ? 1 : 0) << endl;
    // }
}