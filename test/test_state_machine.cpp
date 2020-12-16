//
// Created by shreyas on 16.12.20.
//

#include "gtest/gtest.h"
#include "../src/StateMachine.h"
#include <exception>


bool printHello(){
    std::cout << "Hello" << std::endl;
    return true;
}

bool printWaiting(){
    std::cout << "Wait State" << std::endl;
    return true;
}

bool countHundred(){
    int j = 0;
    for (int i = 0; i < 100; ++i) {
        j++;
    }
    std::cout << "Final Value " <<  j << std::endl;
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

// Checks if creating new state is possible
TEST(TestState, AddState) {
    State s("Init" , &printHello);
    EXPECT_EQ(s.getName(), "Init");

}

// Checks if state can be executed
TEST(TestState, ExecuteState) {
    State s("Init" , &printHello);
   EXPECT_EQ((bool) s.getExecuteStateFnPtr(), true);

}

// Checks if error of not providing an execute function is handled
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

// Checks if a state machine can be created
TEST(TestStateMachine, CreateMachine) {
    State* s1 =  new State("Init" , &printHello);
    State* s2 =  new State("Wait" , &printWaiting);
    StateMachine* m = new StateMachine();
    m->addNewState(s1);
    m->addNewState(s2);
    EXPECT_EQ(m->findState(s1), true);
    EXPECT_EQ(m->findState(s2), true);

}

// Checks if machine can tick and execute state function
TEST(TestStateMachine, TickMachnine) {
    State* s1 =  new State("Init" , &printHello);
    StateMachine* m = new StateMachine();
    m->addNewState(s1);

    EXPECT_EQ(m->tickMachine(), true);
    EXPECT_EQ(m->tickMachine(), true);
    EXPECT_EQ(m->tickMachine(), true);
}

// Check if a transition to the next state can be added and performed
TEST(TestStateMachine, CheckTransiton) {
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

// Check complete function of state machine
TEST(TestStateMachine, CheckMultiAdd) {
    State* s1 =  new State("Init" , &printHello);
    State* s2 =  new State("Wait" , &printWaiting);
    State* s3 =  new State("Counter" , &countHundred);

    StateMachine* m = new StateMachine();

//  Transition s1->s2 is true
    s1->addTransition(s2,&checkTransitionFunctionTrue);
//  Transition s2->s3 is true
    s2->addTransition(s3,&checkTransitionFunctionTrue);
//  Transition s2->s1 is false
    s2->addTransition(s1,&checkTransitionFunctionFalse);
//  Transition s3->s1 is true
    s3->addTransition(s1,&checkTransitionFunctionTrue);

    m->addNewState(s1);
    m->addNewState(s2);
    m->addNewState(s3);

//    State s1
    EXPECT_EQ(m->tickMachine(), true);
//    Go to state s2
    EXPECT_EQ(m->goToNextState(), true);
    EXPECT_EQ(m->tickMachine(), true);

//    Go to state s3
    EXPECT_EQ(m->goToNextState(), true);
    EXPECT_EQ(m->tickMachine(), true);

    //    Go to state s1
    EXPECT_EQ(m->goToNextState(), true);
    EXPECT_EQ(m->tickMachine(), true);

    //    State s1
    EXPECT_EQ(m->tickMachine(), true);
//    Go to state s2
    EXPECT_EQ(m->goToNextState(), true);
    EXPECT_EQ(m->tickMachine(), true);

}

