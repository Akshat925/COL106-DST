// Do NOT add any other includes
#include "dict.h"

Dict::Dict()
{
     // tsize=100001;
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
Xwords::~Xwords(){
     for (int i = 0; i < 101; i++)
    {
        
         //delete table[i];
    }
}
char ToLower(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + 'a' - 'A';
    }
    return c;
}
void inOrderTraversal(AVLNode *root, ofstream &outputFile)
{
    if (root)
    {
        inOrderTraversal(root->left, outputFile);

        outputFile << root->key << "," << root->count << endl;

        inOrderTraversal(root->right, outputFile);
    }
}

void Dict::insertword(string k)
{
    int h = hash(k);
    //  cout<<"the hash is "<<h<<endl;
    table[h]->insert(k);
}
bool isValidChar(char c)
{
    return (c != '.' && c != ',' && c != '-' && c != ':' && c != '!' && c != '\"' &&
            c != '(' && c != ')' && c != '?' &&
            c != '[' && c != ']' && c != ';' && c != '@' && c != ' ' && c != 39);
}
void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    std::string word = "";
    for (char c : sentence)
    {
        if (!isValidChar(c))
        {
            if (!word.empty())
            {
                for (size_t i = 0; i < word.length(); i++)
                {
                    word[i] = ToLower(word[i]);
                }
                insertword(word);
                word = "";
            }
        }
        else
        {
            word += c;
        }
    }

    if (!word.empty())
    {
        for (size_t i = 0; i < word.length(); i++)
        {
            word[i] = ToLower(word[i]);
        }
        insertword(word);
    }
}

long long Dict::get_word_count(string word)
{
    int h = hash(word);
    if (table[h]->search(word) != 0)
    {
        return table[h]->search(word);
    }
    return 0;
}
int Xwords::get_word_count(string word)
{
    int h = hash(word);
    if (table[h]->search(word) != 0)
    {
        return table[h]->search(word);
    }
    return 0;
}

void Dict::dump_dictionary(string filename)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open())
    {
        return;
    }

    for (int i = 0; i < 100001; i++)
    {
        AVLTree *avlTree = table[i];
        AVLNode *root = avlTree->root;
        inOrderTraversal(root, outputFile);
    }
    outputFile.close();
    return;
}
void Xwords::insert_sentence(string sentence)
    {
    std::string word = "";
    for (char c : sentence)
    {
        if (!isValidChar(c))
        {
            if (!word.empty())
            {
                for (size_t i = 0; i < word.length(); i++)
                {
                    word[i] = ToLower(word[i]);
                }
                insertword(word);
                word = "";
            }
        }
        else
        {
            word += c;
        }
    }

    if (!word.empty())
    {
        for (size_t i = 0; i < word.length(); i++)
        {
            word[i] = ToLower(word[i]);
        }
        insertword(word);
    }
}
// double Xwords::GetScorePara(string sentence){
//      std::string word = "";
//      double ans=0;
//     for (char c : sentence)
//     {
//         if (!isValidChar(c))
//         {
//             if (!word.empty())
//             {
//                 for (size_t i = 0; i < word.length(); i++)
//                 {
//                     word[i] = ToLower(word[i]);
//                 }
//               ans+=(get_word_count(word))*()
//                 word = "";
//             }
//         }
//         else
//         {
//             word += c;
//         }
//     }

//     if (!word.empty())
//     {
//         for (size_t i = 0; i < word.length(); i++)
//         {
//             word[i] = ToLower(word[i]);
//         }
//         insertword(word);
//     }
// }
// // int main(){
//     Dict Oxford;
// //     Oxford.insertword("Aaloo");
// //      Oxford.insertword("Aaloo");
// //      Oxford.insertword("BC");
// //      Oxford.insertword("Aaloo");
// //   //  cout<<Oxford.get_word_count("Aaloo")<<endl;
// //    //   cout<<Oxford.get_word_count("BC")<<endl;
// //     //   for(long long i=0;i<1000000;i++){
// //     //     Oxford.insertword(to_string(i));
// //     //   }
// // int k=0;
// //       Oxford.insert_sentence(1,1,1,1,"camp knha kr rhe h");
// //       cout<<Oxford.get_word_count("camp")<<endl;
// //       Oxford.dump_dictionary("tet");
// //  for(long long i=0;i<20000;i++){
// //     Oxford.insert_sentence(1,1,1,1,to_string(i));
// //     if(Oxford.get_word_count(to_string(i))==-1){
// //        // cout<<"Noob\n";
// //         cout<<i<<endl;
// //         k++;
// //     }
// //  }
// //   cout<<k<<endl;
//   Oxford.insertword(to_string(9123));
//    Oxford.insertword(to_string(8123));
//     Oxford.insertword(to_string(7123));
//      Oxford.insertword(to_string(6123));
//       Oxford.insertword(to_string(5123));
//        Oxford.insertword(to_string(4123));
//         Oxford.insertword(to_string(3123));
//          Oxford.insertword(to_string(2123));
//           Oxford.insertword(to_string(1123));
//       cout<<Oxford.get_word_count(to_string(1123))<<endl;
//        cout<<Oxford.get_word_count(to_string(123))<<endl;
//         cout<<Oxford.get_word_count(to_string(2123))<<endl;
//          cout<<Oxford.get_word_count(to_string(3123))<<endl; cout<<Oxford.get_word_count(to_string(4123))<<endl;
//           cout<<Oxford.get_word_count(to_string(5123))<<endl; cout<<Oxford.get_word_count(to_string(6123))<<endl; cout<<Oxford.get_word_count(to_string(7123))<<endl;
//     return 0;
// }