//
// Created by shreyas on 15.12.20.
//

#ifndef STATEMACHINE_STATE_H
#define STATEMACHINE_STATE_H


#include <string>
#include <vector>
#include <utility>
#include <iostream>


class State;

struct Transition{
    State* NextState;
    bool (*transitionCondition)();
};


class State {

public:

    State();

    State(std::string name, bool (*executeStateFnPtr)());

    void addTransition(State* NextState, bool(*transitionCondition)() );

    void setExecuteStateFnPtr(bool (*executeStateFnPtr)());

    void printStateName();

    bool *getExecuteStateFnPtr();

    std::vector<Transition> getStateTransitions();

    virtual ~State();

    const std::string &getName() const;

private:

    std::string name_;

    bool (*executeStateFnPtr)() = nullptr;

    std::vector<Transition> transitions;

};




#endif //STATEMACHINE_STATE_H
