//
// Created by Eunhee Kim on 02/03/20.
//

#include "creature.h"
#include "maze.h"
#include <iostream>

void test() {
    Maze m("maze.txt");
    cout << m << endl;
    Creature c(4, 4);
    cout << "Path: " << c.solve(m) << endl;
    cout << m << endl;

    Maze m1("maze1.txt");
    cout << m1 << endl;
    Creature c1(13, 7);
    cout << "Path: " << c1.solve(m1) << endl;
    cout << m1 << endl;

    Maze m2("maze2.txt");
    cout << m2 << endl;
    Creature c2(8, 8);
    cout << "Path: " << c2.solve(m2) << endl;
    cout << m2 << endl;

    Maze m3("maze3.txt");
    cout << m3 << endl;
    Creature c3(2, 1);
    cout << "Path: " << c3.solve(m3) << endl;
    cout << m3 << endl;
}

int main() {
    test();
    cout << "Done!" << std::endl;
    return 0;
}