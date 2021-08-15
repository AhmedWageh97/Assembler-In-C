#ifndef PARSE_MAIN_COMMANDS_H_
#define PARSE_MAIN_COMMANDS_H_
/* Inclusion */
#include "SharedHeader.h"

/* Functions prototype */
/* Parse R instruction */
void R_Instruction(char * Line, Instruction_t * instruction);
/* Parse I instruction */
void I_Instruction(char * Line, Instruction_t * instruction, int index);
/* Parse J instruction */
void J_Instruction(char * Line, Instruction_t * instruction, int index);
#endif