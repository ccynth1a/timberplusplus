#ifndef TIMBER_H
#define TIMBER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum Levels {
  DEBUG,
  INFO,
  WARN,
  ERROR,
  CRITICAL,	
};

class Logger {
public:
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

  const char *_get_color_code(color_t color);
};

#endif
