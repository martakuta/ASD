#include <iostream>
using std::cin;
using std::cout;

long long dp[1005][1005][2];
int a[1005];
const int mod = 1000*1000*1000;

int main() {

    int n;
    cin >> n;
    for (int i=0; i<n; i++)
        cin >> a[i];

    for (int i=0; i<n; i++) {
        dp[1][i][0] = 1;
        dp[1][i][1] = 0;
    }

    for (int len=2; len<=n; len++) {
        for (int beg=0; beg<=n-len; beg++) {

            if (a[beg] < a[beg+1])
                dp[len][beg][0] += dp[len-1][beg+1][0];
            dp[len][beg][0] %= mod;
            if (a[beg] < a[beg+len-1])
                dp[len][beg][0] += dp[len-1][beg+1][1];
            dp[len][beg][0] %= mod;

            if (a[beg+len-1] > a[beg+len-2])
                dp[len][beg][1] += dp[len-1][beg][1];
            dp[len][beg][1] %= mod;
            if (a[beg+len-1] > a[beg])
                dp[len][beg][1] += dp[len-1][beg][0];
            dp[len][beg][1] %= mod;
        }
    }
    long long wynik = dp[n][0][0] + dp[n][0][1];
    wynik %= mod;
    cout << wynik << "\n";

/*    for (int beg=0; beg<n; beg++) {
        for (int len = 1; len <= n; len++) {
            cout << dp[len][beg][0] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    for (int beg=0; beg<n; beg++) {
        for (int len = 1; len <= n; len++) {
            cout << dp[len][beg][1] << " ";
        }
        cout << "\n";
    }
*/
    return 0;
}