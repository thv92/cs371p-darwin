#ifndef RunDarwin_h
#define RunDarwin_h

#include <vector>
#include <iostream>
#include <string>

enum inst_t{HOP, LEFT, RIGHT, INFECT, GO, IF_EMPTY, IF_ENEMY, IF_RANDOM, IF_WALL};
enum dir_t {NORTH, SOUTH, EAST, WEST};
enum front_t {EMPTY, ENEMY, WALL}


struct instruction{
    int _n;
    inst_t _i;
};


//Creation: takes in name of species
//Takes in instructions
class Species{

    public:
        void addInstruction(std::string in);
        void executeInstruction(int c);
    private:
        std::vector<instruction> _instructions;
        std::string _name;
};

//Execute instructions?
class Creature{

    public:
        Creature(Species s, std::string dir);
    
    private:
        Species _s;
        dir_t _dir;
        int pc;

};



//Create grid
//Add creatures
class Darwin{

    public:

    private:

};





#endif // RunDarwin_h

//Actions

// ----
// hop
// ----

// -----
// left
// -----


// ------
// right
// ------

// -------
// infect
// -------


//Controls

// ---------
// if_empty
// ---------


// ---------
// if_wall
// ---------


// ---------
// if_random
// ---------


// --------
// if_enemy
// --------

// ---
// go
// ---