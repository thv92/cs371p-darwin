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
    ASSERT_EQ(s.getName(), "food");
}

TEST(Species, species_getName_2) 
{
	Species s("rover");
    ASSERT_EQ(s.getName(), "rover");
}

TEST(Species, species_getName_3) 
{
	Species s("hopper");
    ASSERT_EQ(s.getName(),"hopper");
}

TEST(Species, species_add_and_execute_1) 
{
	Species food("food");
    food.addInstruction("left");
    food.addInstruction("go 0");
    int pc = 0;
    inst_t result = food.executeControls(pc, EMPTY);
    ASSERT_EQ(result, LEFT);
}

TEST(Species, species_add_and_execute_2) 
{
	Species food("food");
    food.addInstruction("left");
    food.addInstruction("go 0");
    int pc = 1;
    inst_t result = food.executeControls(pc, EMPTY);
    ASSERT_EQ(result, LEFT);
}

TEST(Species, species_add_and_execute_3) 
{
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    int pc = 1;
    inst_t result = hopper.executeControls(pc, EMPTY);
    ASSERT_EQ(result, HOP);
}

TEST(Species, species_add_and_execute_4) 
{
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    int pc = 0;
    inst_t result = hopper.executeControls(pc, EMPTY);
    ASSERT_EQ(result, HOP);
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
    ASSERT_EQ(result, LEFT);
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
    ASSERT_EQ(result, INFECT);
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
    ASSERT_EQ(result, INFECT);
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
    ASSERT_EQ(result, INFECT);
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
    ASSERT_EQ(result, INFECT);
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
    ASSERT_EQ(result, INFECT);
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
    ASSERT_EQ(result, HOP);
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
    ASSERT_EQ(result, RIGHT);
}

TEST(Species, species_compare_1) 
{
	Species food1("food");
    food1.addInstruction("left");
    food1.addInstruction("go 0");

    Species food2("food");
    food2.addInstruction("left");
    food2.addInstruction("go 0");

    ASSERT_TRUE(food1 == food2);
}

TEST(Species, species_compare_2) 
{
	Species food1("food");
    food1.addInstruction("left");
    food1.addInstruction("go 0");

    Species food2("food");
    food2.addInstruction("right");
    food2.addInstruction("go 0");

    ASSERT_TRUE(food1 == food2);
}

TEST(Species, species_compare_3) 
{
	Species food1("food");
    food1.addInstruction("left");
    food1.addInstruction("go 0");

    Species food2("rover");
    food2.addInstruction("left");
    food2.addInstruction("go 0");

    ASSERT_TRUE(!(food1 == food2));
}

TEST(Creature, construct_and_get_direction_1)
{
    Species food("food");
    Creature f(food, 0);

    ASSERT_EQ(f.getDirection(), WEST);
}

TEST(Creature, construct_and_get_direction_2)
{
    Species food("food");
    Creature f(food, 1);

    ASSERT_EQ(f.getDirection(), NORTH);
}

TEST(Creature, construct_and_get_direction_3)
{
    Species food("food");
    Creature f(food, 3);

    ASSERT_EQ(f.getDirection(), SOUTH);
}

TEST(Creature, construct_and_get_direction_4)
{
    Species food("trap");
    Creature f(food, 2);

    ASSERT_EQ(f.getDirection(), EAST);
}

TEST(Creature, construct_and_get_direction_5)
{
    Species trap("I AM A SUPER LONG SPECIES NAME FOR TESTING THAT THINGS ARE OKAY");
    Creature f(trap, 2);

    ASSERT_EQ(f.getDirection(), EAST);
}

TEST(Creature, construct_and_get_direction_6)
{
    Species trap("I AM A SUPER LONG SPECIES NAME FOR TESTING THAT THINGS ARE OKAY");

    try{
        Creature f(trap, -1);
    }
    catch (std::exception& e) {
        std::string msg = e.what();
        ASSERT_EQ(msg, "Invalid direction.");
    }
}

TEST(Creature, construct_and_get_direction_7)
{
    Species trap("I AM A SUPER LONG SPECIES NAME FOR TESTING THAT THINGS ARE OKAY");

    try{
        Creature f(trap, 4);
    }
    catch (std::exception& e) {
        std::string msg = e.what();
        ASSERT_EQ(msg, "Invalid direction.");
    }
}

TEST(Creature, get_species_name_1)
{
    Species food("food");
    Creature f(food, 1);

    ASSERT_EQ(f.getSpeciesName(), "food");
}

