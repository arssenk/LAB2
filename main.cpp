#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <cstring>

using namespace std;

map<string, int> count_word(vector<string> words, int ID){
    map<string, int> D;
    for (int i = 0; i < words.size(); ++i){
        D[words[i]]++;
    }
    return D;
};
vector<vector<string>> read_file(string filename, int threads){
    ifstream in1(filename);
    string s;
     map counted[threads];
    vector<string> words;
    vector<vector<string>> listOfWords;
    for (int i = 0; i < threads; ++i) listOfWords.push_back(words);
    map<string, int> D;
    int i = threads;
    while (in1 >> s) {
        --i;
        listOfWords[i].push_back(s);
        if (i==0) i = threads;
    }
    in1.close();
    return listOfWords;
}
//void readConfigFile(string fileName){
//    string line;
//    string delimiter = "=";
//    size_t pos = 0;
//    string infile, out_by_a, out_by_n;
//    int threads;
//    string token;
//    ifstream myfile (fileName);
//    if (myfile.is_open())
//    {
//        while ( getline (myfile,line) )
//        {
//
//            while ((pos = line.find(delimiter)) != string::npos) {
//                token = line.substr(0, pos);
//                if (token.compare("infile")== 0){
//                    token = line.substr(0, pos);
//                    infile = token;
//                }
//                else if (token.compare("out_by_a")== 0){
//                    token = line.substr(0, pos);
//                    out_by_a = token;
//                }
//                else if (token.compare("out_by_n")== 0){
//                    token = line.substr(0, pos);
//                    out_by_n = token;
//                }
//                else if (token.compare("threads")== 0){
//                    threads = atoi(token.c_str());
//                    cout << "th" ;
//                }
//                else{
//                    cout << token << "sd"<< endl;
//                }
//                line.erase(0, pos + delimiter.length());
//            }
//
//        }
//        myfile.close();
//
//    }
//
//    else cout << "Unable to open file";
//    cout << out_by_a;
//}
int multithreading(int numb, vector<string> word){
    if (numb <= 0){
        cout << "Invalid number of threads";
        return NULL;
    }
    else{
        int noOfThreads = numb;
        int chunkSize;
        thread threadIDs[noOfThreads+1];
//        chunkSize = (int) (word.size() % numb);
        for (int i = 0; i < noOfThreads; ++i){
            threadIDs[i] = std::thread(count_word, word);
        }
    }
}
int main() {
    read_file("/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/data.txt", 4);
//setlocale(LC_ALL, "Russian");
    //readConfigFile("/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/config.txt");
    //number_of_threads(2, words);
    const char *path="/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/res.txt";
    ofstream res(path);
    map <string, int>::iterator it;
//    for (it = D.begin(); it != D.end(); it++)
//        res << it->first << ": " << it->second << endl;
//    res.close();
    return 0;
}

