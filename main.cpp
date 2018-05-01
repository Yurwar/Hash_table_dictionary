#include <iostream>
#include <string>
#include <fstream>

#define TABLE_SIZE 847

using namespace std;

class LinkedList {
public:
    string word;
    string data;
    LinkedList* next;

    LinkedList(string word, string data) {
        this->word = word;
        this->data = data;
        this->next = nullptr;
    }

    LinkedList() {
        this->next = nullptr;
    }
};

class HashTable {
private:
    LinkedList* table[TABLE_SIZE];
    static int _hash(string str) {
        int asciiSum = 0;
        for(int i = 0; i < str.length(); i++) {
            asciiSum += str[i];
        }
        return asciiSum % TABLE_SIZE;
    }

public:
    HashTable() {
        for(int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void push(string word, string data) {
        int hashNumber = _hash(word);
        LinkedList* wordMeaning = new LinkedList(word, data);
        LinkedList* place = table[hashNumber];
        if(place == nullptr) {
            table[hashNumber] = wordMeaning;
            return;
        }

        while(place->next != nullptr) {
            place = place->next;
        }
        place->next = wordMeaning;
    }

    void find(string word) {
        for(int i = 0; i < word.length(); i++) {
            word[i] = static_cast<char>(toupper(word[i]));
        }
        int hashNumber = _hash(word);
        LinkedList* result = table[hashNumber];
        if(!result) {
            cout << "Element does not found" << endl;
            return;
        }
        while(result->word != word) {
            if(!result->next) {
                cout << "Element does not found";
                return;
            }
            result = result->next;
        }
        cout << result->data;
    }
};

int main() {
    HashTable dictionary;
    ifstream inputFile("./dict_processed.txt", ifstream::in);
    while(!inputFile.eof()) {
        string data;
        getline(inputFile, data, '\n');
        int found = data.find(";");
        string word = data.substr(0, found);
        dictionary.push(word, data);

    }
    string wordToFind;
    cout << "Type a word to get a definition: ";
    while(cin >> wordToFind) {
        dictionary.find(wordToFind);
        cout << endl << "Continue? [y] to continue, [n] to exit: ";
        char answer;
        cin >> answer;
        if(answer == 'n') exit(0);
        cout << "Enter the next word: ";
    }
}
