#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

int const playfairSizeX = 5;
int const playfairSizeY = 5;

char const keyPlayfairMatrix[playfairSizeX][playfairSizeY] = {
	{'C', 'R', 'Y', 'P', 'T'},
	{'O', 'G', 'A', 'H', 'B'},
	{'D', 'E', 'F', 'I', 'K'},
	{'L', 'M', 'N', 'Q', 'S'},
	{'U', 'V', 'W', 'X', 'Z'}
};

pair<int, int> const keyRoatingLattice[4] = {
	{0, 0}, {1, 3}, {2, 2}, {3, 1}
};

void changeIndent(int &numOfIndent) {
	numOfIndent = 3 - numOfIndent;
}

string coderRailFenceMethod(string word, int key) {
	int len = word.length();
	string codeWord = "";
	int firstIndent = (key - 1) * 2;
	int secondIndent = 0;
	for (int startSymb = 0; startSymb < key; startSymb++) {
		int num = startSymb;
		int numOfIndent = 1;
		if (firstIndent == 0) {
			numOfIndent = 2;
		}
		while (num < len) {
			codeWord += word[num];
			if (numOfIndent == 1) {
				num += firstIndent;
			} else {
				num += secondIndent;
			}
			if (firstIndent > 0 && secondIndent > 0) { 
				changeIndent(numOfIndent); 
			}
		}
		firstIndent = firstIndent - 2;
		secondIndent = secondIndent + 2;
	}
	return codeWord;
}

string decoderRailFenceMethod(string codeWord, int key) {
	int len = codeWord.length();
	string word = codeWord;
	int firstIndent = (key - 1) * 2;
	int secondIndent = 0;
	int i = 0;
	for (int startSymb = 0; startSymb < key; startSymb++) {
		int num = startSymb;
		int numOfIndent = 1;
		if (firstIndent == 0) {
			numOfIndent = 2;
		}
		while (num < len) {
			word[num] = codeWord[i];
			if (numOfIndent == 1) {
				num += firstIndent;
			}
			else {
				num += secondIndent;
			}
			if (firstIndent > 0 && secondIndent > 0) {
				changeIndent(numOfIndent);
			}
			i++;
		}
		firstIndent = firstIndent - 2;
		secondIndent = secondIndent + 2;
	}
	return word;
}

string coderColumnarMethod(string word, string key) {
	string codeWord = "";
	vector<int> keyNum;
	int lenKey = key.length();
	keyNum.resize(lenKey);
	for (int i = 0; i < lenKey; i++) {
		int position = 0;
		for (int j = 0; j < lenKey; j++) {
			if ((key[j] < key[i]) || (key[j] == key[i] && i > j)) {
				position++;
			}
		}
		keyNum[position] = i;
	}
	for (int i = 0; i < lenKey; i++) {
		int num = keyNum[i];
		while (num < word.length()) {
			codeWord += word[num];
			num += lenKey;
		}
	}
	keyNum.clear();
	return codeWord;
}

string decoderColumnarMethod(string codeWord, string key) {
	string word = codeWord;
	vector<int> keyNum;
	int lenKey = key.length();
	keyNum.resize(lenKey);
	for (int i = 0; i < lenKey; i++) {
		int position = 0;
		for (int j = 0; j < lenKey; j++) {
			if ((key[j] < key[i]) || (key[j] == key[i] && i > j)) {
				position++;
			}
		}
		keyNum[position] = i;
	}
	int position = 0;
	for (int i = 0; i < lenKey; i++) {
		int num = keyNum[i];
		while (num < codeWord.length()) {
			word[num] = codeWord[position];
			position++;
			num += lenKey;
		}
	}
	keyNum.clear();
	return word;
}

