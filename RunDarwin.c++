// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2014
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"


// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    Species food("food");
    food.addInstruction("left");
    food.addInstruction("go 0");
    
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    Species trap("trap");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    Species rover("rover");
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */
    Darwin board1(8, 8, 5);
    Creature b1_f1(food, 2);
    Creature b1_h1(hopper, 1);
    Creature b1_h2(hopper, 2);
    Creature b1_h3(hopper, 3);
    Creature b1_h4(hopper, 0);
    Creature b1_f2(food, 1);

    board1.addCreature(b1_f1, 0, 0);
    board1.addCreature(b1_h1, 3, 3);
    board1.addCreature(b1_h2, 3, 4);
    board1.addCreature(b1_h3, 4, 4);
    board1.addCreature(b1_h4, 4, 3);
    board1.addCreature(b1_f2, 7, 7);

    board1.simulate();


    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */
    Darwin board2(7, 9, 5);

    Creature t1(trap, 3);
    Creature h1(hopper, 2);
    Creature r1(rover, 1);
    Creature t2(trap, 0);

    board2.addCreature(t1, 0, 0);
    board2.addCreature(h1, 3, 2);
    board2.addCreature(r1, 5, 4);
    board2.addCreature(t2, 6, 8);
    board2.simulate();



    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    Darwin board3(72, 72, 1000);
    std::vector<Creature> storeCreatures;
    
    for(int i = 0; i < 10; ++i){
        int pos = rand()%5184;
        int row = pos/72;
        int col = pos%72;
        Creature k(food, rand()%4);
        board3.addCreature(k, row, col);
    }
    for(int i = 0; i < 10; ++i){
        int pos = rand()%5184;
        int row = pos/72;
        int col = pos%72;
        Creature k(hopper, rand()%4);
        board3.addCreature(k, row, col);

    }
    for(int i = 0; i < 10; ++i){
        int pos = rand()%5184;
        int row = pos/72;
        int col = pos%72;
        Creature k(rover, rand()%4);
        board3.addCreature(k, row, col);
    }
    for(int i = 0; i < 10; ++i){
        int pos = rand()%5184;
        int row = pos/72;
        int col = pos%72;
        Creature k(trap, rand()%4);
        board3.addCreature(k, row, col);

    }

    board3.simulate();

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;}
