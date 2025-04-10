#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#define TRUE 1
#define FALSE 0

typedef unsigned char bool;
typedef unsigned char byte;

typedef enum RetVal
{
    SUCCESS,
    BAD_INPUT
} RetVal; // to distinguish from other function return values

typedef enum Flag
{
    WRAP,
    TOTAL,
    STEP,
    LOWER,
    UPPER
} Flag;

#endif
