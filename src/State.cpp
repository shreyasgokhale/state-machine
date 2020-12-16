//
// Created by shreyas on 15.12.20.
//

#include "State.h"

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


void State::printStateName() {
    std::cout << this->name_ << std::endl;

}


const std::string &State::getName() const {
    return name_;
}

bool *State::getExecuteStateFnPtr() {
    if (executeStateFnPtr == nullptr) {
        throw std::invalid_argument("No state function found!");
        return nullptr;
    } else {
        return reinterpret_cast<bool *>((*executeStateFnPtr)());
    }
}

std::vector<Transition> State::getStateTransitions() {
    return transitions;
}

State::State() {

}

State::~State() {

}
