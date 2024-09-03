#include <bits/stdc++.h>

using namespace std;

const int S = 1 << 20, MAXV = 2 * S + 10;
int t[MAXV], pch[MAXV], s, w, n;
const int MAX_COORD = 30010;
const int MAXN = 2 * MAX_COORD;
map<int, vector<pair<int, int>>> otw, zam;


void Pchaj(int v, int p, int k) {
    t[v] += pch[v];
    if (p != k)
        pch[v * 2] += pch[v], pch[v * 2 + 1] += pch[v];
    pch[v] = 0;
}

void Insert(int v, int p, int k, int a, int b, int w) {
    Pchaj(v, p, k);
    if (k < a || p > b)
        return;
    if (a <= p && k <= b) {
        pch[v] += w;
        Pchaj(v, p, k);
        return;
    }
    Insert(v * 2, p, (p + k) / 2, a, b, w);
    Insert(v * 2 + 1, (p + k) / 2 + 1, k, a, b, w);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
}

int Query(int v, int p, int k, int a, int b) {
    Pchaj(v, p, k);
    if (k < a || p > b)
        return 0;
    if (a <= p && k <= b)
        return t[v];
    return max(Query(v * 2, p, (p + k) / 2, a, b), Query(v * 2 + 1, (p + k) / 2 + 1, k, a, b));
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> s >> w >> n;

    // Wczytywanie współrzędnych i normalizacja
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x += MAX_COORD;  // Normalizacja współrzędnych x
        y += MAX_COORD;  // Normalizacja współrzędnych y
        otw[x].emplace_back(y, y + w);  // Dodawanie par (y, y + w)
        zam[x + s].emplace_back(y, y + w);
    }

    auto itOtw = otw.begin();
    auto itZam = zam.begin();

    int maxValue = 0;  // Maksymalna liczba samorodków

    // Obsługa drzewa przedziałowego
    for (int i = 0; i < MAXN; i++) {
        while (itOtw != otw.end() && itOtw->first == i) {
            for (auto &p : itOtw->second) {
                Insert(1, 0, S - 1, p.first, p.second, 1);
            }
            itOtw++;
        }

        maxValue = max(maxValue, Query(1, 0, S - 1, 0, S - 1));  // Zapisywanie maksymalnej wartości

        while (itZam != zam.end() && itZam->first == i) {
            for (auto &p : itZam->second) {
                Insert(1, 0, S - 1, p.first, p.second, -1);
            }
            itZam++;
        }
    }

    cout << maxValue << "\n";

    return 0;
}
