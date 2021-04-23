#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

long long p = 17;//2297;
long long q = 19;//9277;
long long e = 43;// 257;
long long r, fi, d;
pair<long long, long long> kO, kC;

long long extEuclideanAlg(long long a, long long b) {
    long long d0 = a;
    long long d1 = b;
    long long x0 = 1;
    long long x1 = 0;
    long long y0 = 0;
    long long y1 = 1;
    while (d1 > 1) {
        long long q = d0 / d1;
        long long d2 = d0 % d1;
        long long x2 = x0 - q * x1;
        long long y2 = y0 - q * y1;
        d0 = d1; d1 = d2;
        x0 = x1; x1 = x2;
        y0 = y1; y1 = y2;
    }
    if (y1 < 0) {
        y1 += a;
    }
    return y1;
}

void Init() {
    cout << "Введите p, q, e для шифрования\n";
    cin >> p >> q >> e;
    r = p * q;
    fi = (p - 1) * (q - 1);
    d = extEuclideanAlg(fi, e);
    kO = make_pair(e, r);
    kC = make_pair(d, r);
}

long long fastExp(long long num, long long pow, long long md) {
    if (pow == 1) {
        return num;
    }
    if ((pow % 2) == 0) {
        return (fastExp((num * num) % md, pow / 2, md));
    }
    return ((num * fastExp(num, pow - 1, md)) % r);
}

long long getHashFunc(long long word[], const int len, int md) {
    long long h = 100;
    for (int i = 0; i < len; i++) {
        h = (long long)pow(h + word[i], 2) % md;
    }
        
    return h;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Init();
    int type = 1;
    while (type != 0) {
        cout << "Введите 1, если хотите вычислить электронную цифровую подпись\n";
        cout << "Введите 2, если хотите проверить электронную цифровую подпись\n";
        cout << "Введите 0, если хотите выйти\n";
        cin >> type;
        long long word[1000] = {};
        long long m = 0, S = 0, signature = 0;
        int len;
        switch (type) {
        case 1:
            cout << "Введите длину массива\n";
            cin >> len;
            cout << "Введите массив\n";
            for (int i = 0; i < len; i++) {
                cin >> word[i];
            }
            m = getHashFunc(word, len, kC.second);
            S = fastExp(m, kC.first, kC.second);
            cout << "Эклетронная цифровая подпись - " << S << '\n';
            break;
        case 2:
            cout << "Введите длину массива\n";
            cin >> len;
            cout << "Введите массив\n";
            for (int i = 0; i < len; i++) {
                cin >> word[i];
            }
            cout << "Введите подпись\n";
            cin >> signature;
            m = getHashFunc(word, len, kO.second);
            S = fastExp(signature, kO.first, kO.second);
            if (S == m) {
                cout << "Подпись действительна\n";
            }
            else {
                cout << "Подпись недействительна\n";
            }
            break;
        }
    }
}