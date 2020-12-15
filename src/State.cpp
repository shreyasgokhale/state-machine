//
// Created by shreyas on 15.12.20.
//

#include "State.h"

#include <utility>

State::State(std::string name, bool (*executeStateFnPtr)()) : name_(std::move(name)) {

    this->executeStateFnPtr = executeStateFnPtr;

}

void State::addTransition(State *NextState, bool (*transitionCondition)()) {

    Transition new_transition{};

    new_transition.transitionCondition = transitionCondition;
    new_transition.NextState = NextState;
    this->transitions.emplace_back(new_transition);

}


void State::setExecuteStateFnPtr(bool (*executeStateFnPtr)()) {
    State::executeStateFnPtr = executeStateFnPtr;
}


State::~State() {

}