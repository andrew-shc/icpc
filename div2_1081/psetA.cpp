#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>
#include <unordered_map>
#include <functional>
#include <array>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

using namespace std;

int main()
{
    int t;
    cin >> t;
    vector<ll> results(t);
    for (int test_case = 0; test_case < t; ++test_case)
    {
        int n;
        cin >> n;

        bool duplicate = false;

        ll blocks = 1;

        string char_i;
        string char_f;
        string current;

        string s;
        cin >> s;

        for (int i = 0; i < n; ++i)
        {
            string x(1, s[i]);

            if (i == 0)
            {
                char_i = x;
                current = x;
                continue;
            }
            else if (i == n - 1)
            {
                char_f = x;
            }

            if (x != current)
            {
                // different block
                current = x;
                blocks++;
            }
            else
            {
                // same block
                duplicate = true;
            }
        }

        if (char_i == char_f)
        {
            // first and last same character, we can't increase the blocks
            duplicate = false;
        }

        // cout << duplicate << endl;

        results[test_case] = blocks + (duplicate ? 1 : 0);
    }

    for (const auto &res : results)
    {
        cout << res << endl;
    }
    return 0;
}
