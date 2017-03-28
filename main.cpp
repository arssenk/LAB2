#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>


using namespace std;
map<string, int> counted[100];
mutex lockGuard;


map<string, int> count_word(vector<string> words, int ID){
    map<string, int> D;
    for (int i = 0; i < words.size(); ++i){
        D[words[i]]++;
    }
    lockGuard.lock();
    counted[ID] = D;
    lockGuard.unlock();
    return D;
};
vector<vector<string>> read_file(string filename, int threads){
    ifstream in1(filename);
    string s;

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

int multithreading(int numb, vector<vector<string>> word){
    if (numb <= 0){
        cout << "Invalid number of threads";
        return -1;
    }
    else{
        int noOfThreads = numb;
        thread threadIDs[noOfThreads+1];
        for (int i = 0; i < noOfThreads; ++i){
            threadIDs[i] = thread(count_word, word[i], i);
        }
        for(int iter = 0; iter < numb; iter++)
        {
            threadIDs[iter].join();
        }
        return 1;
    }
}
map<string, int> merge(int numOfThreads){
    map<string, int> answer;
    cout << counted[0].size() << endl;
    for (int i = 1; i < numOfThreads; ++i){
        cout << counted[i].size() << endl;
        for (auto it=counted[i].begin(); it!=counted[i].end(); ++it) {
            if ( counted[0][it->first] )
                counted[0][it->first] += it->second;
            else
                counted[0][it->first] = it->second;
        }
    }
    answer = counted[0];
    cout << counted[0].size() << endl;
    return answer;

};




void testik(){
    int stop  = 0;
    for (int i = 0; i < 4; ++i){
        for (auto k = counted[i].begin(); k != counted[i].end(); ++k){
            if (stop == 5){
                stop=0;
                break;
            }
            stop++;
            cout << k->first<< " : " << k->second << " || " << i <<  endl;
        }
    }
}
void writeAToFile(string path, vector<pair<string, int>> words){
    ofstream res(path);
    for (int i = 0; i < words.size(); ++i)
        res << words[i].first << ": " << words[i].second << endl;
    res.close();
}
//void writeToFile(string path, multimap<int, string> words){
//    ofstream res(path);
//    map <string, int>::iterator it;
//    for (multimap<int, string>::iterator itr = words.begin(); itr != words.end(); ) {
//        /* ... process *itr ... */
//        cout << itr->first << ": " << itr->second << endl;
//        itr++;
//        /* Now, go skip to the first entry with a new key. */
//        multimap<int, string>::iterator curr = itr;
//
//    }
//        //res << it->first << ": " << it->second << endl;
//    res.close();
//}
vector<pair<string, int>> getToVector(map<string, int> words){
    map <string, int>::iterator it;
    vector<pair<string, int>> wordVector;
    for (it = words.begin(); it != words.end(); it++){
        wordVector.push_back(make_pair(it->first, it->second));}
    return wordVector;
};
bool sortbysec(const pair<string,int> &a,
               const pair<string,int> &b)
{
    return (a.second > b.second);
}
bool sortbyfirst(const pair<string,int> &a,
               const pair<string,int> &b)
{
    return (a.first < b.first);
}
int main() {

    int threads = 4;
    vector<vector<string>> words;
    words = read_file("/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/data.txt", threads);
    string path="/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/res.txt";
    string path_a="/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/res_a.txt";
    multithreading(threads, words);
    map<string, int> output;
    output = merge(threads);
    vector<pair<string, int>> kk;
    kk = getToVector(output);
    sort(kk.begin(), kk.end(), sortbysec);
    writeAToFile(path, kk);
    sort(kk.begin(), kk.end(), sortbyfirst);
    writeAToFile(path_a, kk);

//    for(int i = 0; i < kk.size(); i++)
//    {
//        cout << kk[i].first << ", " << kk[i].second << endl;
//    }

//    auto cmp = [](std::pair<string, int> const & a, std::pair<string, int> const & b)
//    {
//        return a.second != b.second?  a.second < b.second : a.first < b.first;
//    };

//    sort(output.begin(), output.end(), descending<string, int>());

    //readConfigFile("../config.txt");
//setlocale(LC_ALL, "Russian");
    //readConfigFile("/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/config.txt");
    //number_of_threads(2, words);

    return 0;
}

