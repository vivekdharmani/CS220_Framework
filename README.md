CS220 Project Framework
===============

## Algorithms Implemented
- Lees Algorithm
- Lees Algorihm (3-bit)
- Lees Algorithm (2-bit)
- Ruben's Cost Function (and 2 enhancements)
- Korn's Cost Function (with 2 enhancements and user-given overpull)
- Hadlock's Algorithm (with enhancement to expand latest node discovered)



## Project Overview

You will use this framework for the following projects:

- Grid Routing

The project will involve reading in JSON test files (located in the test directory) and parsing these files into a Problem Object. This step has already been done for you and is written at the beginning of main.cc to allow for command line arguments, **You should not change this code** as it will be used for testing.

You will then take this Problem Object, and pass it into your custom problem map object. The custom problem map object is the object you use to reprsent the problem space. In the example we give that object is the Grid object, however **you should not use the grid object** as it is not adequate for this project. you should, however, take advantage of the other classes we give you, such as the Node and Edge classes.

Once you have created your custom problem map object, you should make a call to a routing algorithm (the specific algorithm will depend on which submission you are working on). You will likely be able to use the same custom problem object for mulitple routers, however it is not required that all routes work with the same custom problem object. Your routing algorithm **must return either a Path/vector of Paths or Netlist/vector of Netlists** depending on what the situation calls for.

- Path: A path is a set of straight line segments from one source to one sink

Once you have a solution in the form of a Path/vector of Paths, you should print your solution to std out for review.

Currently there is only one test case given, and it is not a good test case. It is given as an example so you can create your own test cases. **You should be creating robust test cases** that are capable of testing malformed input files, edge cases, and problems that are impossible to solve. With this **your program should error gracefully**, meaning if there is a bad input file or some type of error the program should not simply crash. It should give an explination as to the possible error and exit. We have given you the claim system for printing errors, please use it.

**Please Note:** If you have one of the projects listed at the top, then your project **MUST** exist within this framework.

## Running the Framework

In order to run the framework, you must first go to Utilities/JSON_parser and run "make". This will create a json_parse.so file that is need to parse the JSON test files that we give you. Next you will go back to the root directory and run "make". This will generate an executable called "grid_router", which you can run by calling "./grid_router <test_case>", where <test_case> is the path of a test case. In the framework we give you there is only one test case, located at "Tests/test_sample.json". This will run the example that we have written for the framework.

**Please Note:** some of you may get a library error when trying to run grid_router. If you recieve this library error, please copy the file "json_parser.so" from Utilities/JSON_parser to the root directory where the file "grid_router" exists and this should fix the problem. Note that you must have already called "make" in Utilities/JSON_parser for "json_parse.so" to exist.

