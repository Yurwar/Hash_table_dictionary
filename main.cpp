#include <iostream>
#include <string>
#include <fstream>

#define PRIME_SIZE 127

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
    LinkedList *table[PRIME_SIZE];
    int size;
    static int _hash(string str) {
        int asciiSum = 0;
        for(int i = 0; i < str.length(); i++) {
            asciiSum += str[i];
        }
        return asciiSum % PRIME_SIZE;
    }

public:
    HashTable() {
        for(int i = 0; i < PRIME_SIZE; i++) {
            table[i] = nullptr;
        }
    }
    HashTable(int size) {
        this->size = size;
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

    void find(string word) {      //TODO Compare string in lower case
        int hashNumber = _hash(word);
        LinkedList* result = table[hashNumber];
        if(!result) {
            cout << "Element does not found" << endl;
            return;
        }
        while(result->word != word) {
            if(!result->next) {
                cout << "Element does not found" << endl;
                break;
            }
            result = result->next;
        }
        cout << result->data;  //TODO If word does not find return the message
    }

    //TODO Write delete function
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
    while(cin >> wordToFind) {    //TODO Need command to exit the program
        dictionary.find(wordToFind);
        cout << endl;
    }
}
