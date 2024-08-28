#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;
char ToLower2(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + 'a' - 'A';
    }
    return c;
}
bool isValidChar2(char c)
{
    return (c != '.' && c != ',' && c != '-' && c != ':' && c != '!' && c != '\"' &&
            c != '(' && c != ')' && c != '?' &&
            c != '[' && c != ']' && c != ';' && c != '@' && c != ' ' && c != 39);
}
void readAndInsertIntoDictionary(const string& filename, Dict& dictionary) {
      ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << std::endl;
        return ;
    }

   string line;
    bool i=true;
    while (getline(file, line)) {
        if(i){
            i=false;
            continue;
        }
        stringstream ss(line);
       string currentWord;
       getline(ss, currentWord, ',');
        string countString;
        getline(ss, countString);
        long long count =stoll(countString);

        // Insert into the Dictionary
       // cout<<"hello\n";
        dictionary.insert(currentWord, count);
      
    }

    file.close();  // Close the file when done reading
}

QNA_tool::QNA_tool(){
    // Implement your function here 
    readAndInsertIntoDictionary("unigram_freq.csv",unigram); 
}

QNA_tool::~QNA_tool(){
    // Implement your function here  
   // vecofparas.clear();
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
   Dictionary.insert_sentence( book_code,  page,  paragraph,  sentence_no, sentence);
     if(currpara==paragraph&&currpg==page&&currbc==book_code){
              vecofparas.back().insert_sentence(sentence);
     }else{
          Xwords x(book_code,page,paragraph);
          x.insert_sentence(sentence);
          vecofparas.push_back(x);
          currpara=paragraph;
          currbc=book_code;
          currpg=page;
     }
   
    return;
}
void heapify(vector<Xwords>& v, int n, int i) {
    int largest = i;
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && v[left].score > v[largest].score){
          largest = left;
    }
       

    if (right < n && v[right].score > v[largest].score){
               largest = right;
    }
        

    if (largest != i) {
        Xwords temp=v[largest];
        v[largest]=v[i];
        v[i]=temp;
        heapify(v, n, largest);
    }
}
void buildMaxHeap(std::vector<Xwords>& v) {
    int n = v.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i);
    }
}
void QNA_tool::parascore(string sentence){
     int n=vecofparas.size();  
     vector<string> words;
      std::string word = "";
    for (char c : sentence)
    {
        if (!isValidChar2(c))
        {
            if (!word.empty())
            { 
                  int n=word.length();
                for (int i = 0; i < n; i++)
                {
                    word[i] = ToLower2(word[i]);
                }
                words.push_back(word);
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
          int n=word.length();
        for (int i = 0; i < n; i++)
        { 
            word[i] = ToLower2(word[i]);
        }
      words.push_back(word);
    }
  //  for(string w:words){
       // cout<<w<<" ";
  //  }
   // cout<<endl;
    for (int i=0;i<n;i++){
        double ans=0;
     for(string word:words){
          double num=(double)Dictionary.get_word_count(word)+1;
              double den=(double)unigram.get_word_count(word)+1;
                double score=(num)/(den);
            
        ans+=(double)(vecofparas[i].get_word_count(word))*(score);
     }
    vecofparas[i].score=ans;
    }
}
Xwords deleteMax(vector<Xwords>& v,int i) {
    Xwords maxElement = v[0];
    v[0] = v.back();
    v.pop_back();
    heapify(v, v.size()-i, 0);
    return maxElement;
}
Node* QNA_tool::get_top_k_para(string question, int k) {
    parascore(question);
    buildMaxHeap(vecofparas);
    Node* n=NULL;
    Node* tail=NULL;
   vector<Xwords> residue;
    int i=0;
    while(k>0){
       Xwords x=deleteMax(vecofparas,0);
       i++;
       residue.push_back(x);
   //  cout<<x.score<<endl;
        k--;
       if(n!=NULL){
        tail->right=new Node(x.book_code,x.page_no,x.para_no,0,0);
        tail=tail->right;
        tail->right=NULL;
     //   cout<<x.score<<endl;
       }else{
         //  cout<<x.score<<endl;
        n=new Node(x.book_code,x.page_no,x.para_no,0,0);
        tail=n;
       }
    }
  for(Xwords x:residue){
    vecofparas.push_back(x);
   }
    return n;
}

void QNA_tool::query(string question, string filename){
    // Implement your function here  
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: " << "Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){
    // first write the k paragraphs into different files
    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}
// int main(){
//     QNA_tool q;
//       q.insert_sentence(1,1,1,1,"Apple on the table on a car on the road");
//       double num=q.Dictionary.get_word_count("on")+1;
//      double den=q.unigram.get_word_count("on")+1;
//      cout<<num<<"  "<<q.unigram.get_word_count("on")<<endl;
//     return 0;
// }