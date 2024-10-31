#ifndef TIMBER_H
#define TIMBER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// This macro should be called instead of calling _log_print() directly. This is to avoid verbosity in function calls
// Example call: LOG(DEBUG, "Finished Calculations")

typedef enum {
	COLOR_RESET,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_BLUE,
	COLOR_MAGENTA,
	COLOR_CYAN,
	COLOR_RED,
	ANSI_RESET,
} color_t;

enum Levels {
	DEBUG,
	INFO,
	WARN,
	ERROR,
	CRITICAL,	
};

typedef struct logger_t {
	int min_level; // Minimum level to be printed
	FILE* stream; 
	bool time_enabled; // Print time along with debug message. Enabled by default
	bool line_enabled; // Print line number that debug message occurs on. Enabled by default
	bool function_enabled; // Print the name of the current function. Enabled by default
	color_t output_colors[5]; // Default colors are: Green, Cyan, Yellow, Red, Red
} logger_t;

class Logger {
public:
  int min_level;
  FILE* stream;
  bool time_enabled;
  bool line_enabled;
  bool function_enabled;
  color_t output_colors[5];
  
  Logger(const enum Levels min_level, const char *file_name);

  ~Logger();

  void kill();
  
  void log(const enum Levels level, const char *msg, const char *func = __builtin_FUNCTION(), int line = __builtin_LINE());

private:
  void err(const char *msg);
};

#endif
