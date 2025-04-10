#ifndef ERRORS_H
#define ERRORS_H

#include "typedefs.h"

extern const RetVal err_codes;

bool chk_positive(int value);
bool chk_non_negative(int value);
bool chk_flag_value(int option_index);
bool extra_flag_chk();
void not_rectangular();

#endif