#include <Windows.h>
#include <conio.h>
#include <thread> 
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>


using namespace std::chrono_literals;
using namespace std;

HANDLE console;
vector <int> Currentdata;
vector <int> Futuredata;

void Numbercatcher(string Values)                                           //Converting string data from file to int         
{
    stringstream tmp;
    string temp;
    int found;
    tmp << Values;
    while (!tmp.eof())
    {
        tmp >> temp;
        if (stringstream(temp) >> found)
        {
            Currentdata.push_back(found);
        }
    }
}

void lifesupport(int width, int height) {                                      //Applying rules of Conway 
    int population = 0;
    for (int i = 0; i < Currentdata.size();i++) {
        population = 0;
        if (Currentdata[i] == 2) {
            Futuredata.push_back(2);
        }
        if (Currentdata[i] == 1) {
            if ((Currentdata[i - 1]         == 1)) population++;
            if ((Currentdata[i + 1]         == 1)) population++;
            if ((Currentdata[i - width]     == 1)) population++;
            if ((Currentdata[i - width - 1] == 1)) population++;
            if ((Currentdata[i - width +1]  == 1)) population++;
            if ((Currentdata[i + width]     == 1)) population++;
            if ((Currentdata[i + width - 1] == 1)) population++;
            if ((Currentdata[i + width +1]  == 1)) population++;
            if (population == 2 || population == 3) {
                Futuredata.push_back(1);
            }
            if (population < 2 || population > 3) {
                Futuredata.push_back(0);
            }
            }
        if (Currentdata[i] == 0) {
            if ((Currentdata[i - 1]         == 1)) population++;
            if ((Currentdata[i + 1]         == 1)) population++;
            if ((Currentdata[i - width]     == 1)) population++;
            if ((Currentdata[i - width - 1] == 1)) population++;
            if ((Currentdata[i - width + 1] == 1)) population++;
            if ((Currentdata[i + width]     == 1)) population++;
            if ((Currentdata[i + width - 1] == 1)) population++;
            if ((Currentdata[i + width + 1] == 1)) population++;
            if (population == 3) Futuredata.push_back(1);
            else
                Futuredata.push_back(0);
        }
    }
    Currentdata.clear();
    Currentdata = Futuredata;
    Futuredata.clear();
}

void Draw(int width, int height) {                                          //Displaying image of board
    COORD pos;                                                                              
    pos.X = 0;
    pos.Y = 0;                                   
    SetConsoleCursorPosition(console, pos);
    for (int i = 0; i < Currentdata.size();i++) {
        if (pos.X == width) {
            pos.X = 0;
            pos.Y++;
        }
        SetConsoleCursorPosition(console, pos);
        if (Currentdata[i] == 2) {
            SetConsoleTextAttribute(console, BACKGROUND_GREEN);
            cout << "#";
            pos.X++;
        }
        if (Currentdata[i] == 1) {
            SetConsoleTextAttribute(console, BACKGROUND_RED);
            cout << " ";
            pos.X++;
        }
        if (Currentdata[i] == 0) {
            pos.X++;
        }
    
    }
}

int main() {
    string line;
    fstream file;
    int width, height, input = 0;
    vector <string> Values;
    string path;

    console = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "Input path to your image.(Remember to use double backslash!!): ";      //Taking path from user
    cin >> path;

    file.open(path, ios::in);                                                       //Colecting data from file
    if (file.good() == true)
    {
        while (!file.eof())
        {
            getline(file, line);
            Values.push_back(line);
        }
        file.close();
    }
    else {
        cout << "Wrong path!!";
        return 0;
    }
    for (int i = 0;i <= Values.size() - 1;i++) {                                   //Changing data type
        Numbercatcher(Values[i]);
    }
    width = Currentdata[0];
    Currentdata.erase(Currentdata.begin());
    height = Currentdata[0];
    Currentdata.erase(Currentdata.begin());
    cout << "If you want to go to next stages automatically press a." << endl<<"To stop press X in right top corner."<< endl << "If you want to go to next stages manually press m and press it again anytime you want to go further."<< endl << "To stop press ESC.";
    
    
    while (input != 27) {                                                         //Main part of program count and show game of life
        if (_kbhit()) {
            input = _getch();
            if (input == 65 || input == 97) {
                while (true) {
                    SetConsoleTextAttribute(console, 1);
                    system("cls");
                    Draw(width, height);
                    lifesupport(width, height);
                    Sleep(5000);
                }
            }
            if (input == 77 || input == 109) {
                SetConsoleTextAttribute(console, 1);
                system("cls");
                Draw(width, height);
                lifesupport(width, height);
            }
        }
    }
}