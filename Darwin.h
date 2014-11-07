#ifndef RunDarwin_h
#define RunDarwin_h

//----------
// includes
//----------

#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

//-------
// enums
//-------

/**
 * inst_t instructions and actions 
 * dir_t cardinal directions
 * front_t identifying what space in front is
 */

enum inst_t { HOP, LEFT, RIGHT, INFECT, GO, IF_EMPTY, IF_ENEMY, IF_RANDOM, IF_WALL };
enum dir_t { WEST, NORTH, EAST, SOUTH};
enum front_t { EMPTY, ENEMY, WALL, FRIEND};



//-------------
// instruction
//-------------

/**
 * stores Instruction code and Instruction
 */
struct instruction{
    int _n;
    inst_t _i;
};

//

//---------
// Species
//---------
class Species{

    public:
        Species();


        //---------
        // Species
        //---------

        /**
         * @param n name of species
         */
        Species(std::string n);

        //---------------
        //addInstruction
        //---------------
        
        /**
         * add instructions with format of "inst n"
         * @param in takes in instruction with format "inst n"
         */
        void addInstruction(std::string in);
        
        
        //-----------------
        // executeControls
        //-----------------
       
        /**
         * perform all of the controls until an action is reached
         * @param pc program counter of creature
         * @param front direction of creature
         * @return current instruction creature is on
         */
        
        inst_t executeControls(int& pc, front_t front);
        
        
        //------
        // ==
        //------
        
        /**
         * Overloaded == for Species to compare their names
         * @param in takes in instruction with format "inst n"
         * @return if the two names are equal
         */
        bool operator==(const Species &rhs);
        


        //----------
        // getName
        //----------
        /**
         * get the name of species
         * @return name of Species
         */
        const std::string getName() const;
    private:
        //Vector of all instructions of species
        std::vector<instruction> _instructions;
        std::string _name;          //Name of species  
};  

class Creature{

    public:

        //---------------------
        // Default Constructor
        //---------------------
        Creature();


        //------------------------
        // Assignment Constructor
        //------------------------
        
        /**
         * Creates creature with species and where it's currently facing
         * @param s Species for Creature
         * @param dir direction creature is facing
         */

        Creature(Species s, int dir);


        //--------------
        // getDirection
        //--------------
       
        /**
         * gets direction creature is currently facing
         * @return direction of Creature
         */

        dir_t getDirection();

        //----------
        // execute
        //----------
        
        /**
         * perform action instruction
         * @param front who's in front
         * @param other creature in front if any
         * @return whether or not it hop action is in play
         */

        bool execute(front_t front, Creature& other);
        
        //----------------
        // compareSpecies
        //----------------
        
        /**
         * compare the species between two creatures
         * @param rhs other creature to compare against
         * @return if same species
         */

        bool compareSpecies(const Creature &rhs);
        
        //----------------
        // getSpeciesName
        //----------------
        
        /**
         * gets name of species
         * @return name of Species for Creature
         */

        const std::string getSpeciesName() const;

    private:

        Species _s; //What the creature's species is
        dir_t _dir; //Direction creature is currently facing
        int _pc;    //PC that creature is currently on

};


//--------------
// creatureInfo
//--------------


/**
* c creature stored
* pos current position of creature
*/


struct creatureInfo{
    Creature c;
    int pos;
};

//Create grid
//Add creatures
class Darwin{

    public:
        //----------
        // Constructor
        //----------
        
        /**
         * builds board given x y and turns
         * @param h number of columns
         * @param w number of rows
         * @param t number of turns to simulate
         */
        Darwin(int h, int w, int t);

        //-------------
        // addCreature
        //-------------
        
        /**
         * adds creature onto grid
         * @param s Creature to add
         * @param r y coordinate on grid
         * @param c x coordinate on grid
         */
        void addCreature(Creature s, int r, int c);
        
        //-----------
        // printGrid
        //-----------
        
        /**
         * prints grid with creatures
         */

        void printGrid(std::ostream& w);


        //----------
        // simulate
        //----------
        
        /**
         * simulate each creature's turn
         */

        void simulate();

        //--------
        // front
        //--------
       
        /**
         * gets what's in front of creature
         * @param dir direction of creature
         * @param pos position of creature on grid
         * @return pair of enum and id
         */

        std::pair<front_t, int> front(int pos, dir_t dir);


        //--------
        // front
        //--------
       
        /**
         * gets position of who's in front of creature
         * @param pos position of creature to find front of
         * @param dir direction creature is facing
         * @return pair of r, c of next space depending on direction
         */
        std::pair<int, int> front_coordinate(int pos, dir_t dir);
       

        //-----------
        // in_bounds
        //-----------
       
        /**
         * checks to see if r,c is in bounds
         * @param coord r,c values
         * @return bool if the pair is within bounds of grid
         */

        bool in_bounds(std::pair<int, int> coord);

        //-----------------
        // coordToPosition
        //-----------------
       
        /**
         * changes pair coordinates to row major order position on grid
         * @param coord r,c values
         * @return actual position on grid
         */

        int coordToPosition(std::pair<int, int> coord);


        //-------------------
        // orderCreatureTurn
        //-------------------
       
        /**
         * orders which creature goes first based on the grid
         */

        void orderCreatureTurn();


    private:
        const int _height;
        const int _width;
        const int _size;
        int _turns;         //total turns
        int _turns_gone;    //turns that have passed

        std::vector<int> _grid; //Grid filled with creature ids
        std::unordered_map<int, creatureInfo> _creatureInfo;  //filled with creature id and creature info
        std::vector<int> _creaturesOnGrid;  //vector of creatures' ids


       
};





#endif // RunDarwin_h