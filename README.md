# timber++ v1.0
 
 ## Intro
 
This is a port of my timber logging library to C++. Obviously since its C -> C++, the conversion was quite simple, but as I'm unfamiliar with the language in general, there's a high chance that I've encountered the dreaded "undefined behaviour". Please if you encounter these issues, contact me.

Other than that, this is a very simple logger library that works relatively similar to how Python's does, since that language has the best standard library logger in all languages. This project will be updated sporadically, and may not always be in line with the most up to date version of timber (C). Timber is also my first time ever writing a library, so please forgive the shoddy code.
 
 ## Index
 
 [Installation](#installation-compilation)
 
 [Project Specific Notes](#notes)
 
 [Example Code](#examples)
 
 [Configuration](#configuration)
 
 [Contact Me](#contact-me)
 
 ## Installation/Compilation
 
 After cloning the repo, compile:
 ```sh
 g++ -c timber.c -o timber.o
 ```
 
 Then create the static library:
 ```sh 
 ar rcs libtimber.a timber.o 
 ```
 
 Then for your own projects, add the "timber.h" and "libtimber.a" files to the project directory, and compile with:
 ```sh 
 g++ -o your_project your_project_main.c libtimber.a
 ```
 
 ## Notes
 
 - This project was compiled with GCC on Linux. Unlike my other project (Mako), this should be cross-platform and cross-compiler.
  
 - Any time a LOG_ERROR occurs, this is your fault, if it's something I've done wrong, the program will crash. Check that your values when calling a function are within the expected ranges
 
 - When writing to a filestream that is not stdout, colors cannot be printed
 
 ## Examples
 
 The way the library works is simple enough, it includes a new class named Logger, as well as various enum types for configuration and function calling
 
 ### Basic Usage:
 
 ```cpp
 #include "timber.h"
 #include <iostream>

 Logger *timber;
 
 int main()
 {
 	timber = new Logger(DEBUG, NULL);
    timber->log(DEBUG, "Example Message");
    delete timber;
    timber = NULL;
 }
 ```
 
 ### Explanation
 
 1. Globally declare a pointer to a Logger class instance. This holds all the configuration data. Global declaration is necessary to ensure the logger can be used in any function
 
 2. Allocate the correct amount of bytes for the pointer on heap. You could also obviously declare it on stack, but since all of the functions take pointers I've written it this way in the example for readability. The class constructor takes 2 arguments:
    1. enum Levels: The MINIMUM logging level to be printed. This follows the traditional 5 tiered scheme of DEBUG, INFO, WARN, ERROR, CRITICAL
    2. const char *: The filestream to be printed to. **To print to stdout, call the constructor with NULL as the filestream arg**
    
    The constructor also sets sane defaults for the configuration of the library.
 
 3. Call the .log() method as many times as needed to print to the requested filestream. This takes 2 arguments:
 	1. enum Levels: The level to print at
 	2. const char *: The message to be printed along with debug information
 
 4. Delete the logger once you're done, and set the pointer to NULL
 
 ## Configuration
 
 The Logger class contains members that control the eventual output of any call to the LOG() macro.
 
 By default, all features are enabled, so if you just want every single bit of relevant information, skip configuring the library.
 
 #### Optional Printable Information
 ```cpp
 bool time_enabled; //prints the current time
 bool line_enabled; //prints the line that the LOG() macro was called from
 bool function_enabled; //prints the function that the LOG() macro was called from
 color_t output_colors[5]; //array of color enum type which corresponds to the debug levels
 ```
 
 Since these are all members of a class, change the values by using the pointer
 
 As for the colors, the current options are:
 - COLOR_GREEN
 - COLOR_YELLOW
 - COLOR_BLUE
 - COLOR_MAGENTA
 - COLOR_CYAN
 - COLOR_RED
 
 ## Contact Me
 
 If you have any bugs/issues, please contact me via the usual avenues (Tumblr probably) or directly on Github.
