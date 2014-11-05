
#include "Darwin.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

//---------
// Species
//---------

int Species::species_count;
Species::Species():_name(++species_count){}


void Species::addInstruction(std::string in){
    instruction instruction;

    int space = in.find_first_of(' ');
    instruction._n = atoi(in.substr(space+1, in.length()).c_str());
    in = in.substr(0, space);

    if(in == "hop"){
        instruction._i = HOP;
        instruction._n = -1;
    }else if(in == "left"){
        instruction._i = LEFT;
        instruction._n = -1;
    }else if(in == "right"){
        instruction._i = RIGHT;
        instruction._n = -1;
    }else if(in == "infect"){
        instruction._i = INFECT;
        instruction._n = -1;
    }else if(in == "go"){
        instruction._i = GO;
    }else if(in == "if_empty"){
        instruction._i = IF_EMPTY;
    }else if(in == "if_enemy"){
        instruction._i = IF_ENEMY;
    }else if(in == "if_random"){
        instruction._i = IF_RANDOM;
    }else if(in == "if_wall"){
        instruction._i = IF_WALL;
    }else{
        throw std::invalid_argument("Illegal instruction.");
    }
    _instructions.push_back(instruction);
}


//Add creature parameter?
void Species::executeInstruction(int pc, front_t front){
    instruction instruction = _instructions[pc];


    //Perform controls till reach an action
    while (instruction._i > INFECT && instruction._n < (int) _instructions.size()) {
        switch (instruction._i) {
            case GO:
                instruction = _instructions[instruction._n];
                break;
            case IF_EMPTY:
                if (front == EMPTY) {
                    instruction = _instructions[instruction._n];
                } else if(++instruction._n < (int) _instructions.size()) {
                    instruction = _instructions[++instruction._n];
                }
                break;
            case IF_ENEMY:
                  if(front == ENEMY){
                    instruction = _instructions[instruction._n];
                  } else if(++instruction._n < (int) _instructions.size()){
                    instruction = _instructions[++instruction._n];
                  } 
                break;
            case IF_RANDOM:
                std::cout << "Random" << std::endl;
                break;
            case IF_WALL:
                if(front == WALL){
                  instruction = _instructions[instruction._n];
                }else if(++instruction._n < (int) _instructions.size()){
                  instruction = _instructions[++instruction._n];
                }
                break;
            default:
                break;
        }
    }

    //Creature performs action and sets counter

}

//----------
// Creature
//----------

//Creature Constructor
Creature::Creature(Species s, std::string dir): _s(s){

    //Set direction of the creature
    if(dir == "north"){
      _dir = NORTH;
    }else if(dir == "south"){
      _dir = SOUTH;
    }else if(dir == "east"){
      _dir = EAST;
    }else if(dir == "west"){
      _dir = WEST;
    }else{
      throw std::invalid_argument("Invalid direction.");
    }
}

//------------------
// Creature Actions
//------------------

//parameters for actions(pc)






//--------
// Darwin
//--------

Darwin::Darwin(int x, int y): _height(x), _width(y), _size(x*y), _grid(_size){}

void Darwin::addCreature(Creature s, int x, int y){
    int index = x + y * _width;
    _grid[index] = &s;
}

// index = X + Y * Width;
// Y = (int)(index / Width)
// X = index - (Y * Width)


void Darwin::printGrid(){
    std::cout << std::setw(4) << " ";
    for(int i = 0; i < _width; ++i)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;

   int i = 0;
   while(i < _size){
        std::cout << std::setw(4) << i/_width;
        for(int j = 0; j < _width; ++j){

            int y = (int) (j/_width);
            int x = j - (y - _width); 

            std::cout << std::setw(4) << ".";
        }
        std::cout << std::endl;

        i+=_width;
    }

    std::cout << std::endl;
}