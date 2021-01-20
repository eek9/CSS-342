//
// Created by Eunhee Kim on 02/03/20.
//

#include "creature.h"
#include "maze.h"
#include <algorithm>

using namespace std;

// prints current location of creature, for example C(7,3)
ostream& operator<<(ostream& out, const Creature& creature) { 
    return out << "(" << creature.row << "," << creature.col << ")" << endl; 
}

//this function is the a constructor that initializes the row and column
//of where the creature will start in the maze
Creature::Creature(int row, int col) : row(row), col(col), path(""){}

//this function returns a bool to check if whether the creature is
//at the exit or not
bool Creature::atExit(const Maze& maze) const { 
    return (row==maze.getExitRow()) && (col==maze.getExitColumn()); 
}

// returns a string in the form of NNEEN
// (where N means North, E means East, etc)
string Creature::solve(Maze& maze) {
    //the creature will initially mark the starting part of 
    //where they are in the maze
    maze.markAsPath(row, col);
    //the creature will check if it is at the exit and will return
    //a blank path because they are already at the location of their
    //destination
    if (atExit(maze)) {
        return path;
    }
    if (!atExit(maze)) {
        path = goWest(maze);
    }
    if (!atExit(maze)) {
        path = goEast(maze);
    }
    if (!atExit(maze)) {
        path = goSouth(maze);
    }
    if (!atExit(maze)) {
        path = goNorth(maze);
    }
    reverse(path.begin(), path.end());
    return path;
}

//this function will lead the creature to go North
string Creature::goNorth(Maze& maze) {
    string p;
    //if the direction of where the creature is trying to go
    //in the maze (in this case, North) is clear, it will
    //mark it as a path and continue
    if (maze.isClear(row-1, col)) {
        row -= 1;
        maze.markAsPath(row, col);
        //if the creature is at the exit, it will return the
        //direction it went to reach the destination
        if (atExit(maze)) {
            p += "N";
        }
        //if the creature is not at the exit, it will continue
        //going north and check if the local variable string is empty.
        //when p == "", it will try going through all the other directions
        //and recurse until it finds a path that leads to the exit.
        else {
            p = goNorth(maze);
            if (p == "") {
                p = goEast(maze);
                if (p == "") {
                    p = goWest(maze);
                    if (p == "") {
                        maze.markAsVisited(row, col);
                        row += 1;
                    }
                    else {
                        p += "N";
                    }
                }
                else {
                    p += "N";
                }
            }
            else {
                p += "N";
            }
        }
    }
    //if the direction that the creature is trying to go to is not clear,
    //it will return a blank string
    else {
        p = "";
    }
    //after running the whole, function, it will return the overall string of p
    //that returns the directions it took.
    return p;
}

//this function will lead the creature to go West
string Creature::goWest(Maze& maze) {
    string p;
    //if the direction of where the creature is trying to go
    //in the maze (in this case, West) is clear, it will
    //mark it as a path and continue
    if (maze.isClear(row, col - 1)) {
        col -= 1;
        maze.markAsPath(row, col);
        //if the creature is at the exit, it will return the
        //direction it went to reach the destination
        if (atExit(maze)) {
            p += "W";
        }
        //if the creature is not at the exit, it will continue
        //going west and check if the local variable string is empty.
        //when p == "", it will try going through all the other directions
        //and recurse until it finds a path that leads to the exit.
        else {
            p = goWest(maze);
            if (p == "") {
                p = goNorth(maze);
                if (p == "") {
                    p = goSouth(maze);
                    if (p == "") {
                        maze.markAsVisited(row, col);
                        col += 1;
                    }
                    else {
                        p += "W";
                    }
                }
                else {
                    p += "W";
                }
            }
            else {
                p += "W";
            }
        }
    }
    else {
        p = "";
    }
    return p;
}

//this function will lead the creature to go East
string Creature::goEast(Maze& maze) { 
    string p;
    //if the direction of where the creature is trying to go
    //in the maze (in this case, East) is clear, it will
    //mark it as a path and continue
    if (maze.isClear(row, col + 1)){
        col += 1;
        maze.markAsPath(row, col);
        //if the creature is at the exit, it will return the
        //direction it went to reach the destination
        if (atExit(maze)) {
            p += "E";
        }
        //if the creature is not at the exit, it will continue
        //going east and check if the local variable string is empty.
        //when p == "", it will try going through all the other directions
        //and recurse until it finds a path that leads to the exit.
        else {

            p = goEast(maze);
            if (p == "") {
                p = goNorth(maze);
                if (p == "") {
                    p = goSouth(maze);
                    if (p == "") {
                        maze.markAsVisited(row, col);
                        col -= 1;
                    }
                    else {
                        p += "E";
                    }
                }
                else {
                    p += "E";
                }
            }
            else {
                p += "E";
            }
        }
    }
    else {
        p = "";
    }
    return p;
}

//this function will lead the creature to go South
string Creature::goSouth(Maze& maze) { 
    string p;
    //if the direction of where the creature is trying to go
    //in the maze (in this case, South) is clear, it will
    //mark it as a path and continue
    if (maze.isClear(row+1, col)) {
        row += 1;
        maze.markAsPath(row, col);
        //if the creature is at the exit, it will return the
        //direction it went to reach the destination
        if (atExit(maze)) {
            p += "S";
        }
        //if the creature is not at the exit, it will continue
        //going south and check if the local variable string is empty.
        //when p == "", it will try going through all the other directions
        //and recurse until it finds a path that leads to the exit.
        else {
            p = goSouth(maze);
            if (p == "") {
                p = goEast(maze);
                if (p == "") {
                    p = goWest(maze);
                    if (p == "") {
                        maze.markAsVisited(row, col);
                        row -= 1;
                    }
                    else {
                        p += "S";
                    }
                }
                else {
                    p += "S";
                }
            }
            else {
                p += "S";
            }
        }
    }

    else {
        p = "";
    }
    return p;
}