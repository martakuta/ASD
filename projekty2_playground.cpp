#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::sort;
using std::max;

#define LL long long

struct Dane {
    int p; //poczatek przedzialu
    int k; //koniec przedzialu
    int w; //zysk
    LL wynik; //wynik po dynamiku - wpisuje go pole z poczatku
};

struct Konce {
    bool czy_p; //czy jest poczatkiem przedzialu (jesli nie, to jest koncem)
    int id; //jaki ma indeks w tablicy dane
    int pkt; //jaki to punkt na osi czasu wydarzen
};

Dane d[200*1000+5];
Konce k[2*200*1000+5];
LL biore[2*200*1000+5];
LL nie_biore[2*200*1000+5];

bool sort_k (Konce a, Konce b) {
    if (a.pkt < b.pkt)
        return true;
    else if (a.pkt > b.pkt)
        return false;
    else
        return a.czy_p;
}

int main() {

    std::ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> d[i].p >> d[i].k >> d[i].w;
        k[i].czy_p = true;
        k[i].id = i;
        k[i].pkt = d[i].p;
        k[i+n].czy_p = false;
        k[i+n].id = i;
        k[i+n].pkt = d[i].k;
    }
    k[2*n].id = 0;
    k[2*n].pkt = 0;
    k[2*n].czy_p = false;

    sort(k, k+2*n+1, sort_k);
/*
    for (int i = 0; i < n; i++) {
        cout << d[i].p << " " << d[i].k << " " << d[i].w << "\n";
    }
    cout << "\n";
    for (int i = 0; i < 2*n+1; i++) {
        cout << k[i].pkt << " " << k[i].id << " " << k[i].czy_p << "\n";
    }
*/
    biore[0] = 0;
    nie_biore[0] = 0;
    LL max_ost_k = 0, id;

    for (int i = 1; i < 2*n+1; i++) {
        id = k[i].id;
        if (k[i].czy_p) {
            biore[i] = max_ost_k + d[id].w;
            nie_biore[i] = max(biore[i-1], nie_biore[i-1]);
            d[id].wynik = biore[i];
        }
        else {
            biore[i] = d[id].wynik;
            nie_biore[i] = max(biore[i-1], nie_biore[i-1]);
            max_ost_k = max(max_ost_k, biore[i]);
        }
    }
/*
    for (int i = 0; i < 2*n+1; i++) {
        cout << biore[i] << " ";
    }
    cout << "\n  ";
    for (int i = 0; i < 2*n+1; i++) {
        cout << nie_biore[i] << " ";
    }
    cout << "\n";
*/

    cout << max(biore[2*n], nie_biore[2*n]) << "\n";

    return 0;
}