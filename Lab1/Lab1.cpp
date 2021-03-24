#include <iostream>
#include <string>
#include <vector>

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
	string s;
	getline(cin, s);
	cout << decoderPlayfair(s);
}
