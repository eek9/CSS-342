//
// Created by Eunhee Kim on 02/03/20.
//
#ifndef MAZE_H
#define MAZE_H

#pragma once

#include <ostream>

using namespace std;

enum CELL { CLEAR, WALL, PATH, VISITED };

class Maze {
    friend ostream& operator<<(ostream& out, const Maze& maze);

public:
    explicit Maze(const string& fileName);
    bool isClear(int row, int col) const;
    void markAsPath(int row, int col);
    void markAsVisited(int row, int col);
    int getExitRow() const;
    int getExitColumn() const;

private:
    static const int MAX_SIZE = 100;

    char field[MAX_SIZE][MAX_SIZE];
    int width;
    int height;
    int exitRow;
    int exitColumn;
};

#endif // !MAZE_H