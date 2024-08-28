#include "dict.h"
#include <iostream>
Dict::Dict()
{
    for (int i = 0; i < 100001; i++)
    {
        table[i] = new AVLTree();
    }
}

Dict::~Dict()
{
    for (int i = 0; i < 100001; i++)
    {
        delete table[i];
    }
}
void Dict::insertword(string k)
{
    int h = hash(k);
    if (table[h]->root == NULL)
    {
        clash++;
    }
    table[h]->insert(k);
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence) {
    // Define a set of separators
    string separators = ".,-:!\"'()?—[]“”‘’˙;@";

    // Initialize word and start position
    string word = "";
    size_t start = 0;

    for (size_t i = 0; i < sentence.length(); i++) {
        char currentChar = sentence[i];

        if (separators.find(currentChar) != string::npos) {
            // If the current character is a separator
            if (!word.empty()) {
                // If there's a word accumulated, insert it into the dictionary
                word = remove_punctuation(word, separators);
                if (!word.empty()) {
                    int h = hash(word);
                    insertword(word);
                }
                word = ""; // Reset word
            }
        } else if (currentChar != ' ') {
            // If the current character is not a separator or space, add it to the current word
            word += currentChar;
        } else if (i > 0 && sentence[i - 1] != ' ') {
            // If a space is encountered, and the previous character was not a space, it indicates a word boundary
            // Insert the accumulated word into the dictionary
            word = remove_punctuation(word, separators);
            if (!word.empty()) {
                int h = hash(word);
                insertword(word);
            }
            word = ""; // Reset word
        }
    }

    // Handle the last word in the sentence
    if (!word.empty()) {
        word = remove_punctuation(word, separators);
        if (!word.empty()) {
            int h = hash(word);
            insertword(word);
        }
    }
}


int Dict::get_word_count(string word)
{
    int h = hash(word);
    if (table[h]->search(word) != 0)
    {
        return table[h]->search(word);
    }
    return -1;
}

void Dict::dump_dictionary(string filename) {
    ofstream outfile(filename);

    if (outfile.is_open()) {
        for (int i = 0; i < 100001; i++) {
            if (table[i]->root != nullptr) {
                inorderTraversal(outfile, table[i]->root);
            }
        }
        outfile.close();
        cout << "Dictionary dumped to " << filename << endl;
    } else {
        cout << "Unable to open the file for dumping the dictionary." << endl;
    }
}

int main()
{
    Dict Oxford;
    Oxford.insertword("Aaloo");
    Oxford.insertword("Aaloo");
    Oxford.insertword("BC");
    Oxford.insertword("Aaloo");
    //  cout<<Oxford.get_word_count("Aaloo")<<endl;
    //   cout<<Oxford.get_word_count("BC")<<endl;
   Oxford.insert_sentence(0,0,0,0,"Maa Chu Daalo Maa");
    cout<< Oxford.get_word_count("Maa")<< endl;
    return 0;
}