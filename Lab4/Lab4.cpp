#include <iostream>
#include <fstream>
using namespace std;

const int m = 26;
int state[m];
const string inputFile = "input.txt";
const string outputFile = "output.txt";

void charInBits(unsigned char c, int *bits) {
    for (int i = 0; i < 8; i++) {
        bits[i] = 0;
    }
    int symb = (int)c;
    int i = 7;
    while (symb > 0) {
        bits[i] = symb % 2;
        symb /= 2;
        i--;
    }
}

unsigned char bitsInChar(int* bits) {
    int symb = 0;
    int st = 1;
    for (int i = 7; i >= 0; i--) {
        bits[i] == 1 ? symb += st : symb += 0;
        st *= 2;
    }
    return (unsigned char)symb;
}

int nextState() {
    const int lenNumOfXorBits = 4;
    const int numOfXorBits[] = { 0, 6, 7, 25 };
    int ans = state[m - 1];
    int newBit = 0;
    for (int i = 0; i < lenNumOfXorBits; i++) {
        newBit ^= state[numOfXorBits[i]];
    }
    for (int i = m - 1; i > 0; i--) {
        state[i] = state[i - 1];
    }
    state[0] = newBit;
    return ans;
}

bool coderLSFR(string inFile, string outFile) {
    ifstream fileRead(inFile);
    ofstream fileWrite(outFile);
    if (!fileRead) {
        cout << "Файл не найден\n";
        return false;
    }
    while (true) {
        unsigned char c;
        fileRead >> c;
        if (fileRead.eof()) {
            break;
        }
        int bits[8];
        charInBits(c, bits);
        for (int i = 0; i < 8; i++) {
            bits[i] = bits[i] ^ nextState();
        }
        fileWrite << bitsInChar(bits);
    }
    fileRead.close();
    fileWrite.close();
    return true;
}

void makeStartState() {
    for (int i = 0; i < 26; i++) {
        state[i] = 1;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int type = 1;
    while (type != 0) {
        cout << "Введите 1, если хотите зашифровать файл\n";
        cout << "Введите 2, если хотите расшифровать файл\n";
        cout << "Введите 0, если хотите выйти\n";
        cin >> type;
        if (type == 1) {
            makeStartState();
            if (coderLSFR(inputFile, outputFile)) {
                cout << "Файл зашифрован.\n";
            }
        }
        if (type == 2) {
            makeStartState();
            if (coderLSFR(outputFile, inputFile)) {
                cout << "Файл расшифрован.\n";
            }
        }
    }
}
