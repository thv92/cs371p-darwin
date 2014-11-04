
#include "Darwin.h"
#include <iostream>
#include <string>
#include <stdexcept>

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

void executeInstruction(int pc, front_t front){
    inst_t instruction = instructions[i];

    while (instruction._i > INFECT) {
        switch (instruction._i) {
            case GO:
                instruction = instructions[instruction._n];
            case IF_EMPTY:
                if (front == EMPTY) {
                    instruction = instructions[instruction._n];
                } else {
                    instruction = instructions[++instruction._n];
                }

  }
}
}




Creature::Creature(Species s, std::string dir): _s(s){

  //TODO BARBEQUE: enums


}






