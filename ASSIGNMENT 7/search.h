// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class SearchNode
{
public:
    int bookcode;
    int page_no;
    int paragraph;
    int sentence_no;
    string sentence;
    SearchNode *next;
    SearchNode(int book_code, int page, int paragraph, int sentence_no, string sentence)
    {
        bookcode = book_code;
        page_no = page;
        this->paragraph = paragraph;
        this->sentence_no = sentence_no;
        this->sentence = sentence;
        next = NULL;
    }
    SearchNode()
    {
        next = NULL;
    }
};
class SearchEngine
{
private:
    // You can add attributes/helper functions here
    char ToLower(char c)
    {
        if (c >= 'A' && c <= 'Z')
        {
            return c + 'a' - 'A';
        }
        return c;
    }
    vector<Node *> KMP(SearchNode *searchNode, string pattern)
    {
        std::vector<Node *> matches;
        int m = pattern.length();
        for(int i=0;i<m;i++){
            pattern[i]=ToLower(pattern[i]);
           // cout<<pattern[i];
        }
            std::vector<int> lps(m, 0);
        int j = 0;

        for (int i = 1; i < m; i++)
        {
            while (j > 0 && pattern[i] != pattern[j])
            {
                j = lps[j - 1];
            }
            if (pattern[i] == pattern[j])
            {
                j++;
            }
            lps[i] = j;
        }

        int sentence_number = 0;
        while (searchNode != nullptr)
        {
            int n = searchNode->sentence.length();
            int i = 0;
            j = 0;

            while (i < n)
            {
                if (pattern[j] == searchNode->sentence[i])
                {
                    i++;
                    j++;
                }

                if (j == m)
                {
                    int starting_offset = i - j;
                    Node *match = new Node(searchNode->bookcode, searchNode->page_no, searchNode->paragraph, searchNode->sentence_no, starting_offset);
                    matches.push_back(match);
                    j = lps[j - 1];
                }
                else if (i < n && pattern[j] != searchNode->sentence[i])
                {
                    if (j != 0)
                    {
                        j = lps[j - 1];
                    }
                    else
                    {
                        i++;
                    }
                }
            }

            searchNode = searchNode->next;
            sentence_number++;
        }

        return matches;
    }
    Node *convertToDoublyLinkedList(const std::vector<Node *> &nodePointers)
    {
        Node *head = nullptr;
        Node *tail = nullptr;

        for (Node *node : nodePointers)
        {
            if (node)
            {

                if (!head)
                {
                    head = node;
                    tail = node;
                }
                else
                {
                    tail->right = node;
                    node->left = tail;
                    tail = node;
                }
            }
        }
        return head;
    }

public:
    SearchNode *root;
    SearchNode *tail;
    int size;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);

    /* -----------------------------------------*/
};