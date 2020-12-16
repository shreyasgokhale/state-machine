# Made in Space

## Assignment 2: State Machine for Robotic arm

### Question

```
Provide a state machine for a robotic arm:

States / Transitions are easy to add (compile time)

State actions can be implemented (compile time) for every state,
if state is not implemented print state name in console

Error Handling

Testing

Documentation

Language: C++ (Google C++ Coding Standard)
```

## Initial Observations

Looking at the assignment, it is assumed that we are dealing with a Finite State Machine.  

In robotics, FSMs are used to determine different state a robot can be in (for example IDLE, START, CONFIG etc.). In our example, we are considering a robotic arm. So we can imagine action such as "Move to a position", translates to following steps

1. Initialize the robot parameters
2. Robot waits for goal input (Idle state)
3. Robot receives new goal and computes goal position (Calculate goal)
4. Execute Movement to reach the goal  
5. Check Goal 
6. Go back to idle

These states roughly translate to following state machine

![Made%20in%20Space%208a29f6e434994a938a2cf139a43865f2/Untitled.png](Made%20in%20Space%208a29f6e434994a938a2cf139a43865f2/Untitled.png)

## Design Choices

1. On a first glance at the problem, a State can be defined as a class and the objects can be real states. We can also do something else like using a base state class and each new action can inherit this class. But I want to start simple first. 
2. The `State` class can also include a transition. This can also be an additional class / structure which holds action and pointer to the data structure of another state. 
3. A state also includes a function pointer which points to the activity that the state is performing.
4. We also need a class which keeps track of all the states and transitions in a state machine
5. This `StateMachine` class will need to keep a track of nodes and do sanity checks (for deadlocks, invalid transitions etc). To start with, we can think of this as a linked list.
6. In future, this `StateMachine` class can call individual state execution functions per tick.
7. As we have this requirement: *"if state is not implemented print state name in console",*  we need to also implement a search function.
8. For initial design, as there was no explicit requirement for lowering memory, I am assuming that it is okay to have some slack. Optimizations can be done later.

## Devel Commit 1: Adding basic framework

Two classes were created: One which represents a generic state and one which holds all the states together to form a state machine. For state class, we also define a transition structure which holds the pointer to the next state and the function which makes it true. Similarly, for each state, there exists a state function which is executed when the robot is in that state. 

However, after doing this, I realized that the current implementation will not work if we want to use arguments for state and transition functions. We will have to rely on pointers for memory exchange. For now this means we have to create new custom functions for each state for different functionality. This is a serious flaw in the design. But we might deal with this later, once we get our basics running.

For now, let's go straight for tests and then fix the code as we go progress.

## Tests and Functions

The project uses different tests to make sure that the code is working properly. In actual code, we keep a track of current state in the state machine using `current_state_` variable. We have different functions to find a state and check for transition function. Current state should execute its state function at a clock tick but here, we call a `tickMachine()` function.

## Final *state:*

The current version of code can create different states, search amoung them, and define transition links between different states. The state machine can also tick and execute state functions and if transition condition is met, can perform the transiton to the next state.

Different conditions are tested using GTest. They are all passing.

## TODOs and future:

The exercise was quite fun to work with. And it gave me a chance to use some of the concepts in field. 

To develop further, here are some of the TODOs that I can think of

1. Creating better tests for testing some edge cases. Using tests in more effective manner
2. Optimization of current implementations
3. Adding new functionalities and methods for printing state machine structure, adding cyclic checks and easy ui.
4. Pointer security: I am using a lot of usecure code such as double pointers and function pointers. Instead of giving functions, we can derive class from state baseclass or maybe use cpp templates in the future.
5. Code cleanup and better organization, Using C++ goodies , reducing reuse
6. Using Travis / CircleCI for creating auto build-test-coverage setup