string coderRotatingLatticeMethod(string word) {
	string codeWord = "";
	for (int i = 0; i < 16; i++) codeWord += "*";
	int num = 0;
	pair<int, int> keyRoatingLatticeChange[4];
	for (int i = 0; i < 4; i++) {
		keyRoatingLatticeChange[i].first = keyRoatingLattice[i].first;
		keyRoatingLatticeChange[i].second = keyRoatingLattice[i].second;
	}
	for (int i = 0; i < word.length(); i++) {
		int posX = keyRoatingLatticeChange[num].first;
		int posY = keyRoatingLatticeChange[num].second;
		if ((i != 0) && ((i % 4) == 0)) {
			for (int j = 0; j < 4; j++) {
				int oldPosX = keyRoatingLatticeChange[j].first;
				int oldPosY = keyRoatingLatticeChange[j].second;
				keyRoatingLatticeChange[j].first = oldPosY;
				keyRoatingLatticeChange[j].second = 3 - oldPosX;
			}
			sort(keyRoatingLatticeChange, keyRoatingLatticeChange + 4);
		}
		codeWord[keyRoatingLatticeChange[num].first * 4 + keyRoatingLatticeChange[num].second] = word[i];
		num++;
		num = num % 4;
	}
	return codeWord;
}

string decoderRotatingLatticeMethod(string codeWord) {
	string word = "";
	for (int i = 0; i < 16; i++) word += "*";
	int num = 0;
	pair<int, int> keyRoatingLatticeChange[4];
	for (int i = 0; i < 4; i++) {
		keyRoatingLatticeChange[i].first = keyRoatingLattice[i].first;
		keyRoatingLatticeChange[i].second = keyRoatingLattice[i].second;
	}
	for (int i = 0; i < codeWord.length(); i++) {
		int posX = keyRoatingLatticeChange[num].first;
		int posY = keyRoatingLatticeChange[num].second;
		if ((i != 0) && ((i % 4) == 0)) {
			for (int j = 0; j < 4; j++) {
				int oldPosX = keyRoatingLatticeChange[j].first;
				int oldPosY = keyRoatingLatticeChange[j].second;
				keyRoatingLatticeChange[j].first = oldPosY;
				keyRoatingLatticeChange[j].second = 3 - oldPosX;
			}
			sort(keyRoatingLatticeChange, keyRoatingLatticeChange + 4);
		}
		word[i] = codeWord[keyRoatingLatticeChange[num].first * 4 + keyRoatingLatticeChange[num].second];
		num++;
		num = num % 4;
	}
	while ((word.length() > 0) && (word[word.length() - 1]) == '*') {
		word.erase(word.length() - 1, 1);
	}
	return word;
}

pair<int, int> findPosInPlayfairMatrix(char c) {
	if (c == 'J') {
		c = 'I';
	}
	for (int i = 0; i < playfairSizeX; i++)
		for (int j = 0; j < playfairSizeY; j++)
			if (keyPlayfairMatrix[i][j] == c) {
				pair<int, int> ans = { i, j };
				return ans;
			}
}

string coderPlayfair(string word) {
	int i = 1;
	string codeWord = "";
	while (i < word.length()) {
		pair<int, int> posFirst = findPosInPlayfairMatrix(word[i - 1]);
		pair<int, int> posSecond = findPosInPlayfairMatrix(word[i]);
		pair<int, int> newPosFirst;
		pair<int, int> newPosSecond;
		if (posFirst.first == posSecond.first) {
			newPosFirst = posFirst;
			newPosSecond = posSecond;
			newPosFirst.second = (newPosFirst.second + 1) % playfairSizeY;
			newPosSecond.second = (newPosSecond.second + 1) % playfairSizeY;
		} else {
			if (posFirst.second == posSecond.second) {
				newPosFirst = posFirst;
				newPosSecond = posSecond;
				newPosFirst.first = (newPosFirst.first + 1) % playfairSizeX;
				newPosSecond.first = (newPosSecond.first + 1) % playfairSizeX;
			} else {
				newPosFirst = posFirst;
				newPosSecond = posSecond;
				newPosFirst.first = posFirst.first;
				newPosFirst.second = posSecond.second;
				newPosSecond.first = posSecond.first;
				newPosSecond.second = posFirst.second;
			}
		}
		codeWord += keyPlayfairMatrix[newPosFirst.first][newPosFirst.second];
		codeWord += keyPlayfairMatrix[newPosSecond.first][newPosSecond.second];
		i += 2;
	}
	if (word.length() % 2 != 0) {
		codeWord += word[i - 1];
	}
	return codeWord;
}

