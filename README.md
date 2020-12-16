## State Machine

### Building and Running
For building, make sure you have CMake 3.18+ installed.

From root folder, run following commands. This will also download the GTest 
framework in your build folder.

```shell script
mkdir build
cd build
cmake ../
make
```

From build folder, execute following
 
```shell script
./StateMachine
```
This will run 7 predefined tests

### Structure
The code is structured in 3 folders with respective functions.

```
src/
test/
docs/
```
When main is executed, it runs all the test cases present in `test/test_state_machine.cpp`

You can add your own tests or even use main file directly.

For more clarifications, have a look at [writeup](docs/Writeup.md).