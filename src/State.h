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

    /**
     * State constructor with a name and state execute function pointer
     * @param name
     * @param executeStateFnPtr
     */
    State(std::string name, bool (*executeStateFnPtr)());

    /**
     * Adds a transition from this state
     * @param NextState : The next state
     * @param transitionCondition : Function pointer which checks the conditions of transition
     */
    void addTransition(State* NextState, bool(*transitionCondition)() );

    /**
     * Sets the state execution function pointer
     * @param executeStateFnPtr
     */
    void setExecuteStateFnPtr(bool (*executeStateFnPtr)());

    /**
     * Prints states name
     */
    void printStateName();

    /**
     * Gets the execution function pointer of current state
     * @return
     */
    bool *getExecuteStateFnPtr();

    /**
     * Get name of the state
     * @return : String of the name
     */
    const std::string &getName() const;

    /**
     * Get all possible transitions of current state
     * @return : Vector of <transition> s
     */
    std::vector<Transition> getStateTransitions();

    virtual ~State();


private:

    std::string name_;

    bool (*executeStateFnPtr)() = nullptr;

    std::vector<Transition> transitions;

};




#endif //STATEMACHINE_STATE_H
