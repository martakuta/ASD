#include <iostream>
using namespace std;

int l[500'005];
long long t1[10];
long long t2[500'005][10];

int main() {

    int n, nr;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> l[i];
    }

    for (int i = 1; i <=10; i++) {
        t1[i] = 0;
        t2[0][i] = 0;
    }

    long long wynik = 0;

    for (int j = 1; j <= n; j++) {
        nr = l[j];
        wynik += t2[j-1][nr];
        for (int i = 1; i <= 10; i++) {
            t2[j][i] += t2[j-1][i];
            if (nr + i <= 10)
                t2[j][nr + i] += t1[i];
        }
        t1[nr]++;
    }

    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 10; j++) {
            cout << t1[i][j] << "/" << t2[i][j] << " ";
        }
        cout << "\n";
    }
     */

    cout << wynik << "\n";

    return 0;
}