TEST(Creature, get_species_name_2)
{
    Species food("gotcha");
    Creature f(food, 3);

    ASSERT_EQ(f.getSpeciesName(), "gotcha");
}

TEST(Creature, get_species_name_3)
{
    Species food("trap");
    Creature f(food, 2);

    ASSERT_EQ(f.getSpeciesName(), "trap");
}

TEST(Creature, get_species_name_4)
{
    Species trap("I AM A SUPER LONG SPECIES NAME FOR TESTING THAT THINGS ARE OKAY");
    Creature f(trap, 2);

    ASSERT_EQ(f.getSpeciesName(), "I AM A SUPER LONG SPECIES NAME FOR TESTING THAT THINGS ARE OKAY");
}

TEST(Creature, compare_species_1)
{
    Species food("food");
    Creature f1(food, 1);
    Creature f2(food, 2);

    ASSERT_TRUE(f1.compareSpecies(f2));
}

TEST(Creature, compare_species_2)
{
    Species food("food");
    Species food2("food");
    Creature f1(food, 1);
    Creature f2(food2, 2);

    ASSERT_TRUE(f1.compareSpecies(f2));
}

TEST(Creature, compare_species_3)
{
    Species food("food");
    Species food2("good game");
    Creature f1(food, 1);
    Creature f2(food2, 2);

    ASSERT_FALSE(f1.compareSpecies(f2));
}

TEST(Creature, execute_1)
{
    Species trap ("trap");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    Creature t(trap, 0);

    ASSERT_FALSE(t.execute(EMPTY, t));
}

TEST(Creature, execute_2)
{
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature h(hopper, 0);

    ASSERT_TRUE(h.execute(EMPTY, h));
}

TEST(Creature, execute_3)
{
    Species trap ("trap");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
    Species hopper("hopper");
    Creature t(trap, 0);
    Creature t2(hopper, 3);

    ASSERT_FALSE(t.execute(ENEMY, t2));
    ASSERT_TRUE(t.compareSpecies(t2));
}

TEST(Creature, turning_1)
{
    Species test("rover");
    test.addInstruction("left");
    test.addInstruction("right"); 

    srand(0);
    Creature r(test, 0);
    r.execute(WALL, r);
    ASSERT_EQ(r.getDirection(), SOUTH);
    r.execute(WALL, r);
    ASSERT_EQ(r.getDirection(), WEST);
}

TEST(Creature, turning_2)
{
    Species test("rover");
    test.addInstruction("left");
    test.addInstruction("go 0");

    srand(0);
    Creature r(test, 0);
    r.execute(WALL, r);
    ASSERT_EQ(r.getDirection(), SOUTH);
    r.execute(WALL, r);
    ASSERT_EQ(r.getDirection(), EAST);
    r.execute(WALL, r);
    ASSERT_EQ(r.getDirection(), NORTH);
    r.execute(WALL, r);
    ASSERT_EQ(r.getDirection(), WEST);
}

TEST(Darwin, darwin_1)
{
    Darwin board(8, 8, 1);
    std::ostringstream w;
    std::string r = "Turn = 0.\n  01234567\n0 ........\n1 ........\n2 ........\n3 ........\n4 ........\n5 ........\n6 ........\n7 ........\n\n";

    board.printGrid(w);
    ASSERT_EQ(w.str(), r);
}

TEST(Darwin, darwin_2)
{
    Darwin board(7, 9, 1);
    std::ostringstream w;
    std::string r = "Turn = 0.\n  012345678\n0 .........\n1 .........\n2 .........\n3 .........\n4 .........\n5 .........\n6 .........\n\n";
    board.printGrid(w);
    ASSERT_EQ(w.str(), r);
}

TEST(Darwin, darwin_3)
{
    Darwin board(1, 1, 1);
    std::ostringstream w;
    std::string r = "Turn = 0.\n  0\n0 .\n\n";
    board.printGrid(w);
    ASSERT_EQ(w.str(), r);
}

TEST(Darwin, darwin_4)
{
    Darwin board(2, 2, 1);
    std::ostringstream w;
    std::string r = "Turn = 0.\n  01\n0 ..\n1 ..\n\n";
    board.printGrid(w);
    ASSERT_EQ(w.str(), r);
}

TEST(Darwin, darwin_5)
{
    Darwin board(8, 8, 1);
    std::pair<int, int> test(0, 0);
    ASSERT_FALSE(board.in_bounds(test));
}

TEST(Darwin, darwin_6)
{
    Darwin board(8, 8, 1);
    std::pair<int, int> test(7, 7);
    ASSERT_FALSE(board.in_bounds(test));
}

