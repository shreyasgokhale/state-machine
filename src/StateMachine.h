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

    /**
     * Adds a new state given a state name and corresponding state function
     * @param name
     * @param StateFunction
     * @return true, if operation is success
     */
    bool addNewState(const std::string &name, bool (*StateFunction)());

    /**
     * Adds a new state given a state object
     * @param state
     * @return true, if operation is success
     */
    bool addNewState(State* state);

    /**
     * Adds a transition from state s1 to state s2 with a transition function
     * @param s1 : State 1
     * @param s2 : State 2
     * @param TransitionFunction : Function pointer to a transition function, which can return boolean for success/fail
     * @return
     */
    bool addTransition(State *s1, State *s2, bool (*TransitionFunction)());

    /**
     * Find a state in given machine
     * @param s : State
     * @return : true, if operation is success
     */
    bool findState(State *s);

    /**
     * Find a state given its name
     * @param name
     * @param s: Pointer to a pointer of a state, which the method will fill if it is found.
     * @return : true, if operation is success
     */
    bool findState(const std::string *&name, State **s);

    /**
     * Checks if transition is possible to a next state and does it if it is possible
     * @return
     */
    bool goToNextState();

    /**
     * Ticks state machine to execute the state function of current state
     * @return
     */
    bool tickMachine();

    virtual ~StateMachine();

private:
    
   std::list<State*> stateMachineList_;
   State*current_state_ = nullptr;


    bool getNextState(State *current_state, State *next_state, std::vector<Transition> transition);

    bool getNextState(State *current_state, std::vector<Transition> transition);

    static bool getNextState(State *current_state, std::vector<Transition> transition, std::vector<State *> *available_states);

};


#endif //STATEMACHINE_STATEMACHINE_H
