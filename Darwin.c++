
#include "Darwin.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>
#include <cassert>

//---------
// Species
//---------

Species::Species(std::string n):_name(n){}

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


inst_t Species::executeControls(int& pc, front_t front){
    
    instruction instruction = _instructions[pc];
    int r;
    //Perform controls till reach an action
    while (instruction._i > INFECT) {
        switch (instruction._i) {
            case GO:
                pc = instruction._n;
                instruction = _instructions[pc];
                break;
            case IF_EMPTY:
                if (front == EMPTY) {
                    pc = instruction._n;
                    instruction = _instructions[pc];
                } else {
                    instruction = _instructions[++pc];
                }
                break;
            case IF_ENEMY:
                  if(front == ENEMY){
                    pc = instruction._n;
                    instruction = _instructions[pc];
                  } else {
                    instruction = _instructions[++pc];
                  } 
                break;
            case IF_RANDOM:
                r = rand();
                if(r % 2 == 0) {
                    pc = instruction._n;
                    instruction = _instructions[pc];
                } else {
                    instruction = _instructions[++pc];
                }
                break;
            case IF_WALL:
                if(front == WALL){
                    pc = instruction._n;
                    instruction = _instructions[pc];
                } else {
                  instruction = _instructions[++pc];
                }
                break;
            default:
                break;
        }
    }
    return instruction._i;
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
dir_t Creature::getDirection() {
    return _dir;
}

bool Creature::execute(front_t front, Creature& other) {
    inst_t instruction = _s.executeControls(_pc, front);
    int d;
    switch(instruction) {
        case HOP:
            break;
        case LEFT:
            d = static_cast<int>(_dir);
            ++d;
            _dir = static_cast<dir_t>(d);
            _dir = _dir < 0 ? WEST : _dir; 
            break;
        case RIGHT:
            d = static_cast<int>(_dir);
            ++d;
            _dir = static_cast<dir_t>(d % 5);
            break;
        case INFECT:
            if(front == ENEMY) {
                dir_t temp = other._dir;
                other = *this;
                other._pc = 0;
                other._dir = temp;
            }
            break;
        default:
            assert(false);
            break;
    }
    ++_pc;
    return instruction == HOP;
}

//--------
// Darwin
//--------

Darwin::Darwin(int w, int h, int t): _height(h), _width(w), _size(w*h), _grid(_size), _turns(t){}

void Darwin::addCreature(Creature& s, int r, int c){
    int index = r + c * _width;
    _grid[index] = s;
}

void Darwin::simulate(){
    while (_turns > 0) {
                                                
        --_turns;
    }
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