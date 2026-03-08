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
    ll n, m, l;
    cin >> n >> m >> l;

    // smallest to largest (order doesnt matter across animaltronics)
    // vll danger_levels(m, 0);
    ll prev_ai = 0;
    // ll remainder = m; // pre fill remainder happens first1
    ll increment = 0;

    map<ll, ll> freq_map;
    freq_map[0] = m;

    if (freq_map.empty())
    {
        cout << "?????????????????????????????????? " << m << endl;
        return;
    }

    // if (T == 60)
    // {
    //     cout << n << "-" << m << "-" << l << "-";
    // }

    DBGLN(T);
    // DBG_ITER(danger_levels);
    for (int kkk = 0; kkk < n; kkk++)
    {
        if (n - kkk + 1 < m)
        {
            ll num_to_be_removed = m - (n - kkk + 1);

            if (freq_map.empty())
            {
                cout << "WTF?? x22222 ????????????????? " << kkk << endl;
                return;
            }

            while (num_to_be_removed--)
            {
                ll smallest_key = freq_map.begin()->first;
                if (freq_map[smallest_key] <= 1)
                {
                    freq_map.erase(smallest_key);
                }
                else
                {
                    freq_map[smallest_key]--; // we can ignore an animal tronic thats already the smallest (pointless to increase)
                    //   if the number of remaining flashes is < the m
                }
            }
        }

        // ll prev_remainder = remainder;
        // // ll prev_inc = increment;

        // ll ai;
        // cin >> ai;
        // increment = ai - prev_ai;

        // // m-remainder remaining remainders to go

        // // DBGLN(">>>>>", increment);

        // for (int j = prev_remainder; j < m; j++)
        // {
        //     if (increment == 0)
        //     {
        //         break;
        //     }
        //     danger_levels[j]++;
        //     increment--;
        // }

        // // DBGLN("<<<<<", increment);

        // ll factor = increment / m;
        // remainder = increment % m;

        // for (int j = 0; j < m; j++)
        // {
        //     danger_levels[j] += factor + ((j < remainder) ? 1 : 0);
        // }

        // // finished pre filling dangers

        // // begin danger subtraction

        // // end

        // prev_ai = ai;

        ll ai;
        cin >> ai;
        increment = ai - prev_ai;

        // if (T == 60)
        // {
        //     cout << ai << "|";
        // }

        // sort(danger_levels.begin(), danger_levels.end());

        // compute the frequency map
        // for (auto &d : danger_levels)
        // {
        //     if (freq_map.count(d))
        //     {
        //         freq_map[d]++;
        //     }
        //     else
        //     {
        //         freq_map[d] = 1;
        //     }
        // }

        if (freq_map.empty())
        {
            cout << "WTF?? x22222" << endl;
            return;
        }

        vector<ll> val;  // must always be present
        vector<ll> freq; // must always be present
        for (auto &p : freq_map)
        {
            val.push_back(p.first);
            freq.push_back(p.second);
        }
        // DBG_ITER(val);
        // DBG_ITER(freq);
        // DBGLN(increment);

        for (int i = 0; i < val.size() - 1; i++)
        {
            ll fill = (val[i + 1] - val[i]) * freq[i];
            if (fill <= increment)
            {
                increment -= fill;

                // increment larger than fill
                // merge smaller older val[i] with val[i+1]

                freq_map.erase(val[i]);
                // DBGLN(freq[i]);
                freq_map[val[i + 1]] += freq[i];
                freq[i + 1] += freq[i];
            }
            else
            {
                // increment smaller than fill
                // remove old val[i] & freq[i] with...
                // => new val[i]+increment/freq[i] @ freq=m-remainder
                // =>   & val[i]+increment/freq[i]+1 @ freq=remainder
                //  guarantee the new value not to exceed val[i+1]

                ll factor = increment / freq[i];
                ll remainder = increment % freq[i];

                freq_map.erase(val[i]);
                freq_map[val[i] + factor] = freq[i] - remainder;
                if (remainder > 0)
                {
                    freq_map[val[i] + factor + 1] = remainder;
                }

                increment = 0;

                break;
            }
            // DBGLN(increment);
        }
        if (increment > 0)
        { // still some remaining increment after the last and largest index
            ll I = val.size() - 1;

            ll factor = increment / freq[I];
            ll remainder = increment % freq[I];

            // DBGLN(">>>>", factor);
            // DBGLN(">>>>", remainder);

            freq_map.erase(val[I]);
            freq_map[val[I] + factor] = freq[I] - remainder;
            if (remainder > 0)
            {
                freq_map[val[I] + factor + 1] = remainder;
            }
        }

        // vector<ll> val1;
        // vector<ll> freq1;
        // for (auto &p : freq_map)
        // {
        //     val1.push_back(p.first);
        //     freq1.push_back(p.second);
        // }
        // DBG("> ");
        // DBG_ITER(val1);
        // DBGLN("");
        // DBG("> ");
        // DBG_ITER(freq1);
        // DBGLN("");

        prev_ai = ai;

        // reset largest danger level
        // danger_levels.erase(max_element(danger_levels.begin(), danger_levels.end()))

        if (freq_map.empty())
        {
            cout << "WTF?? x2" << endl;
            return;
        }

        ll largest_k = freq_map.rbegin()->first;
        // replace the largest key with 0
        // freq_map.erase(largest_k);

        if (freq_map[largest_k] > 1) // max key always present, but enough to prevent it being removed?
        {
            freq_map[largest_k]--;
        }
        else
        { // = 1 => becomes 0 so none
            freq_map.erase(largest_k);
        }

        if (freq_map.count(0) > 0) // 0 key present?
        {
            freq_map[0]++;
        }
        else
        {
            freq_map[0] = 1;
        }

        // DBG_ITER(danger_levels);
    }

    // vector<ll> val;
    // vector<ll> freq;
    // for (auto &p : freq_map)
    // {
    //     val.push_back(p.first);
    //     freq.push_back(p.second);
    // }
    // DBG_ITER(val);
    // DBG_ITER(freq);

    if (!freq_map.empty())
    {
        // if (T == 60)
        // {
        //     cout << freq_map.rbegin()->first + (l - prev_ai); // << endl;
        // }
        // else
        // {

        cout << freq_map.rbegin()->first + (l - prev_ai) << endl;
        // }
    }
    else
    {
        cout << "WTF??" << endl;
        return;
    }
}

/*
1
1 4 4
4

*/