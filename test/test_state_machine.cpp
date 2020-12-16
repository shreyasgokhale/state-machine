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
