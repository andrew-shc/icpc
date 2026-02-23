#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

using namespace std;

// useful abstractions
// ordering of the binaries doesn't matter
// notion of even flips is NO-OP and odd flips is FLIP
// holding a character of a group of character offsets the same group of character flip by one

// if we have even 0s and even 1s => holding all 1s => KEEP 0s and FLIP 1s
//            even 0s and  odd 1s => impossible
//             odd 0s and even 1s => holding all 0s => KEEP 0s and FLIP 1s
//             odd 0s and  odd 1s => holding all 0s => KEEP 0s and FLIP 1s

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> s0;
    vector<int> s1;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0')
        {
            s0.push_back(i + 1);
        }
        else
        {
            s1.push_back(i + 1);
        }
    }

    if (s0.size() % 2 == 1)
    {
        cout << s0.size() << endl;
        if (!s0.empty())
        {

            for (int i : s0)
            {
                cout << i << " ";
            }
            cout << endl;
        }
    }
    else if (s0.size() % 2 == 0 && s1.size() % 2 == 0)
    {
        cout << s1.size() << endl;
        if (!s1.empty())
        {

            for (int i : s1)
            {
                cout << i << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << -1 << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll T = 1;

    cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}
