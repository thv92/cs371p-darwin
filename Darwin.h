#ifndef RunDarwin_h
#define RunDarwin_h

#include <vector>
#include <iostream>
#include <string>
#include <array>

enum inst_t{HOP, LEFT, RIGHT, INFECT, GO, IF_EMPTY, IF_ENEMY, IF_RANDOM, IF_WALL};
enum dir_t {NORTH, SOUTH, EAST, WEST};
enum front_t {EMPTY, ENEMY, WALL};


struct instruction{
    int _n;
    inst_t _i;
};


//Creation: takes in name of species
//Takes in instructions
class Species{

    public:

        void addInstruction(std::string in);
        void executeInstruction(int c, front_t front);
        Species();
    private:
        std::vector<instruction> _instructions;
        static int species_count; //Species recognition
        const int _name;          //Name of species  
};  

//Execute instructions?
class Creature{

    public:
        Creature(Species s, std::string dir);
        
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
        std::vector<Creature*> _grid;
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