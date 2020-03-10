#include <iostream>
using namespace std;

#define LL long long

const LL p = 997;
const LL mod = 1000*1000*1000+19;

LL h[300*1000+5];
LL pow[300*1000+5];

void init(const string& s) {

    h[0] = (int)(s[0]) % mod;

    for (size_t i = 1; i < s.size(); i++) {
        h[i] = s[i] + p * h[i-1];
        h[i] %= mod;
    }
    
    pow[0] = 1;
    
    for (size_t i = 1; i < s.size(); i++) {
        pow[i] = pow[i-1] * p;
        pow[i] %= mod;
    }
}
 
LL przedzial(int p, int k) {

    //cout << "przedzial " << p << "-" << k << ":   ";

    p--;
    k--;
    
    if (p == 0) {
        //cout << h[k] % mod << "\n";
        return h[k] % mod;
    }

    LL minus = h[p-1]; //with 0s at the end
    minus *= pow[k-p+1];
    minus %= mod;

    LL ans =  h[k] - minus + mod;
    ans %= mod;
    //cout  << h[k] << " - " << minus << " + " << mod << " % " << pow[p] << " = " << ans << "";
    ans %= mod;
    if (ans < 0) {
        ans += mod;
        ans %= mod;
    }
    //cout << " mod\n" << ans << "\n";
    return ans;
}

//zwraca -1 jesli ab < cd; 0 jesli rowne; 1 jesli ab > cd
//binsearch szuka wpolnego prefiksu i porownuje nastepna litere
int porownaj(int a, int b, int c, int d, string s) {

    while (a < b) {
        int sab = (a + b) / 2;
        int scd = (c + d) / 2;
        LL hab = przedzial(a, sab);
        LL hcd = przedzial(c, scd);
        //cout << a << "-" << sab << " vs. " << c << "-" << scd << ":   ";
        //cout << hab << " ? " << hcd << "\n";
        if (hab == hcd) {
            a = sab + 1;
            c = scd + 1;
        }
        else {
            b = sab;
            d = scd;
        }
    }
    //cout << a << " vs. " << c << ":   ";
    //cout << s[a-1] << " ? " << s[c-1] << "\n";
    if (s[a-1] == s[c-1])
        return 0;
    else if (s[a-1] < s[c-1])
        return -1;
    else
        return 1;
}

void wypisz(int a, int b, int c, int d, string s) {

    for (int i=a; i<=b; i++)
        cout << s[i-1];
    cout << "...";
    for (int i=c; i<=d; i++)
        cout << s[i-1];
    cout << "...";
}

int main() {

    std::ios_base::sync_with_stdio(false);

    int n, m; string s;
    cin >> n >> m >> s;

    init(s);

    int a, b, c, d;

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c >> d;

        /*
        if (i == 2380-1) {
            wypisz(a,b,c,d,s);
        }
         */

        if (b-a > d-c) { //czyli gdy a...b jest dluzszy
            int por = porownaj(a, a+d-c, c, d, s);
            if (por == -1)
                cout << "<\n";
            else
                cout << ">\n";
        }
        else if (b-a < d-c) { //czyli gdy c...d jest dluzszy
            int por = porownaj(a, b, c, c+b-a, s);
            if (por == -1 || por == 0)
                cout << "<\n";
            else
                cout << ">\n";

        }
        else { //czyli gdy sa rownych dlugosci
            int por = porownaj(a, b, c, d, s);
            if (por == -1)
                cout << "<\n";
            else if (por == 1)
                cout << ">\n";
            else
                cout << "=\n";
        }
    }

    //cout << (int)('b') << " " << (int)('z') << " ";
    //cout << (int)('c') << " " << (int)('i') << "\n";


    return 0;
}

/*
 *   12 wiersz 2380: wczytano 'bzprqyyp...cigbqonp...>', a oczekiwano '<'
 *  czyli
 *  a-b:   bzprqyyp
 *  c-d:   cigbqonp
 *  mój program mówi: >
 *  powinno być: <
 */