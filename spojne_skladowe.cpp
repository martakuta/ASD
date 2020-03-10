#include <iostream>
using namespace std;

#define LL long long

LL tab[1000'005];
LL rep[1000'005];
LL pot[35];
LL repG[35];

LL find(LL a) {
    if (repG[a] == a)
        return a;
    else
        return repG[a] = find(repG[a]);
}

void onion(LL a, LL b) {
    if (repG[a] != repG[b])
        repG[find(b)] = find(a);
}

int main() {

    LL n, p = 1, maxi = 0;
    cin >> n;
    int ile0 = 0;
    
    for (int i = 0; i <= 32; i++) {
        pot[i] = p;
        p *= 2;
        //cout << i << " " << pot[i] << endl;
    }

    for (int i = 0; i < n; i++) {
        cin >> tab[i];
        if (tab[i] > maxi)
            maxi = tab[i];
        if (tab[i] == 0)
            ile0++;
    }

    /*cout << maxi << " " << maxi*2 << endl;

    for (p = 1; pot[p] <= maxi*2; p++) {
        cout << p << " " << pot[p] << endl;
    }*/

    for (p = 1; pot[p] <= maxi*2; p++) {
        for (int i = 0; i < n; i++) {
            //cout << p << " " << pot[p] << " " << i << endl;
            if (tab[i] < pot[p] && tab[i] >= pot[p-1]) {
                if (repG[p] == 0)
                    repG[p] = p;
                rep[i] = p;
            }
        }
    }
/*
    for (int i = 0; i < n; i++)
        cout << rep[i] << " ";
    cout << endl;

    for (int i = 0; pot[i] <= maxi*2; i ++)
        cout << repG[i] << " ";
    cout << "\n";
*/
    for (p = 1; pot[p] <= maxi*2; p++) {
        for (int i = 0; i < n; i++) {
            if (tab[i] % pot[p] >= pot[p-1])
                onion(rep[i], p);
        }
    }

    int ile = 0;

    for (int i = 1; pot[i] <= maxi*2; i ++) {
        //cout << repG[i] << " ";
        if (repG[i] == i)
            ile++;
    }
    //cout << "\n";

    ile += ile0;

    cout << ile << "\n";
    

    return 0;
}