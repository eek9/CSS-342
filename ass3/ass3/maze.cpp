//
// Created by Eunhee Kim on 02/03/2020.
//

#include "maze.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

ostream& operator<<(ostream& out, const Maze& maze) {
    for (int row = 0; row < maze.height; row++) {
        for (int col = 0; col < maze.width; col++) {
            out << maze.field[row][col];
        }

        out << endl;
    }

    out << endl;

    return out;
}

// For CLion, need the following line in CMakeLists.txt so maze.txt is found
// at the same location as the cpp files
// # need to load data files from current directory as cpp files
// set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
Maze::Maze(const string& fileName) : field{ {0} }, width{ 0 }, height{ 0 }, exitRow{ 0 }, exitColumn{ 0 } {
    ifstream inFile;
    inFile.open(fileName.c_str());
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    inFile >> width >> height;
    inFile >> exitRow >> exitColumn;

    string str;
    getline(inFile, str);
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            inFile.get(field[row][col]);
            // cout << row << ", " << col << ": " << field[row][col] << endl;
        }

        getline(inFile, str);
    }
}

int Maze::getExitRow() const { return exitRow; }

int Maze::getExitColumn() const { return exitColumn; }

bool Maze::isClear(int row, int col) const { return field[row][col] == ' '; }

void Maze::markAsPath(int row, int col) { field[row][col] = '*'; }

void Maze::markAsVisited(int row, int col) { field[row][col] = '+'; }