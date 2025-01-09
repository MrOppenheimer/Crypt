// FileEncryptor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using std::string, std::cout, std::cin, std::ifstream, std::ofstream;

char* getCharArr(string str);
bool exist(string fname);
int cloneFile(string ifname, string ofname);
int encryptFile(string ifname, string ofname, string key);
int decryptFile(string ifname, string ofname, string key);


int main(int argc, char* argv[])
{
	if (argc != 4 || (strcmp(argv[1], "e") != 0) && (strcmp(argv[1], "d") != 0)) {
		cout << "User Guide:\n";
		cout << "To encrypt a file, run './crypt e input_filename output_filename'\n";
		cout << "To decrypt a file, run './crypt d input_filename output_filename'\n";
		return 0;
	}

	string ifname = (string)argv[2];
	string ofname = (string)argv[3];

	if (!exist(ifname)) {
		cout << "Input file does not exist.";
		return -1;
	}

	if (exist(ofname)) {
		cout << "There is already a file with the same output file name, please choose another output file name.";
		return -1;
	}

	string key;

	if (strcmp(argv[1], "e") == 0) {
		cout << "Enter a key for encryption:\n";
		cin >> key;

		encryptFile(ifname, ofname, key);
		return 0;
	}

	if (strcmp(argv[1], "d") == 0) {
		cout << "Enter a key for decryption:\n";
		cin >> key;

		decryptFile(ifname, ofname, key);
		return 0;
	}

	return 0;
}

char* getCharArr(string str) {
	size_t strLen = str.length();
	char* charArr = new char[strLen];
	for (int i = 0; i < strLen; i++) {
		charArr[i] = str[i];
	}
	return charArr;
}

bool exist(string fname) {
	ifstream inFile;
	inFile.open(fname);
	if (inFile) {
		inFile.close();
		return true;
	}
	return false;
}

int cloneFile(string ifname, string ofname) {
	ifstream inFile;
	inFile.open(ifname, std::ios::binary);
	if (!inFile) {
		cout << "Input file does not exist.";
		return -1;
	}

	if (exist(ofname)) {
		cout << "There is already a file with the same output file name, please choose another output file name.";
		return -1;
	}

	ofstream outFile;
	outFile.open(ofname, std::ios::binary);

	char c;
	while (inFile.read(&c, 1)) {
		outFile << c;
	}

	inFile.close();
	outFile.close();

	cout << "Cloning completed.";
	return 0;
}

int encryptFile(string ifname, string ofname, string key) {
	ifstream inFile;
	inFile.open(ifname, std::ios::binary);

	ofstream outFile;
	outFile.open(ofname, std::ios::binary);

	size_t keyLength = key.length();
	char* roundKey = getCharArr(key);

	int i = 0;
	char byte;
	while (inFile.read(&byte, 1)) {
		outFile << ((char)(byte ^ roundKey[i % keyLength]));
		roundKey[i % keyLength] = byte;
		i++;
	}

	inFile.close();
	outFile.close();

	cout << "Encrpytion completed.";
	return 0;
}

int decryptFile(string ifname, string ofname, string key) {
	ifstream inFile;
	inFile.open(ifname, std::ios::binary);

	ofstream outFile;
	outFile.open(ofname, std::ios::binary);

	size_t keyLength = key.length();
	char* roundKey = getCharArr(key);

	int i = 0;
	char byte;
	char decryptedByte;
	while (inFile.read(&byte, 1)) {
		decryptedByte = ((char)(byte ^ roundKey[i % keyLength]));
		outFile << decryptedByte;
		roundKey[i % keyLength] = decryptedByte;
		i++;
	}

	inFile.close();
	outFile.close();

	cout << "Decrpytion completed.";
	return 0;

}
