//
//  hw01.cpp
//  HW #1 - Caesar Cipher - reading and decrypting a text file
//
//  Created by Mandy Kong on 1/27/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

char decryptLetter(char& encryptLetter, const int& Key);

void rearrangeLines (const vector<string>& textLines, vector<string>& newTextLines);

int main() {
    ifstream text;
    text.open ("encrypted.txt");
    
    if (!text) {
        cerr << "Could not open the file\n";
        exit(1);
    }
    
    int Key;
    text >> Key;
    //obtains the shift number from text file
    text.clear();
    
    string line;
    vector<string> textLines;
    vector<string> newTextLines;
    getline(cin, line);
    
    while (getline(text, line)) {
        for (size_t letter = 0; letter < line.size(); ++letter) {
            if (islower(line[letter])) { // line[letter] <= 'z' && line[letter] >= 'a'
                decryptLetter(line[letter], Key);
            }
        }
        textLines.push_back(line);
        //the decrypted letters are placed into a vector, line by line
    }
    rearrangeLines (textLines, newTextLines);
    
    for (string Line : newTextLines) {
        cout << Line << endl;
    }
    
}

char decryptLetter(char& encryptLetter, const int& Key) {
    if (encryptLetter - Key < 'a') {
        encryptLetter = encryptLetter + 26 - Key;
        //if the rotation shift causes the letter to become a non-lowercase letter character, the formula above makes it so the letter wraps around the alphabet
    }
    else {
        encryptLetter = encryptLetter - Key;
        //otherwise the letter is shifted normally by going backwards 'Key' spaces
    }
    return encryptLetter;
}

void rearrangeLines (const vector<string>& textLines, vector<string>& newTextLines) {
    for (size_t index = textLines.size(); index != 0; --index) {
        newTextLines.push_back(textLines[index]);
    }
    //the function places the decrypted lines into another vector, starting with the last line and ending with the first line
}
