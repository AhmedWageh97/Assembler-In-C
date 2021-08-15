#ifndef UPDATE_OUTPUT_DATA_H_
#define UPDATE_OUTPUT_DATA_H_
/* Inclusion */
#include "SharedHeader.h"

/* Functions prototype */
/* Prepare data to be output to .ext file */
void AddExtern(char * var);
/* Prepare data to be output to .ent file */
void AddEntry(char * var);
/* Assign data to be output to .ext file */
void AddExternOut(char * var, signed int address);
/* Assign data to be output to .ext file */
void AddEntryOut(char * var, signed int address);
#endif