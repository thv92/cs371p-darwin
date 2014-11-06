#ifndef RunDarwin_h
#define RunDarwin_h

#include <vector>
#include <iostream>
#include <string>
#include <array>

enum inst_t { HOP, LEFT, RIGHT, INFECT, GO, IF_EMPTY, IF_ENEMY, IF_RANDOM, IF_WALL };
enum dir_t { NORTH, EAST, SOUTH, WEST };
enum front_t { EMPTY, ENEMY, WALL, FRIEND };


struct instruction{
    int _n;
    inst_t _i;
};

class Species{

    public:

        void addInstruction(std::string in);
        inst_t executeControls(int& pc, front_t front);
        Species(std::string n);
    private:
        std::vector<instruction> _instructions;
        std::string _name;          //Name of species  
};  

class Creature{

    public:
        Creature(Species s, std::string dir);
        dir_t getDirection();
        bool execute(front_t front, Creature& other);
        
    private:
        Species _s;
        dir_t _dir;
        int _pc;

};

//Create grid
//Add creatures
class Darwin{

    public:
        Darwin(int x, int y);
        void addCreature(Creature s, int x, int y);
        void printGrid();
    private:
        const int _height;
        const int _width;
        const int _size;
        int _turns;
        std::vector<Creature> _grid;
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