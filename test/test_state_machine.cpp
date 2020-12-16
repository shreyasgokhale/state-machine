//
// Created by shreyas on 16.12.20.
//

#include "gtest/gtest.h"
#include "../src/StateMachine.h"
#include "../src/State.h"
#include <exception>


bool printHello(){
    std::cout << "Hello" << std::endl;
    return true;
}

bool printWaiting(){
    std::cout << "Wait State" << std::endl;
    return true;
}


bool checkTransitionFunctionTrue(){

    std::cout << "This transition function always returns true" << std::endl;
    return true;
}


bool checkTransitionFunctionFalse(){

    std::cout << "This transition function always returns false" << std::endl;
    return false;
}


TEST(TestState, AddState) {
    State s("Init" , &printHello);
    EXPECT_EQ(s.getName(), "Init");

}

TEST(TestState, ExecuteState) {
    State s("Init" , &printHello);
   EXPECT_EQ((bool) s.getExecuteStateFnPtr(), true);

}


TEST(TestState, AddNullPtrFunction) {
    State s("Init" , nullptr);

    try {
        s.getExecuteStateFnPtr();
        FAIL() << "getExecuteStateFnPtr should throw an error\n";
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

        EXPECT_TRUE(1);
        // Didn't work
//        EXPECT_THROW( e, &std::invalid_argument);
    }
}


TEST(TestStateMachine, CreateMachine) {
    State* s1 =  new State("Init" , &printHello);
    State* s2 =  new State("Wait" , &printWaiting);
    StateMachine* m = new StateMachine();
    m->addNewState(s1);
    m->addNewState(s2);
    EXPECT_EQ(m->findState(s1), true);
    EXPECT_EQ(m->findState(s2), true);

}


TEST(TestStateMachine, TickMachnine) {
    State* s1 =  new State("Init" , &printHello);
    StateMachine* m = new StateMachine();
    m->addNewState(s1);

    EXPECT_EQ(m->tickMachine(), true);
    EXPECT_EQ(m->tickMachine(), true);
    EXPECT_EQ(m->tickMachine(), true);
}


TEST(TestStateMachine, AddTransition) {
    State* s1 =  new State("Init" , &printHello);
    State* s2 =  new State("Wait" , &printWaiting);
    StateMachine* m = new StateMachine();


    s1->addTransition(s2,&checkTransitionFunctionTrue);
    s2->addTransition(s2,&checkTransitionFunctionFalse);

    m->addNewState(s1);
    m->addNewState(s2);

    EXPECT_EQ(m->tickMachine(), true);
    EXPECT_EQ(m->goToNextState(), true);
    EXPECT_EQ(m->goToNextState(), false);


}


