#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string pathTestFileBalanced = "../TestFileGenerator/TestFiles/balanced.txt";
string pathTestFileBig = "../TestFileGenerator/TestFiles/bigValues.txt";
string pathTestFileMuch = "../TestFileGenerator/TestFiles/muchValues.txt";


vector<int> CountingSort(vector<int> toSort)
{
    vector<int> countingPlus, countingMinus;
    for (int element : toSort)
    {
        if (element >= 0)
        {
            if (countingPlus.size() < element + 1)
            {
                countingPlus.resize(element + 1, 0);
            }
            countingPlus[element]++;
        }
        else
        {
            if (countingMinus.size() < -element + 1)
            {
                countingMinus.resize(-element + 1, 0);
            }
            countingMinus[-element]++;
        }
    }

    vector<int> sorted;
    for (int i = countingMinus.size() - 1; i > 0; i--)
    {
        for (int j = 1; j <= countingMinus[i]; j++)
        {
            sorted.push_back(-i);
        }
    }

    for (int i = 0; i < countingPlus.size(); i++)
    {
        for (int j = 1; j <= countingPlus[i]; j++)
        {
            sorted.push_back(i);
        }
    }

    return sorted;
}

bool CheckSorting(vector<int> sorted)
{
    for (int i = 0; i < sorted.size() - 1; i++)
    {
        if (sorted[i + 1] < sorted[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{

    ifstream input;
    input.open(pathTestFileBalanced);

    ofstream output;
    output.open("./SortedOutput.txt");

    vector<int> toSort;

    int x;
    while (input >> x)
    {
        toSort.push_back(x);
    }

    auto startTime = chrono::high_resolution_clock::now();
    vector<int> sorted = CountingSort(toSort);
    auto stopTime = chrono::high_resolution_clock::now();

    // printing result: -------------------------------------------------
    cout << "sorting completed in: " << ((chrono::duration<float>)(stopTime - startTime)).count() << " seconds, with status: ";
    if (CheckSorting) cout << "sorted";
    else cout << "not sorted";

    for (int y : sorted)
    {
        output << y << endl;
    }

    cout << "\n\nWanna see result here (press any button)?\n\n";
    getchar();

    int i = 1;
    for (int y : sorted)
    {
        cout << i << ". " << y << endl;
        i++;
    }
}

