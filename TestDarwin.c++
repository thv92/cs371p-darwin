#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;


// -----------
// TestDrawin
// -----------
TEST(Species, species_getName_1) 
{
	Species s("food");
    assert(s.getName() == "food");
}

TEST(Species, species_getName_2) 
{
	Species s("rover");
    assert(s.getName() == "rover");
}

TEST(Species, species_getName_3) 
{
	Species s("hopper");
    assert(s.getName() == "hopper");
}

TEST(Species, species_add_and_execute_1) 
{
	Species food("food");
    food.addInstruction("left");
    food.addInstruction("go 0");
    int pc = 0;
    inst_t result = food.executeControls(pc, EMPTY);
    assert(result == LEFT);
}

TEST(Species, species_add_and_execute_2) 
{
	Species food("food");
    food.addInstruction("left");
    food.addInstruction("go 0");
    int pc = 1;
    inst_t result = food.executeControls(pc, EMPTY);
    assert(result == LEFT);
}

TEST(Species, species_add_and_execute_3) 
{
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    int pc = 1;
    inst_t result = hopper.executeControls(pc, EMPTY);
    assert(result == HOP);
}

TEST(Species, species_add_and_execute_4) 
{
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    int pc = 0;
    inst_t result = hopper.executeControls(pc, EMPTY);
    assert(result == HOP);
}

TEST(Species, species_add_and_execute_5) 
{
	Species trap("trap");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    int pc = 0;
    inst_t result = trap.executeControls(pc, EMPTY);
    assert(result == LEFT);
}

TEST(Species, species_add_and_execute_6) 
{
	Species trap("trap");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    int pc = 0;
    inst_t result = trap.executeControls(pc, ENEMY);
    assert(result == INFECT);
}

TEST(Species, species_add_and_execute_7) 
{
	Species trap("trap");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    int pc = 3;
    inst_t result = trap.executeControls(pc, ENEMY);
    assert(result == INFECT);
}

TEST(Species, species_add_and_execute_8) 
{
	Species trap("trap");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    int pc = 4;
    inst_t result = trap.executeControls(pc, ENEMY);
    assert(result == INFECT);
}

TEST(Species, species_add_and_execute_9) 
{
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

    int pc = 0;
    inst_t result = rover.executeControls(pc, ENEMY);
    assert(result == INFECT);
}

TEST(Species, species_add_and_execute_10) 
{
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

    int pc = 0;
    inst_t result = rover.executeControls(pc, ENEMY);
    assert(result == INFECT);
}

TEST(Species, species_add_and_execute_11) 
{
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

    int pc = 0;
    inst_t result = rover.executeControls(pc, EMPTY);
    assert(result == HOP);
}

TEST(Species, species_add_and_execute_12) 
{
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

    srand(0);
    int pc = 0;
    inst_t result = rover.executeControls(pc, WALL);
    assert(result == LEFT);
}

TEST(Species, species_compare_1) 
{
	Species food1("food");
    food1.addInstruction("left");
    food1.addInstruction("go 0");

    Species food2("food");
    food2.addInstruction("left");
    food2.addInstruction("go 0");

    assert(food1 == food2);
}

TEST(Species, species_compare_2) 
{
	Species food1("food");
    food1.addInstruction("left");
    food1.addInstruction("go 0");

    Species food2("food");
    food2.addInstruction("right");
    food2.addInstruction("go 0");

    assert(food1 == food2);
}

TEST(Species, species_compare_3) 
{
	Species food1("food");
    food1.addInstruction("left");
    food1.addInstruction("go 0");

    Species food2("rover");
    food2.addInstruction("left");
    food2.addInstruction("go 0");

    assert(!(food1 == food2));
}