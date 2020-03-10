#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int ceny[n];
    for (int i=0; i<n; i++)
        std::cin >> ceny[i];

    long long suf[n];
    suf[n-1] = ceny[n-1];
    for (int i=n-2; i>=0; i--)
        suf[i] = suf[i+1] + ceny[i];

    int np_lewo[n], np_prawo[n], p_lewo[n], p_prawo[n];

    np_lewo[0] = 0;
    p_lewo[0] = 0;
    for (int i=1; i<n; i++) {
        if (ceny[i-1] % 2 == 1) {
            np_lewo[i] = ceny[i-1];
            p_lewo[i] = p_lewo[i-1];
        }
        else {
            p_lewo[i] = ceny[i - 1];
            np_lewo[i] = np_lewo[i - 1];
        }
    }

    if (ceny[n-1] % 2 == 1) {
        np_prawo[n-1] = ceny[n-1];
        p_prawo[n-1] = 0;
    }
    else {
        np_prawo[n-1] = 0;
        p_prawo[n-1] = ceny[n-1];
    }

    for (int i=n-2; i>=0; i--) {
        if (ceny[i] % 2 == 1) {
            np_prawo[i] = ceny[i];
            p_prawo[i] = p_prawo[i+1];
        }
        else {
            p_prawo[i] = ceny[i];
            np_prawo[i] = np_prawo[i+1];
        }
    }

    int m;
    std::cin >> m;

    for (int i=0; i<m; i++) {
        int ile;
        std::cin >> ile;

        long long suma_najw = suf[n-ile];
        if (suma_najw % 2 == 1) {
            std::cout << suma_najw << "\n";
        }
        else if (np_prawo[n-1] == 0 && np_lewo[n-1] == 0) {
            std::cout << "-1\n";
        }
        else if (ile == 1) {
            if (ceny[n-1] % 2 == 0)
                std::cout << np_lewo[n-1] << "\n";
            else
                std::cout << np_prawo[n-1] << "\n";
        }
        else if (ile == n) {
            if (suf[0] % 2 == 1)
                std::cout << suf[0] << "\n";
            else
                std::cout << "-1\n";
        }
        else {
            long long wynik1 = suf[n-ile], wynik2 = suf[n-ile];
            if (np_lewo[n-ile] != 0 && p_prawo[n-ile] != 0)
                wynik1 = suf[n-ile] + np_lewo[n-ile] - p_prawo[n-ile];
            if (p_lewo[n-ile] != 0 && np_prawo[n-ile] != 0)
                wynik2 = suf[n-ile] + p_lewo[n-ile] - np_prawo[n-ile];

            if (wynik1 < wynik2) {
                long long pom = wynik1;
                wynik1 = wynik2;
                wynik2 = pom;
            }
            if (wynik1 % 2 == 1)
                std::cout << wynik1 << "\n";
            else if (wynik2 % 2 == 1)
                std::cout << wynik2 << "\n";
            else
                std::cout << "-1\n";
        }

    }

    return 0;
}