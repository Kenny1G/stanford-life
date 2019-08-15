// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include<thread>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
using namespace std;

void createGeneration(Grid<string> &g);
void displayGeneration(const Grid<string> &g);
int numOfNeighbours(Grid<string> &g, int row, int column);
Grid<string> nextGeneration(Grid<string> g);

int main()
{
    cout << "Welcome to the CS 106B Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl;
    cout << endl;

    Grid<string> generation;
    createGeneration(generation);
    displayGeneration(generation);

    char ch = 'v';
    while(ch != 'q')
    {
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> ch;
        ch = tolower(ch);
        if (ch == 't')
        {
            generation = nextGeneration(generation);
            displayGeneration(generation);
        }
        else if (ch == 'a')
        {
            int frames;
            cout << "How many frames?";
            cin >> frames;
            while (cin.fail())
            {
                cout << "Illegal integer format. Try again";
                cin.clear();
                cin.ignore(256,'\n');
                cin >> frames;
            }
                for (int i = 0; i < frames; i++)
                {
                    generation = nextGeneration(generation);
                    displayGeneration(generation);
                    this_thread::sleep_for(chrono::milliseconds(50));
                }
        }
        else
        {}
    }
    cout << "Have a nice Life!";
    return 0;
}

void createGeneration(Grid<string> &g)
{
    ifstream infile;
    promptUserForFile(infile, "Grid input file name?");
    Vector<string> fileContent;
    Vector<string> mainContent;
    string line;
    int row;
    int column;
    while(getline(infile,line))
    {
        fileContent.add(line);
    }
    row = stringToInteger(fileContent[0]);
    column = stringToInteger(fileContent[1]);
    mainContent = fileContent.subList(2,row);

    Grid<string> generation(row,column);

    for (int i = 0; i < mainContent.size(); i++)
    {
        for (string::size_type y = 0; y < mainContent[i].size(); y++)
        {
            generation[i][y] = mainContent[i][y];
        }
    }
    g = generation;
    //cout << generation << endl;

    infile.close();
}

Grid<string> nextGeneration(Grid<string> g)
{
    Grid<string> n = g;
    for (int r = 0; r < g.height(); r++)
    {
        for (int c = 0; c < g.width(); c++)
        {
            switch (numOfNeighbours(g,r,c))
            {
            case 2:
                break;
            case 3:
                n[r][c] = "X";
                break;
            default:
                n[r][c] = "-";
                break;
            }
        }
    }
    return n;
}

int numOfNeighbours(Grid<string> &g, int row, int column)
{
    int neighbours = 0;
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int y = column -1; y <= column + 1; y++)
        {
            if(g.inBounds(i,y))
            {
                if (g[i][y] == "X")
                {
                    neighbours++;
                }
            }
        }
    }
    if (g[row][column] == "X")
    {
        return neighbours - 1;
    }
    return neighbours;
}

void displayGeneration(const Grid<string> &g)
{
    for (int r = 0; r < g.numRows(); r++)
    {
        for (int c = 0; c < g.numCols(); c++)
        {
            cout << g[r][c];
        }
        cout << endl;
    }
}
