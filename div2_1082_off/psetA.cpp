#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const long long NEG = (long long)-4e18;

using namespace std;

void solve()
{
    int x, y;
    cin >> x >> y;

    // line test
    if ((y + x) % 3 == 0 && -(float)x / 4.f <= y && y <= (float)x / 2.f)
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
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
