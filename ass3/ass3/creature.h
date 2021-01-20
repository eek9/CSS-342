//
// Created by Eunhee Kim on 02/03/20.
//
#ifndef CREATURE_H
#define CREATURE_H

#pragma once

#include "maze.h"
#include <ostream>

using namespace std;

class Creature {
public:
    friend ostream& operator<<(ostream& out, const Creature& creature);

public:
    Creature(int row, int col);

    // returns a string in the form of NNEEN
    // (where N means North, E means East, etc)
    string solve(Maze& maze);

    bool atExit(const Maze& maze) const;
    string goNorth(Maze& maze);
    string goSouth(Maze& maze);
    string goEast(Maze& maze);
    string goWest(Maze& maze);

private:
    int row;
    int col;
    //I added this string instance variable to record all the
    //directions it will take to get the creature to its destination
    string path;
};

#endif // !CREATURE_H