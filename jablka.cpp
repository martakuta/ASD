#include <iostream>
using std::cin;
using std::cout;

int dane[1000*1000+5][2];
long long tab[1000*1000+5];
const long long mod = 1000*1000*1000;

int main() {

    int n, d;
    cin >> n >> d;

    for (int i = 1; i <= n; i++) {
        cin >> dane[i][0];
        cin >> dane[i][1];
    }

    for (int i = 1; i <= n; i++)
        tab[i] = 0;

    for (int i = 1; i <= d; i++) {
        for (int j = n; j >= 1; j--) {
            tab[j] = tab[dane[j][0]] + tab[dane[j][1]] + 1;
            tab[j] %= mod;
        }
        tab[0] = 1;
    }

    long long ile_zebrano = tab[n];

    tab[0] = 1; // z galezi 0 zawsze jest jedno jablko
    for (int i = 1; i <= n; i++) {
        tab[i] = tab[dane[i][0]] + tab[dane[i][1]] + 1;
        tab[i] %= mod;
    }

    long long ile_wszystkich = tab[n];

    long long wynik = ile_wszystkich - ile_zebrano;
    wynik %= mod;
    wynik += mod;
    wynik %= mod;

    cout << wynik << "\n";

    return 0;
}