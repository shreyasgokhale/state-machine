//
// Created by shreyas on 15.12.20.
//

#include <algorithm>
#include "StateMachine.h"

bool StateMachine::addNewState(const std::string &name, bool (*StateFunction)()) {

    State *new_state = new State(name, StateFunction);
    new_state->setExecuteStateFnPtr(StateFunction);
    this->stateMachineList_.emplace_back(new_state);
    return true;
}


bool StateMachine::addTransition(State *s1, State *s2, bool (*TransitionFunction)()) {
//   Check if current state exists
    if (findState(s1) && findState(s2)) {
        s1->addTransition(s2, TransitionFunction);
        return true;
    }

    std::cout << "Given state does not exist" << std::endl;

    return false;
}

bool StateMachine::goToNextState() {

    if (findState(current_state_)) {
        std::vector<Transition> transitions = current_state_->getStateTransitions();
        if (transitions.empty()) {
//            Vector is empty, no transitions present
            throw std::logic_error("No transitions present for this state");
            return false;
        }

        std::vector<State *> available_transitions;

        if (!getNextState(current_state_, transitions, &available_transitions)) {
            std::cout << "No state change conditions are satisfied at the moment" << std::endl;
            return false;
        } else {
            std::cout << "Transition Possible" << std::endl;
//            For now, adding the first state as the next state
            current_state_ = available_transitions.at(0);
        }

        return true;
    }
    return false;
}


bool StateMachine::findState(const std::string *&name, State **s) {

    auto findIter = std::find_if(stateMachineList_.begin(), stateMachineList_.end(),
                                 [&name](const State *state) { return *name == state->getName(); });

    if (findIter != stateMachineList_.end()) {
        *s = (*findIter);
        return true;
    }
    *s = nullptr;
    return false;
}


bool StateMachine::getNextState(State *current_state, std::vector<Transition> transition,
                                std::vector<State *> *available_states) {

    for (auto &it:transition) {
        if (it.transitionCondition())
            available_states->emplace_back(it.NextState);
    }
    if (available_states->empty())
        return false;
    return true;
}


bool StateMachine::findState(State *s) {


//    std::cout << "Finding State" << s->getName() << std::endl;

    return (std::find(stateMachineList_.begin(), stateMachineList_.end(), s) != stateMachineList_.end());

}


bool StateMachine::addNewState(State *state) {

    findState(state);
    if (!findState(state)) {
//       Put this state in state machine
        this->stateMachineList_.emplace_back(state);
//      For now, assume that first state is the init state
        if (current_state_ == nullptr)
            current_state_ = state;

        return true;
    }

    return false;

}


bool StateMachine::tickMachine() {
    return current_state_->getExecuteStateFnPtr();
}


StateMachine::StateMachine(const std::list<State *> &stateMachineList) : stateMachineList_(stateMachineList) {}

StateMachine::StateMachine() {

}

StateMachine::~StateMachine() {

}
