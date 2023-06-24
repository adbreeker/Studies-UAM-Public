#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

//input files paths
string pathTestFile = "./Files/Input/testFile.txt";
string pathExcerciseFile = "./Files/Input/we50.txt";

//assistant files paths
string pathMergedFile = "./Files/Assistant/mergedFile.txt";
string pathAssistant1File = "./Files/Assistant/assistantFile1.txt";
string pathAssistant2File = "./Files/Assistant/assistantFile2.txt";

//output files paths
string pathSortedFile = "./Files/Output/sorted.txt";

int getFileLength(ifstream & file)
{
    int length = 0;
    string line;
    while (getline(file, line))
    {
        length++;
    }
    file.clear();
    file.seekg(0, ios::beg);
    return length;
}

void separate(ifstream& input)
{
    ofstream temp1, temp2;
    temp1.open(pathAssistant1File, std::ofstream::out | std::ofstream::trunc);
    temp2.open(pathAssistant2File, std::ofstream::out | std::ofstream::trunc);
    temp1.close();
    temp2.close();

    temp1.open(pathAssistant1File, ios_base::app);
    temp2.open(pathAssistant2File, ios_base::app);

    int lastInt = NULL;
    int lastFile = 1;
    int series1 = 1;
    int series2 = 1;

    int fileLength = getFileLength(input);

    for (int i = 0; i < fileLength; i++)
    {
        int number;
        input >> number;

        if (lastInt == NULL)
        {
            if (lastFile == 1)
            {
                temp1 << series1 << " " << number << endl;
            }
            if (lastFile == 2)
            {
                temp2 << series2 << " " << number << endl;
            }
        }
        else
        {
            if (lastInt <= number)
            {
                if (lastFile == 1)
                {
                    temp1 << series1 << " " << number << endl;
                }
                if (lastFile == 2)
                {
                    temp2 << series2 << " " << number << endl;
                }
            }
            else
            {
                if (lastFile == 1)
                {
                    temp2 << series2 << " " << number << endl;
                    lastFile = 2;
                    series1++;
                }
                else if (lastFile == 2)
                {
                    temp1 << series1 << " " << number << endl;
                    lastFile = 1;
                    series2++;
                }
            }
        }

        lastInt = number;

    }

    temp1.close();
    temp2.close();
    input.close();
}

void merge(ifstream& input1, ifstream& input2)
{
    ofstream temp;
    temp.open(pathMergedFile, std::ofstream::out | std::ofstream::trunc);
    temp.close();

    temp.open(pathMergedFile, ios_base::app);

    int i1Length = getFileLength(input1);
    int i2Length = getFileLength(input2);

    int actuallI1 = 0;
    int actuallI2 = 0;
    while (actuallI1 < i1Length || actuallI2 < i2Length)
    {
        int i1series = NULL, i1number = NULL;
        int i2series = NULL, i2number = NULL;

        streampos oldI1Pos, oldI2Pos;

        if (actuallI1 < i1Length)
        {
            oldI1Pos = input1.tellg();
            actuallI1++;
            input1 >> i1series >> i1number;
            // cout << "taking from first " << i1series << " " << i1number << endl;
        }
        if (actuallI2 < i2Length)
        {
            oldI2Pos = input2.tellg();
            actuallI2++;
            input2 >> i2series >> i2number;
            //cout << "taking from second " << i2series << " " << i2number << endl;
        }

        if (i1series != NULL && i2series != NULL)
        {
            if (i1series == i2series)
            {
                if (i2number < i1number)
                {
                    //cout << i2number << " < " << i1number << " putting from second " << i2number << endl;
                    temp << i2number << endl;
                    actuallI1--;
                    input1.seekg(oldI1Pos);
                }
                else
                {
                    //cout << i1number << " < " << i2number << " putting from first " << i1number << endl;
                    temp << i1number << endl;
                    actuallI2--;
                    input2.seekg(oldI2Pos);
                }
            }
            else
            {
                if (i1series < i2series)
                {
                    //cout << "diffrent series, putting from first " << i1number << endl;
                    temp << i1number << endl;
                    actuallI2--;
                    input2.seekg(oldI2Pos);
                }
                else
                {
                    //cout << "diffrent series, putting from second " << i2number << endl;
                    temp << i2number << endl;
                    actuallI1--;
                    input1.seekg(oldI1Pos);
                }
            }
        }
        else
        {
            if (i1series == NULL)
            {
                //cout << "first is empty, putting from second " << i2number << endl;
                temp << i2number << endl;
            }
            if (i2series == NULL)
            {
                //cout << "second is empty, puting from first " << i1number << endl;
                temp << i1number << endl;
            }
        }
    }

    temp.close();
    input1.close();
    input2.close();
}

void copyFile(ifstream& original, ofstream& copy)
{
    string line;
    while (getline(original, line))
    {
        copy << line << endl;
    }

    original.close();
    copy.close();
}

void printFile(ifstream& file, char separator)
{
    file.clear();
    file.seekg(0, ios::beg);

    int fileLength = getFileLength(file);

    for (int i = 1; i <= fileLength; i++)
    {
        int number;
        file >> number;
        if (separator == '\n')
        {
            cout << i << ".  " << number << separator;
        }
        else
        {
            cout << number << separator;
        }
        
    }

    file.clear();
    file.seekg(0, ios::beg);
}

void NaturalConnectingSort()
{
    while (true)
    {
        ifstream merged;
        merged.open(pathMergedFile);
        separate(merged);

        ifstream assistant1, assistant2;
        assistant1.open(pathAssistant1File);
        assistant2.open(pathAssistant2File);

        if (getFileLength(assistant1) == 0 || getFileLength(assistant2) == 0)
        {
            merge(assistant1, assistant2);
            break;
        }
        else
        {
            merge(assistant1, assistant2);
        }
    }
}

int main()
{
    //creating copy of to sort file
    ifstream startingValues;
    //startingValues.open(pathTestFile); test file
    startingValues.open(pathExcerciseFile);
    ofstream inputFileCopy;
    inputFileCopy.open(pathMergedFile);

    copyFile(startingValues, inputFileCopy);

    //counting sort time
    auto startTime = chrono::high_resolution_clock::now();
    NaturalConnectingSort();
    auto stopTime = chrono::high_resolution_clock::now();



    // printing result: -------------------------------------------------
    cout << "sorting completed in: " << (chrono::duration_cast<chrono::microseconds>(stopTime - startTime)).count() << " microseconds\n\n";

    // coping last merged into sorted file
    ifstream merged;
    merged.open(pathMergedFile);
    ofstream sorted;
    sorted.open(pathSortedFile);

    copyFile(merged, sorted);


    //printing sort result
    ifstream sortedOutput;
    sortedOutput.open(pathSortedFile);

    printFile(sortedOutput, '\n');
    sortedOutput.close();
    
}

