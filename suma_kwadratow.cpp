#include <iostream>
#include <set>
#include <map>
using namespace std;

#define LL long long

int main() {

    int n;
    cin >> n;

    set<LL> s;
    set<LL>::iterator it;
    map<LL, pair<LL, LL>> m;
    LL a, b, c;
    bool littlest, biggest;
    LL suma = 0, e, f, g;

    cin >> a;
    s.insert(a);
    m[a] = make_pair(0,0);

    for (int i = 1; i < n; i++) {
        cin >> b;
        s.insert(b);
//        cout << "\ninsert " << b << "\n";

        a = 0; c = 0;
        biggest = false;
        littlest = false;
        it = s.upper_bound(b);
        if (it == s.end())
           biggest = true;
        else
            c = *it;
        it--;
        if (it == s.begin())
            littlest = true;
        else {
            it--;
            a = *it;
        }
/*
        for (it = s.begin(); it != s.end(); it++) {
            cout << *it << " ";
        }
        cout << "\n";

        cout << a << " " << b << " " << c << " - ";
*/
        if (littlest) {
            e = (c-b)*(c-b);
            suma += e;
            m[c] = make_pair(e, m[c].second);
            m[b] = make_pair(0, e);
        }
        else if (biggest) {
            e = (b-a)*(b-a);
            suma += e;
            m[a] = make_pair(m[a].first, e);
            m[b] = make_pair(e, 0);
        }
        else {
            e = (b-a)*(b-a);
            f = (c-b)*(c-b);
            g = (c-a)*(c-a);
            suma -= g;
            suma += e + f;
            m[a] = make_pair(m[a].first, e);
            m[b] = make_pair(e, f);
            m[c] = make_pair(f, m[c].second);
        }
        cout << suma << "\n";
    }



    return 0;
}