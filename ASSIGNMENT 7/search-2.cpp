// Do NOT add any other includes
#include "search.h"
SearchEngine::SearchEngine()
{
    size = 0;
    root = NULL;
    tail = NULL;
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
    SearchNode *current = root;
    while (current != nullptr)
    {
        SearchNode *next = current->next;
        delete current;
        current = next;
    }
    root = nullptr;
    tail = nullptr;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
           int n=sentence.length();
             for(int i=0;i<n;i++){
            sentence[i]=ToLower(sentence[i]);
          //  cout<<sentence[i];
        }
    if (root == NULL)
    {
        size++;
        root = new SearchNode(book_code, page, paragraph, sentence_no, sentence);
        tail = root;
        return;
    }
    tail->next = new SearchNode(book_code, page, paragraph, sentence_no, sentence);
    tail = tail->next;
    return;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    vector<Node *> v = KMP(root, pattern);
    n_matches = v.size();
    return convertToDoublyLinkedList(v);
}
// void printNode(Node *root)
// {
//     if (root == NULL)
//     {
//         return;
//     }
//   cout<<root->book_code<<","<<root->page<<","<<root->paragraph<<","<<root->sentence_no<<","<<root->offset<<endl;
//     printNode(root->right);
// }
// int main(){
//     SearchEngine GoogleKaBaap;
//     GoogleKaBaap.insert_sentence(11,1,1,1,"cart");
//    //  GoogleKaBaap.insert_sentence(11,1,1,2,"Tk with him");
//     //  GoogleKaBaap.insert_sentence(11,1,1,3,"Talk with him");
//      //  GoogleKaBaap.insert_sentence(11,1,1,4,"Tak with him");
//       //  GoogleKaBaap.insert_sentence(11,1,1,5,"Talk with hm");
//       //   GoogleKaBaap.insert_sentence(11,1,1,6,"Talk with m");
//       //    GoogleKaBaap.insert_sentence(11,1,1,7,"Talk ith him");
//           GoogleKaBaap.insert_sentence(11,1,1,8,"CArt");
//   int k=0;
//    Node* v= GoogleKaBaap.search("cart",k);
//    printNode(v);
//    return 0;
// }