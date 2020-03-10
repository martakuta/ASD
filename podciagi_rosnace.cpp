#include <iostream>
using namespace std;

int tab[1'000'005];
int sufix2[1'000'005];
int sufix3[1'000'005];

int main() {

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }

    long long wynik = n; // n to sa podciagi 1-elementowe

    //zliczanie podciagow 2-elementowych
    long long ile2 = 0, ile3 = 0;

    for (int i = n-1; i >= 0; i--) {
        if (tab[i] == 1) {
            wynik += ile2 + ile3;
        }
        else if (tab[i] == 2) {
            wynik += ile3;
            ile2++;
        }
        else { //  if (tab[i] == 3)
            ile3++;
        }
    }

    //zliczanie podciagow 3-elementowych
    long long ile1 = 0, ile12 = 0;

    for (int i = 0; i < n; i++) {
        if (tab[i] == 1) {
            ile1++;
        }
        else if (tab[i] == 2) {
            ile12 += ile1;
        }
        else { //  if (tab[i] == 3)
            wynik += ile12;
        }
    }

    cout << wynik << "\n";

    return 0;
}