#include <iostream>

using std::cin;
using std::cout;

int t[1000 * 1000 + 5];
int kp[1000 * 1000 + 5];

int main() {

    /* NOTATKI z zajęć
     *
     * jeśli przykład w zadaniu jest za prosty, to albo nie da się wymyślić trudnego
     * albo że twórcy zadania chcieli coś ukryć
     *
     * dla 5; 5 4 3 2 1 istnieją wszystkie krawędzie i jest jedna spójna składowa
     * dla 5; 1 2 3 4 5 nie istnieje żadna krawędź i jest 5 spójnych składowych
     * dlatego nie możemy rozpatrywać wszystkch istniejących krawędzi, bo skoro jest 10^6 wierzchołków
     * to by było ich rzędu 10^12
     *
     * spójne składowe zawsze będą przedziałami,
     * np 6; 3-1-2, 4, 6-5
     *
     * jak znajdować te przedziały?
     * na bieżąco trzymamy maksimum i wiemy że musimy zająć wszystkie indeksy aż do
     * tego o numerze maksimum (a jeśli idąc do niego po kolejnych indeksach znajdziemy
     * nowe maksimum, to idziemy jeszcze dalej); i tak aż do momentu kiedy jesteśmy
     * na indeksie 'i' oraz nasze maksimum wynosi 'i' (to przy indeksowaniu od 1)
     *
     */

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        kp[i] = 0;
    }

    int ile = 0, elty = 0, maxi = 0;
    for (int i = 1; i <= n; i++) {
        elty++;
        if (t[i] > maxi)
            maxi = t[i];
        if (i == maxi) {
            ile++;
            kp[i] = elty;
            elty = 0;
        }
    }

    cout << ile << "\n";
    for (int i = 1; i <= n; i++) {
        if (kp[i] > 0) {
            cout << kp[i] << " ";
            for (int j = i - kp[i] + 1; j <= i; j++)
                cout << j << " ";
            cout << "\n";
        }
    }


    return 0;
}