#include <iostream>

int main() {

    std::string napis;
    std::cin >> napis;

    int start = 0;
    while (napis[start] == '*')
        start++;

    int min_odleglosc = (int)napis.size(), ostatni_okreslony = start;
    for (int i=start+1; i<napis.size(); i++) {
        if (napis[i] != '*') {
            if (napis[ostatni_okreslony] == napis[i]) {
                ostatni_okreslony = i;
                continue;
            }
            int odleglosc = i - ostatni_okreslony - 1;
            ostatni_okreslony = i;
            if (min_odleglosc > odleglosc)
                min_odleglosc = odleglosc;
        }
    }

    if (napis.size() == min_odleglosc)
        std::cout << "1\n";
    else
        std::cout << napis.size() - min_odleglosc << "\n";

    return 0;
}