// Do NOT add any other includes
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
    long long count;
    AVLNode()
    {
        left = NULL;
        right = NULL;
        par = NULL;
     //   score=0;
        count = 0;
        key = "";
    }
    AVLNode(string k)
    {
        left = NULL;
        right = NULL;
        par = NULL;
        count = 1;
       // score=0;
        height = 0;
        key = k;
    }
    ~AVLNode()
    {
        if (left != NULL)
        {
            delete left;
        }
        if (right != NULL)
        {
            delete right;
        }
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
public:
    AVLNode *root;
     AVLNode *searchkro(AVLNode*r,string k)
    {
        if (r == NULL)
        {
            return NULL;
        }
        if (r->key == k)
        {
            return r;
        }
        if (r->key > k)
        {
            return searchkro(r->left,k);
        }
        else
        {
            return searchkro(r->right,k);
        }
    }
    AVLTree()
    {
        root = NULL;
    }
    ~AVLTree()
    {
        if (root)
        {
            delete root;
        }
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
            //  cout<<k<<endl;
            //  cout<<"surprisemf\n";
            return new AVLNode(k);
        }
        else if (root->key > k)
        {
            //  cout<<"on your left\n";
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
        //   cout<<"hii "<<root->key<<endl;
        return root;
    }
    void insert(string k)
    {
        if (root == NULL)
        {
            root = new AVLNode(k);
            return;
        }
        AVLNode *o = searchkro(root,k);
        
        if (o == NULL)
        {
            // cout<<"hii\n";
            root = Insertkro(root, k);
            return;
        }
        o->count++;
    }
    long long search(string k)
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
            long long k = o->count;
            o = NULL;
            return k;
        }
    }
};
class Dict
{
private:
    // You can add attributes/helper functions here
public:
    int clash = 0;
  
    AVLTree *table[100001];
    int hash(string id)
    {
        long long sum = 0;
        int n=id.size();
        for (int i = 0; i < n; i++)
        {
            int k = id[i];
            sum = (sum * 29) % 100001 + k;
        }
        return sum % 100001;
    }
    void insertword(string k);
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();
    void insert(string word,long long count){
       // cout<<"hola\n";
       // cout<<word<<endl;
        insertword(word);
             int h = hash(word);
           AVLTree* tr=table[h];
           AVLNode* fnd=tr->searchkro(tr->root,word);
           fnd->count=count;
           return;
    }
    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    long long get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
class Xwords{
 public:
   int para_no;
   int page_no;
   int book_code;
   double score;
 AVLTree*table[101];
    int clash = 0;
    int hash(string id)
    {
        long long sum = 0;
        int n=id.size();
        for (int i = 0; i < n; i++)
        {
            int k = id[i];
            sum = (sum * 29) % 101 + k;
        }
        return sum % 101;
    }
     int get_word_count(string word);
 void insertword(string k)
  {
    int h = hash(k);
    
    if (table[h]->root == NULL)
    {
        clash++;
    }
    table[h]->insert(k);

   }
   void insert_sentence(string sentence);

   
 Xwords(int bc,int pg,int pr)
{
     // tsize=100001;
     book_code=bc;
     page_no=pg;
     para_no=pr;
    for (int i = 0; i < 101; i++)
    {
        table[i] = new AVLTree();
    }
}
~Xwords();
};