string decoderPlayfair(string codeWord) {
	int i = 1;
	string word = "";
	while (i < codeWord.length()) {
		pair<int, int> posFirst = findPosInPlayfairMatrix(codeWord[i - 1]);
		pair<int, int> posSecond = findPosInPlayfairMatrix(codeWord[i]);
		pair<int, int> newPosFirst;
		pair<int, int> newPosSecond;
		if (posFirst.first == posSecond.first) {
			newPosFirst = posFirst;
			newPosSecond = posSecond;
			newPosFirst.second = (newPosFirst.second - 1 + playfairSizeY) % playfairSizeY;
			newPosSecond.second = (newPosSecond.second - 1 + playfairSizeY) % playfairSizeY;
		}
		else {
			if (posFirst.second == posSecond.second) {
				newPosFirst = posFirst;
				newPosSecond = posSecond;
				newPosFirst.first = (newPosFirst.first - 1 + playfairSizeX) % playfairSizeX;
				newPosSecond.first = (newPosSecond.first - 1 + playfairSizeX) % playfairSizeX;
			}
			else {
				newPosFirst = posFirst;
				newPosSecond = posSecond;
				newPosFirst.first = posFirst.first;
				newPosFirst.second = posSecond.second;
				newPosSecond.first = posSecond.first;
				newPosSecond.second = posFirst.second;
			}
		}
		word += keyPlayfairMatrix[newPosFirst.first][newPosFirst.second];
		word += keyPlayfairMatrix[newPosSecond.first][newPosSecond.second];
		i += 2;
	}
	if (codeWord.length() % 2 != 0) {
		word += codeWord[i - 1];
	}
	return word;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int type = 0;
	while (type != 9) {
		cout << "Введите 1, если хотите выбрать метод железной изгороди\n";
		cout << "Введите 2, если хотите выбрать столбцовый метод\n";
		cout << "Введите 3, если хотите выбрать метод поворачивающейся решетки\n";
		cout << "Введите 4, если хотите выбрать Шифр Плейфера\n";
		cout << "Введите 9, если хотите выйти\n";
		cin >> type;
		int typeCD = 0;
		switch (type) {
		case 1:
			while (typeCD != 9) {
				cout << "Введите 1, если хотите использовать шифратор\n";
				cout << "Ввелите 2, если хотите использовать дешифратор\n";
				cout << "Введите 9, если хотите выйти\n";
				cin >> typeCD;
				if (typeCD != 9) {
					cout << "Введите слово и ключ\n";
					string word;
					int key;
					cin >> word >> key;
					if (typeCD == 1) {
						cout << "Ответ - " << coderRailFenceMethod(word, key) << '\n';
					}
					else {
						cout << "Ответ - " << decoderRailFenceMethod(word, key) << '\n';
					}
				}
			}
			break;

		case 2:
			while (typeCD != 9) {
				cout << "Введите 1, если хотите использовать шифратор\n";
				cout << "Ввелите 2, если хотите использовать дешифратор\n";
				cout << "Введите 9, если хотите выйти\n";
				cin >> typeCD;
				if (typeCD != 9) {
					cout << "Введите слово и ключ\n";
					string word;
					string key;
					cin >> word >> key;
					if (typeCD == 1) {
						cout << "Ответ - " << coderColumnarMethod(word, key) << '\n';
					}
					else {
						cout << "Ответ - " << decoderColumnarMethod(word, key) << '\n';
					}
				}
			}
			break;

		case 3:
			while (typeCD != 9) {
				cout << "Введите 1, если хотите использовать шифратор\n";
				cout << "Ввелите 2, если хотите использовать дешифратор\n";
				cout << "Введите 9, если хотите выйти\n";
				cin >> typeCD;
				if (typeCD != 9) {
					cout << "Введите слово\n";
					string word;
					cin >> word;
					if (typeCD == 1) {
						cout << "Ответ - " << coderRotatingLatticeMethod(word) << '\n';
					}
					else {
						cout << "Ответ - " << decoderRotatingLatticeMethod(word) << '\n';
					}
				}
			}
			break;
		case 4:
			while (typeCD != 9) {
				cout << "Введите 1, если хотите использовать шифратор\n";
				cout << "Ввелите 2, если хотите использовать дешифратор\n";
				cout << "Введите 9, если хотите выйти\n";
				cin >> typeCD;
				if (typeCD != 9) {
					cout << "Введите слово\n";
					string word;
					cin >> word;
					if (typeCD == 1) {
						cout << "Ответ - " << coderPlayfair(word) << '\n';
					}
					else {
						cout << "Ответ - " << decoderPlayfair(word) << '\n';
					}
				}
			}
			break;
		}
	}
}
