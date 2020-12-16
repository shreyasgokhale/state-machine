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

    StateMachine();

    explicit StateMachine(const std::list<State *> &stateMachineList);

    bool addNewState(const std::string &name, bool (*StateFunction)());
    bool addNewState(State* state);
    bool addTransition(State *current_state, State *next_state, bool (*TransitionFunction)());
    bool findState(State *s);
    bool findState(const std::string *&name, State **s);

    virtual ~StateMachine();

private:
    
   std::list<State*> stateMachineList_;

   State*current_state_;


    bool getNextState(State *current_state, State *next_state, std::vector<Transition> transition);

    bool getNextState(State *current_state, std::vector<Transition> transition);

    static bool getNextState(State *current_state, std::vector<Transition> transition, std::vector<State *> *available_states);

    bool goToNextState();
};


#endif //STATEMACHINE_STATEMACHINE_H
