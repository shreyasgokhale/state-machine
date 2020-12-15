//
// Created by shreyas on 15.12.20.
//

#ifndef STATEMACHINE_STATEMACHINE_H
#define STATEMACHINE_STATEMACHINE_H

#include <list>
#include <stdexcept>
#include <iostream>

#include "State.h"



class StateMachine{

public:

    bool addNewState(const std::string& name, bool (*StateFunction)(), bool (*TransitionFunction)());
    bool addNewState(State state);


private:
    
   std::list<State*> stateMachineList;


};


#endif //STATEMACHINE_STATEMACHINE_H
