#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

string getData(char* filePath, int pos, int size)
{
    fstream f;
    f.open(filePath, ios::binary | ios::in);
    if(!f)
    {
        cout << "Failed to open file: " << filePath << endl;
        return "Error";
    }
    else
    {
        cout << "Current file is: " << filePath <<endl;
    }
    char tmp;
    stringstream sstmp;
    f.seekg(pos);
    for(int i=0; i<size; i++)
    {
        //if((tmp = f.get()) != EOF) //Using this will lost FFs.
        //{
            tmp = f.get();
            sstmp << tmp;
        //}
    }
    f.close();
    return sstmp.str();
}

int getSize(char* filePath)
{
    fstream f;
    f.open(filePath, ios::binary | ios::in);
    if(!f)
    {
        cout << "Failed to open file: " << filePath << endl;
        system("pause");
        return -1;
    }
    f.ignore(numeric_limits<streamsize>::max());
    streamsize length = f.gcount();
    f.clear();
    f.seekg(0, ios::beg);
    f.close();
    return length;
}

int main(int argc, char* argv[])
{
    char* filePath = argv[1];
    stringstream ssfinalPath;
    ssfinalPath << filePath << ".mid";
    string sfinalPath = ssfinalPath.str();
    const char* finalPath = sfinalPath.c_str();

    cout << "RMI to MID Converter v1.0 by shezik" <<endl;
    cout << endl;

    if(argc == 1)
    {
        cout << "Please specify a file." << endl;
        system("pause");
        return -1;
    }

    string id = getData(filePath, 0, 4);
    if(id != "RIFF")
    {
        if(id == "MThd")
        {
            cout << "This file is originally an MID file, or is already converted to MID." <<endl;
        }
        else
        {
            cout << "The file type is neither RMI nor MID. Maybe this file is corrupted." << endl;
        }
        system("pause");
        return -1;
    }

    cout << "File type confirmed. Now working..." << endl;

    int fileSize = getSize(filePath);
    if(fileSize == -1)
    {
        system("pause");
        return -1;
    }
    string midData = getData(filePath, 20, fileSize-20);
    if(midData == "Error")
    {
        system("pause");
        return -1;
    }

    fstream of;
    if(!of)
    {
        cout << "Failed to write to file: " << finalPath << endl;
        system("pause");
        return -1;
    }
    of.open(finalPath, ios::binary | ios::out);
    of << midData;
    of.close();

    cout << "Done." << endl;
    cout << endl;
    //system("pause"); //Meaningless, and also prevents user from using this tool effectively.

    return 0;
}
