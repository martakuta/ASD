#include <iostream>
#include <climits>
using namespace std;

#define LL long long

const int N = 100'005;
int val[N];
LL first_without[N];
LL second_without[N];
LL no_without[N];
LL first_with[N];
LL second_with[N];
LL third_with[N];
LL no_with[N];

int main() {

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    if (n < 4) {
        LL ans = 0;
        for (int i = 0; i < n; i++) {
            ans += val[i];
        }
        cout << ans << "\n";
        return 0;
    }

    first_without[0] = val[0];
    second_without[0] = 0;
    no_without[0] = 0;


    for (int i = 1; i < n; i++) {
        first_without[i] = max(first_without[i-1], no_without[i-1] + val[i]);
        second_without[i] = max(second_without[i-1], first_without[i-1] + val[i]);
        no_without[i] = max(no_without[i-1], first_without[i-1]);
        no_without[i] = max(no_without[i], second_without[i-1]);
    }

    for (int i = 0; i < 5; i++) {
        first_with[i] = 0;
        second_with[i] = 0;
        third_with[i] = 0;
        no_with[i] = 0;
    }

    third_with[2] = second_without[1] + val[2];
    third_with[3] = max(third_with[2], second_without[2] + val[3]);
    no_with[3] = third_with[2];
    first_with[4] = no_with[3] + val[4];
    third_with[4] = max(third_with[3], second_without[3] + val[4]);
    no_with[4] = max(third_with[3], no_with[3]);

    for (int i = 5; i < n; i++) {
        first_with[i] = max(first_with[i-1], no_with[i-1] + val[i]);
        second_with[i] = max(second_with[i-1], first_with[i-1] + val[i]);
        third_with[i] = max(third_with[i-1], second_without[i-1] + val[i]);
        no_with[i] = max(first_with[i-1], second_with[i-1]);
        no_with[i] = max(no_with[i], third_with[i-1]);
        no_with[i] = max(no_with[i], no_with[i-1]);
    }

   /*
    for (int i = 0; i < n; i++)
        cout << first_without[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++)
        cout << second_without[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++)
        cout << no_without[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++)
        cout << first_with[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++)
        cout << second_with[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++)
        cout << third_with[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++)
        cout << no_with[i] << " ";
    cout << "\n";
*/

   LL help1 = max(first_without[n-1], second_without[n-1]);
   LL help2 = max(no_without[n-1], first_with[n-1]);
   LL help3 = max(second_with[n-1], third_with[n-1]);
   LL help4 = max(help3, no_with[n-1]);
   help3 = max(help1, help2);
   help4 = max(help3, help4);

   cout << help4 << "\n";


    return 0;
}