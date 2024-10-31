#include "timber.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// DESC: Returns the ANSI color code of the color type
// NOTE: this was implemented to make editing the logger configuration less confusing on the user end. Future Charlotte: yes, i do in fact know that strncpy exists
static const char *_get_color_code(color_t color) 
{
	switch (color) {
		case COLOR_GREEN: return "\033[32m";
		case COLOR_YELLOW: return "\x1b[33m";
		case COLOR_BLUE: return "\x1b[34m";
		case COLOR_MAGENTA: return "\x1b[35m";
		case COLOR_CYAN: return "\x1b[36m";
		case COLOR_RED: return "\033[31m";
		case ANSI_RESET: return "\033[0m";
		default: return NULL; // if color isnt known, return NULL for later error handling
	}
}

// Constructor
Logger::Logger(const enum Levels min_level, const char *file_name)
{
  if (this == NULL) {
    this->err("NULL Logger Pointer");
    exit(1);
  }
  //Initialising Defaults
  this->time_enabled = true;
  this->line_enabled = true;
  this->function_enabled = true;
  
  //Default output colors
  this->output_colors[0] = COLOR_GREEN;
  this->output_colors[1] = COLOR_CYAN;
  this->output_colors[2] = COLOR_YELLOW;
  this->output_colors[3] = COLOR_RED;
  this->output_colors[4] = COLOR_RED;

  // Open requested file or write to stdout
  if (file_name!=NULL) {
    this->stream = fopen(file_name, "w");
  } else {
    this->stream = stdout;
  }

  if (min_level>4 || min_level<0) {
    this->err("Invalid Minimum Log Level");
    this->min_level = 1;
  } else {
    this->min_level = min_level;
  }
}
  
void Logger::log(const enum Levels level, const char *msg,
         const char *func,
         int line)
{
  const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};
  time_t now = time(NULL);
  //Handling of Errors
  if (this == NULL) {
    this->err("NULL Logger pointer");
    return;
  }
  if (level>4 || level<0) {
    this->err("Invalid Log Level");
    return;
  }
  if (_get_color_code(this->output_colors[level]) == NULL) {
    this->err("Invalid Color");
    return;
  }
  
  // Form the final output based off of which toggles in the struct are enabled
  char sn_buffer[128];
  char optional_output[256] = ""; // intialise the output, apparently strcat doesnt like empty strings
                                                                                                                                                                             
  if (this->time_enabled) {
   snprintf(sn_buffer, sizeof(sn_buffer), "%s", ctime(&now));
   strcat(optional_output, sn_buffer);
  }
  if (this->function_enabled) {
   snprintf(sn_buffer, sizeof(sn_buffer), "In Function: %s() ", func);
   strcat(optional_output, sn_buffer);
  }
  if (this->line_enabled) {
   snprintf(sn_buffer, sizeof(sn_buffer), "At Line: %d", line);
   strcat(optional_output, sn_buffer);
  }
  // Finally, check that the level is greater than or equal to the minimum printing level
  if (level < this->min_level) {
    return;
  }
  
  // Don't print escape codes if the output is anything but stdout
  if (this->stream != stdout) {
    fprintf(this->stream, "—————————————————————\n%s\n[%s]: %s\n—————————————————————\n", optional_output, levels[level], msg);
  } else {
    fprintf(this->stream, "%s—————————————————————\n%s\n[%s]: %s\n—————————————————————\n", _get_color_code(this->output_colors[level]), optional_output, levels[level], msg);
    //Reset colors 
    fprintf(this->stream, "%s", _get_color_code(ANSI_RESET));
  }
}
    
// Destructor
Logger::~Logger() 
{
  if (this->stream != NULL) {fclose(this->stream);}
}

void Logger::err(const char *msg)
{
  fprintf(stderr, "[LOG ERROR]: %s\n", msg);
}
