#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

using namespace std;

void solve()
{
    int n;
    cin >> n;
    string X;
    cin >> X;

    if (n % 2 == 1)
    {
        if (X[0] == 'b')
        {
            cout << "NO" << endl;
            return;
        }
        else
        {
            // n--;
        }
    }

    for (int i = n % 2; i < n; i += 2)
    {
        if (X[i] == '?' || X[i + 1] == '?')
        {
            continue;
        }
        if (X[i] == X[i + 1])
        {
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;
    return;
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
