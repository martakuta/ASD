#include <iostream>

using std::cin;
using std::cout;

const int N = 32 * 1024;
const int mod = 1000 * 1000 * 1000;
int d[11][2*N];
int permutacja[N];
int n;

//aktualizuje wartosc w polu p na w oraz aktualizuje wartosci przodkow p
//id - numer drzewa, p - wartosc elementu z permutacji czyli pole do ktorego dodajemy, w - wartosc ktora chcemy dodac
void dodaj(int id, int p, int w) {

    p += n - 1;

    d[id][p] = w;

    while (p > 1) {

        p /= 2;
        d[id][p] = d[id][2*p] + d[id][2*p +1];
        d[id][p] %= mod;
    }
}


int dajSume(int id, int pocz, int kon) {

    pocz += n - 1;
    kon += n - 1;

    int suma = d[id][pocz];
    if (pocz != kon)
        suma += d[id][kon];
    suma %= mod;

    while (pocz/2 != kon/2) {

        if (pocz % 2 == 0) //jesli pocz jest lewym synem
            suma += d[id][pocz+1]; //to dodaje swojego "wewnetrznego" brata
        suma %= mod;
        if (kon % 2 == 1) //jesli kon jest prawym synem
            suma += d[id][kon-1]; //to dodaje swojego "wewnetrznego" brata
        suma %= mod;

        pocz /= 2; //idziemy pietro wyzej
        kon /= 2;
    }
    return suma;
}

int main() {

    int k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> permutacja[i];

    for (int i = 0; i < n; i++) {

        int p = permutacja[i];
        dodaj(1, p, 1);
        //chce policzyc ile jest j=1...i inwersji konczacych sie na p i zaktualizowac te informacje w drzewach
        //bede sumowala j-1 inwersje konczace sie na wartosci w=p+1...n

        for (int j = 2; j <= i+1 && j <= k; j++) {

            int suma;
            if (p < n)
                suma = dajSume(j-1, p+1, n);
            else suma = 0;
            dodaj(j, p, suma);
        }
    }

    int wynik = dajSume(k, 1, n);
    cout << wynik << "\n";

    return 0;
}