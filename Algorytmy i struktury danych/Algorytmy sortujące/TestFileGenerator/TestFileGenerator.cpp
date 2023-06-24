#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

string testFilesFolderPath = "./TestFiles";

int main()
{
    cout << "How you want to name your test file ?" << endl;
    string fileName;
    cin >> fileName;

    ofstream outputFile;
    outputFile.open(testFilesFolderPath + "/" + fileName + ".txt");

    cout << "How many values you want to generate ?" << endl;
    unsigned int n;
    cin >> n;

    cout << "Write range of values <a , b>:" << endl;
    int a, b;
    cin >> a >> b;


    //generating test file

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(a, b);

    for (unsigned i = 0; i < n; i++)
    {
        outputFile << distribution(gen) << endl;
    }
}

