#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class AVLNode
{
public:
    int height;
    string key;
    AVLNode *left;
    AVLNode *right;
    AVLNode *par;
    int count;
    AVLNode()
    {
        left = NULL;
        right = NULL;
        par = NULL;
        count = 0;
        key = "";
    }
    AVLNode(string k)
    {
        left = NULL;
        right = NULL;
        par = NULL;
        count = 1;
        height = 0;
        key = k;
    }
    int heightc(AVLNode *root)
    {
        if (root == NULL)
        {
            return -1;
        }
        return root->height;
    }
    AVLNode *LeftLeftRotation()
    {
        AVLNode *r = this->right;
        AVLNode *t = r->left;
        r->par = this->par;
        this->par = r;
        if (t != NULL)
        {
            t->par = this;
        }
        this->right = t;
        r->left = this;
        this->height = max(heightc(this->left), heightc(this->right)) + 1;
        r->height = max(heightc(r->left), heightc(r->right)) + 1;
        return r;
    }

    AVLNode *RightRightRotation()
    {
        AVLNode *l = this->left;
        AVLNode *t = l->right;
        l->par = this->par;
        this->par = l;
        if (t != NULL)
        {
            t->par = this;
        }
        this->left = t;
        l->right = this;
        this->height = max(heightc(this->left), heightc(this->right)) + 1;
        l->height = max(heightc(l->left), heightc(l->right)) + 1;
        return l;
    }

    AVLNode *LeftRightRotation()
    {
        this->left = this->left->LeftLeftRotation();
        return this->RightRightRotation();
    }

    AVLNode *RightLeftRotation()
    {
        this->right = this->right->RightRightRotation();
        return this->LeftLeftRotation();
    }
};
class AVLTree
{
    AVLNode *searchkro(AVLNode *root, string k)
    {
        if (root == NULL)
        {
            return NULL;
        }
        if (root->key == k)
        {
            return root;
        }
        if (root->key > k)
        {
            return searchkro(root->left, k);
        }
        else
        {
            return searchkro(root->right, k);
        }
    }

public:
    AVLNode *root;
    AVLTree()
    {
        root = NULL;
    }
    int height(AVLNode *root)
    {
        if (root == NULL)
        {
            return -1;
        }
        return root->height;
    }

    int balance(AVLNode *root)
    {
        return height(root->left) - height(root->right);
    }
    AVLNode *Insertkro(AVLNode *root, string k)
    {
        if (root == NULL)
        {

            //  cout<<"surprisemf\n";
            return new AVLNode(k);
        }
        else if (root->key > k)
        {
            root->left = Insertkro(root->left, k);
            root->left->par = root;
        }
        else
        {
            root->right = Insertkro(root->right, k);
            root->right->par = root;
        }
        root->height = 1 + max(height(root->left), height(root->right));
        int bal = balance(root);

        if (bal > 1 && k < root->left->key)
        {
            return root->RightRightRotation();
        }

        if (bal < -1 && k > root->right->key)
        {
            return root->LeftLeftRotation();
        }

        if (bal > 1 && k > root->left->key)
        {
            return root->LeftRightRotation();
        }

        if (bal < -1 && k < root->right->key)
        {
            return root->RightLeftRotation();
        }

        return root;
    }
    void insert(string k)
    {
        if (root == NULL)
        {
            root = new AVLNode(k);
            return;
        }
        AVLNode *o = searchkro(root, k);
        if (o == NULL)
        {
            Insertkro(root, k);
            return;
        }
        o->count++;
    }
    int search(string k)
    {
        AVLNode *o = searchkro(root, k);
        if (o == NULL)
        {
            //  cout<<"null\n";
            return 0;
        }
        else
        {
            // cout<<"NOTnull\n";
            int k = o->count;
            o = NULL;
            return k;
        }
    }
};
class Dict
{
private:
    string remove_punctuation(const string& word, const string& separators) {
        string result = word;

        result.erase(0, result.find_first_not_of(separators));

        result.erase(result.find_last_not_of(separators) + 1);

        return result;
    }

    void inorderTraversal(ofstream &outfile, AVLNode *node)
    {
        if (node != nullptr)
        {
            inorderTraversal(outfile, node->left);
            outfile << node->key << " " << node->count << "\n";
            inorderTraversal(outfile, node->right);
        }
    }
    // You can add attributes/helper functions here

public:
    AVLTree *table[100001];
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();
    int clash = 0;
    int hash(string id)
    {
        int sum = 0;
        for (int i = 0; i < id.size(); i++)
        {
            int k = id[i];
            sum = (sum * 29) % 100001 + k;
        }
        return sum % 100001;
    }

    void insertword(string k);

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);
};