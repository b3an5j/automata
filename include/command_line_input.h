#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include "typedefs.h"

#define FIRST_CHAR argv[i][0]
#define SECOND_CHAR argv[i][1]
#define THIRD_CHAR argv[i][2]
#define TOTAL_OPTIONS 5
#define NO_VALUE_OPTIONS 1
#define OPTION_INDEX result_buffer[0]
#define OPTION_PARAM_INDEX result_buffer[1]

extern const Flag flags;
extern const char *short_flags[TOTAL_OPTIONS];
extern const char *long_flags[TOTAL_OPTIONS];
extern int flag_values[TOTAL_OPTIONS];

int take_input(int argc, char **argv);
int arg_strcmp(const char *arg, const char *option, int *result_buffer);
void is_option(const char *str, const char **str_list, int *result_buffer);
int atoi(char *flag, int char_index);

#endif