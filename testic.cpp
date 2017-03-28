#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sys/stat.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    using namespace std;

    string s;
    ifstream in1("/home/oksana/Документи/data.txt");

    map<string, int> D;

    while (in1 >> s)
        D[s]++;
    in1.close();

//    const char *path="/home/oksana/Документи/result.txt";



    std::ofstream res("result.txt");


    map <string, int>::iterator it;
    for (it = D.begin(); it != D.end(); it++)
        res << it->first << ": " << it->second << endl;
    res.close();
//    mkdir("myfolder.txt");
    return 0;/*
        setlocale(LC_ALL, "Russian");
        using namespace std;

        string s;
        ifstream in1("data.txt");

        map<string, int> D;

        while (in1 >> s)
            D[s]++;
        in1.close();

        map <string, int>::iterator it;
        ofstream res("result.txt");
        for (it = D.begin(); it != D.end(); it++)
            res << it->first << ": " << it->second << endl;
        return 0;*/
}