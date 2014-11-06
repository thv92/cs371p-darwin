#ifndef RunDarwin_h
#define RunDarwin_h

#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

enum inst_t { HOP, LEFT, RIGHT, INFECT, GO, IF_EMPTY, IF_ENEMY, IF_RANDOM, IF_WALL };
enum dir_t { NORTH, EAST, SOUTH, WEST };
enum front_t { EMPTY, ENEMY, WALL, FRIEND};


struct instruction{
    int _n;
    inst_t _i;
};

class Species{

    public:
        Species();
        void addInstruction(std::string in);
        inst_t executeControls(int& pc, front_t front);
        Species(std::string n);
        bool operator==(const Species &rhs);
        const std::string getName() const;
    private:
        std::vector<instruction> _instructions;
        std::string _name;          //Name of species  
};  

class Creature{

    public:
        Creature();
        Creature(Species s, std::string dir);
        dir_t getDirection();
        bool execute(front_t front, Creature& other);
        bool compareSpecies(const Creature &rhs);
        const std::string getSpeciesName() const;

    private:
        Species _s;
        dir_t _dir;
        int _pc;

};

//Create grid
//Add creatures
class Darwin{

    public:
        Darwin(int x, int y, int t);
        void addCreature(Creature s, int r, int c);
        void printGrid();
        void simulate();
    private:
        const int _height;
        const int _width;
        const int _size;
        int _turns;
        std::vector<Creature> _creatures;
        std::vector<int> _grid;
        std::unordered_map<int, int> _positions;
        std::pair<front_t, int> front(int pos, dir_t dir);
        std::pair<int, int> front_coordinate(int pos, dir_t dir);
        std::pair<int, int> new_position(int pos, dir_t dir);
        bool in_bounds(std::pair<int, int> coord);
        int coordToPosition(std::pair<int, int> coord);
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