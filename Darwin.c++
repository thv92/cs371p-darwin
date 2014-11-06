
#include "Darwin.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <string>
#include <unordered_map>

#define DEBUGSC false
#define DEBUGD false

//---------
// Species
//---------

Species::Species(std::string n):_name(n){}

Species::Species(){}

const std::string Species::getName() const{
    return _name;
}
void Species::addInstruction(std::string in){
    instruction instruction;

    int space = in.find_first_of(' ');
    if(space > 0){
        instruction._n = atoi(in.substr(space+1, in.length()).c_str());
        in = in.substr(0, space);
    }else{
        if(DEBUGSC) std::cout << "Adding control instructions " << std::endl;
        instruction._n = -1;
    }

    if(in == "hop"){
        instruction._i = HOP;
    }else if(in == "left"){
        instruction._i = LEFT;
    }else if(in == "right"){
        instruction._i = RIGHT;
    }else if(in == "infect"){
        instruction._i = INFECT;
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

bool Species::operator==( const Species &rhs){
    // std::cout << " compare in species " << (*this)._name <<  std::endl;

    return (*this)._name == rhs._name;
}

inst_t Species::executeControls(int& pc, front_t front){
    
    instruction instruction = _instructions[pc];
    int r;
    //Perform controls till reach an action
    while (instruction._i > INFECT) {
        switch (instruction._i) {
            case GO:
                if(DEBUGSC) std::cout << " GO " << std::endl;
                pc = instruction._n;
                instruction = _instructions[pc];
                break;
            case IF_EMPTY:
                if(DEBUGSC) std::cout << " IF_EMPTY "  << std::endl;
                if (front == EMPTY) {
                    pc = instruction._n;
                    instruction = _instructions[pc];
                } else {
                    instruction = _instructions[++pc];
                }
                break;
            case IF_ENEMY:
                if(DEBUGSC) std::cout <<  " IF_ENEMY " << std::endl;
                  if(front == ENEMY){
                    pc = instruction._n;
                    instruction = _instructions[pc];
                  } else {
                    instruction = _instructions[++pc];
                  } 
                break;
            case IF_RANDOM:
                if(DEBUGSC) std::cout <<  "IF_RANDOM" << std::endl;
                r = rand();
                if(r % 2 == 0) {
                    pc = instruction._n;
                    instruction = _instructions[pc];
                } else {
                    instruction = _instructions[++pc];
                }
                break;
            case IF_WALL:
                if(DEBUGSC) std::cout <<  " IF_WALL " << std::endl;
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

Creature::Creature(){}

Creature::Creature(Species s, std::string dir)
    : _s(s), _pc(0) {

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

const std::string Creature::getSpeciesName() const{

    return _s.getName();
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
            if(DEBUGSC) std::cout <<  " HOP " << std::endl;
            break;
        case LEFT:
            if(DEBUGSC) std::cout << " LEFT "  << std::endl;
            d = static_cast<int>(_dir);
            --d;
            _dir = static_cast<dir_t>(d);
            _dir = _dir < 0 ? WEST : _dir; 
            break;
        case RIGHT:
            if(DEBUGSC) std::cout <<  " RIGHT " << std::endl;
            d = static_cast<int>(_dir);
            ++d;
            _dir = static_cast<dir_t>(d % 5);
            break;
        case INFECT:
            if(DEBUGSC) std::cout <<  " INFECT " << std::endl;
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

bool Creature::compareSpecies(const Creature &rhs){
    // std::cout << " Creature compare species" << std::endl;
    return (*this)._s == rhs._s;

}

//--------
// Darwin
//--------

Darwin::Darwin(int h, int w, int t): _height(h), _width(w), _size(w*h), _turns(t), _grid(_size, -1) {}

void Darwin::addCreature(Creature s, int r, int c){
    int position = c + r * _width;
    _creatures.push_back(s);
    int id = _creatures.size() - 1;
    _grid[position] = id;
    _positions.insert(std::pair<int, int>(id, position));
}

void Darwin::simulate(){
    printGrid();
    while (_turns > 0) {
        std::unordered_map<int,int>::iterator b = _positions.begin();
        std::unordered_map<int,int>::iterator e = _positions.end();

        while (b != e) {
            int id = b->first;
            int pos = b->second;

            Creature *c = &_creatures[id];
            dir_t dir = c->getDirection();

            if(DEBUGD) std::cout << " Creature Direction: " << dir << " " << c->getSpeciesName()<< std::endl;

            std::pair<front_t, int> x = front(pos, dir);

            Creature *other;

            if(x.second > -1 && x.second < (int) _creatures.size())
                other = &_creatures[x.second];
            else
                other = c;

            bool hopped = c->execute(x.first, *other);

            if (hopped) {
                std::pair<int, int> fc = front_coordinate(pos, dir);
                
                int new_pos = coordToPosition(fc);

                if(!in_bounds(fc) && x.first == EMPTY){
                    _positions[id] = new_pos;
                    _grid[pos] = -1;
                    _grid[new_pos] = id;
                }
            }
            ++b;
        }
        printGrid();
        --_turns;
    }
}

std::pair<int, int> Darwin::front_coordinate(int pos, dir_t dir) {
    int row = pos/_width;
    int col = pos - (row * _width);
    int f_row = row;
    int f_col = col;
    switch(dir) {
        case NORTH:
            f_row = row - 1;
            break;
        case EAST:
            f_col = col + 1;
            break;
        case SOUTH:
            f_row = row + 1;
            break;
        case WEST:
            f_col = col - 1;
            break;
    }
    return std::pair<int, int>(f_row, f_col);
}

bool Darwin::in_bounds(std::pair<int, int> coord) {
    int row = coord.first;
    int col = coord.second;
    return row < 0 || row >= _height || col < 0 || col >= _width;
}

int Darwin::coordToPosition(std::pair<int, int> coord) {
    return coord.second + coord.first * _width;
}

std::pair<front_t, int> Darwin::front(int pos, dir_t dir) {
    std::pair<int, int> fc = front_coordinate(pos, dir);

    if(in_bounds(fc)) {
        return std::pair<front_t, int>(WALL, -1);
    }

    int front_pos = coordToPosition(fc);

    assert(front_pos < (int) _grid.size());
    int id = _grid[front_pos];
    if(DEBUGD) std::cout << " Inside front function " <<  fc.first << " " << fc.second<< std::endl;
    if(DEBUGD) std::cout << " Inside front function " <<  pos << " " << front_pos << std::endl;
    
    if (id == -1) {
        return std::pair<front_t, int>(EMPTY, -1);
    }
    else {
        bool status = _creatures[_grid[pos]].compareSpecies(_creatures[id]);
        if(DEBUGD) std::cout << "status: " << status <<std::endl;
        return status ? std::pair<front_t, int>(FRIEND, -1) : std::pair<front_t, int>(ENEMY, id);
    }
    
}

void Darwin::printGrid(){

	std::cout << "  ";
	for(int i = 0; i < _width; ++i)
	std::cout << i % 10;
	std::cout << std::endl;

    int i = 0;
    while(i < _size){
    	std::cout << (i/_height) % 10<< " ";
        for(int col = 0; col < _width; ++col){
        	int id = _grid[i];
        	if(id != -1) {
	            std::unordered_map<int, int>::iterator getCreatureFromMap = _positions.find(_grid[i]);
	            std::cout << _creatures[getCreatureFromMap->first].getSpeciesName().substr(0,1);
            }else{
                std::cout << ".";
            }
            ++i;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}