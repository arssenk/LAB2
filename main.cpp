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
    for (int i = 1; i < numOfThreads; ++i){
        for (auto it=counted[i].begin(); it!=counted[i].end(); ++it) {
            if ( counted[0][it->first] )
                counted[0][it->first] += it->second;
            else
                counted[0][it->first] = it->second;
        }
    }
    answer = counted[0];
    return answer;

};

void writeAToFile(string path, vector<pair<string, int>> words){
    ofstream res(path);
    for (int i = 0; i < words.size(); ++i)
        res << words[i].first << ": " << words[i].second << endl;
    res.close();
}

vector<pair<string, int>> getToVector(map<string, int> words){
    map <string, int>::iterator it;
    vector<pair<string, int>> wordVector;
    for (it = words.begin(); it != words.end(); it++){
        wordVector.push_back(make_pair(it->first, it->second));}
    return wordVector;
};

int main() {
    string path_to_data, path_to_res_n, path_to_res_a;
    vector<vector<string>> words;
    vector<pair<string, int>> vectorOfPairs;
    //Ці нижні ми маєм з конфіг брати, в тебе та функція.
    int threads = 4;
    path_to_data = "/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/data.txt";
    path_to_res_a ="/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/res_a.txt";
    path_to_res_n = "/home/arsen/Documents/Year_2/Semester_2/ACS/Proj/LAB2/res.txt";



    words = read_file(path_to_data, threads);

    multithreading(threads, words);
    map<string, int> output;
    output = merge(threads);

    vectorOfPairs = getToVector(output);
    sort(vectorOfPairs.begin(), vectorOfPairs.end(), sortbysec);
    writeAToFile(path_to_res_n, vectorOfPairs);
    sort(vectorOfPairs.begin(), vectorOfPairs.end(), sortbyfirst);
    writeAToFile(path_to_res_a, vectorOfPairs);

    return 0;
}