TEST(Darwin, darwin_7)
{
    Darwin board(8, 8, 1);
    std::pair<int, int> test(0, 8);
    ASSERT_TRUE(board.in_bounds(test));
}

TEST(Darwin, darwin_8)
{
    Darwin board(8, 8, 1);
    std::pair<int, int> test(8, 0);
    ASSERT_TRUE(board.in_bounds(test));
}

TEST(Darwin, darwin_coordToPosition1)
{
    Darwin board(1, 1, 1);
    std::pair<int, int> test(0, 0);
    int result = board.coordToPosition(test);
    ASSERT_EQ(result, 0);
}

TEST(Darwin,  darwin_coordToPosition2)
{
    Darwin board(9, 9, 1);
    std::pair<int, int> test(8, 8);
    int result = board.coordToPosition(test);
    ASSERT_EQ(result, 80);
}

TEST(Darwin,  darwin_coordToPosition3)
{
    Darwin board(1, 5, 1);
    std::pair<int, int> test(0, 4);
    int result = board.coordToPosition(test);
    ASSERT_EQ(result, 4);
}

TEST(Darwin,  darwin_coordToPosition4)
{
    Darwin board(5, 1, 1);
    std::pair<int, int> test(0, 4);
    int result = board.coordToPosition(test);
    ASSERT_EQ(result, 4);
}

TEST(Darwin,  darwin_coordToPosition5)
{
    Darwin board(8, 8, 1);
    std::pair<int, int> test(5, 5);
    int result = board.coordToPosition(test);
    ASSERT_EQ(result, 45);
}

TEST(Darwin, darwin_addCreature)
{
    Species food("food");
    Creature c(food, 0);
    Darwin board(1, 1, 1);
    board.addCreature(c, 0, 0);

    std::ostringstream w;
    std::string r = "Turn = 0.\n  0\n0 f\n\n";
    board.printGrid(w);
    ASSERT_EQ(w.str(), r);
}

TEST(Darwin, darwin_addCreature1)
{
    Species food("food");
    Creature c(food, 0);
    Darwin board(2, 2, 1);
    board.addCreature(c, 0, 0);
    board.addCreature(c, 1, 1);

    std::ostringstream w;
    std::string r = "Turn = 0.\n  01\n0 f.\n1 .f\n\n";
    board.printGrid(w);
    ASSERT_EQ(w.str(), r);
}

TEST(Darwin, darwin_addCreature2)
{
    Species food("food");
    Creature c(food, 0);
    Darwin board(2, 2, 1);
    board.addCreature(c, 0, 0);
    board.addCreature(c, 1, 1);

    std::ostringstream w;
    std::string r = "Turn = 0.\n  01\n0 f.\n1 .f\n\n";
    board.printGrid(w);
    ASSERT_EQ(w.str(), r);
}

TEST(Darwin, darwin_addCreature3)
{
    Species food("food");
    Species x("xterminator");
    Creature c(food, 0);
    Creature c2(x, 0);
    Darwin board(2, 2, 1);
    board.addCreature(c, 0, 0);
    board.addCreature(c, 1, 1);
    board.addCreature(c2, 0, 1);
    board.addCreature(c2, 1, 0);

    std::ostringstream w;
    std::string r = "Turn = 0.\n  01\n0 fx\n1 xf\n\n";
    board.printGrid(w);
    ASSERT_EQ(w.str(), r);
}

TEST(Darwin, darwin_front_coordinate)
{
    Darwin board(1, 1, 1);
    std::pair<int, int> test(0,1);
    ASSERT_EQ(test, board.front_coordinate(0, EAST));
}

TEST(Darwin, darwin_front_coordinate2)
{
    Darwin board(3, 3, 1);
    std::pair<int, int> test(1,2);
    ASSERT_EQ(test, board.front_coordinate(4, EAST));
}

TEST(Darwin, darwin_simulate)
{
    Species food("food");
    food.addInstruction("left");
    food.addInstruction("go 0");
    
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

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

    Creature f(food, 0);
    Creature h(hopper, 3);
    Creature r(rover, 1);

    Darwin board(2, 2, 1);
    board.addCreature(f, 0, 0);
    board.addCreature(h, 0, 1);
    board.addCreature(r, 1, 0);

    board.simulate();

    std::ostringstream w;
    std::string res = "Turn = 2.\n  01\n0 r.\n1 rh\n\n";
    board.printGrid(w);
    ASSERT_EQ(w.str(), res);
}