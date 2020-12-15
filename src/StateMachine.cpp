//
// Created by shreyas on 15.12.20.
//

#include "StateMachine.h"

bool StateMachine::addNewState(const std::string &name, bool (*StateFunction)(), bool (*TransitionFunction)()) {

    State* new_state =  new State(name, StateFunction);

    new_state->addTransition(nullptr, TransitionFunction);

    new_state->setExecuteStateFnPtr(StateFunction);

    this->stateMachineList.emplace_back(new_state);

    return true;
}

bool StateMachine::addNewState(State state) {
    throw std::logic_error{"Function not yet implemented"};
    return false;
}
