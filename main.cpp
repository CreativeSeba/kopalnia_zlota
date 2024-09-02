#include <bits/stdc++.h>

using namespace std;
const int S = 1 << 20, MAXV = 2 * S + 10;
int t[MAXV], pch[2 * S + 10], s, w, n;
map<int, vector<int>> otw, zam;
vector<int> maxes;
queue<int> keys;

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


    //wczytanie wspolrzednych

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        otw[x].push_back(y);
        zam[x + s].push_back(y);
    }


    //dodanie wsplorzednych zamykajacyhc do kolejki

    for (const auto &[key, vec]: zam) {
        keys.push(key);
    }


    //przeprowadzanie potrzebnych operacji na drzewie przedzialowym

    for (auto &[key, vec]: otw) {

        if (key > keys.front()) {
            maxes.push_back(Query(1, 0, S - 1, 0, S - 1));
            for (auto &vecZ: zam[keys.front()]) {
                Insert(1, 0, S - 1, vecZ, vecZ + w, -1);
            }
            keys.pop();
            for (auto &vecI: vec) {
                Insert(1, 0, S - 1, vecI, vecI + w, 1);
            }
        } else if (key == keys.front()) {
            for (auto &vecI: vec) {
                Insert(1, 0, S - 1, vecI, vecI + w, 1);
            }
            maxes.push_back(Query(1, 0, S - 1, 0, S - 1));
            for (auto &vecZ: zam[keys.front()]) {
                Insert(1, 0, S - 1, vecZ, vecZ + w, -1);
            }
            keys.pop();
        } else {
            for (auto &vecI: vec) {
                Insert(1, 0, S - 1, vecI, vecI + w, 1);
            }
        }
    }
    if (!keys.empty()) {
        maxes.push_back(Query(1, 0, S - 1, 0, S - 1));
        for (auto &vecZ: zam[keys.front()]) {
            Insert(1, 0, S - 1, vecZ, vecZ + w, -1);
        }
        keys.pop();
    }


    //znalezienie maksymalnej liczby samorodkow

    if (maxes.empty()) {
        return -1;
    }
    auto trueMax = max_element(maxes.begin(), maxes.end());
    int maxValue = *trueMax;

    cout << maxValue;

    return 0;
}