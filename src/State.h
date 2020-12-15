//
// Created by shreyas on 15.12.20.
//

#ifndef STATEMACHINE_STATE_H
#define STATEMACHINE_STATE_H


#include <string>
#include <vector>


class State;

struct Transition{
    State* NextState;
    bool (*transitionCondition)();
};


class State {

public:

    State(std::string name, bool (*executeStateFnPtr)());

    void addTransition(State* NextState, bool(*transitionCondition)() );

    void setExecuteStateFnPtr(bool (*executeStateFnPtr)());

    virtual ~State();




private:

    std::string name_;

    bool (*executeStateFnPtr)();

    std::vector<Transition> transitions;

};



#endif //STATEMACHINE_STATE_H
