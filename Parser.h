#ifndef PARSER_H_
#define PARSER_H_
/* Inclusion */
#include <stdint.h>
#include "SharedHeader.h"
#include "Configurations.h"
#include "HelperFunctions.h"
#include "UpdateOutputData.h"
#include "ParseMainCommands.h"
#include "MemoryCommandsHandler.h"
#include "GenerateOutput.h"

/* Public functions prototype */
/* Prepare all data for assembling and open input file */
void Init(char * FileName);
/* Get all label data in the code */
void GetAllLabels(void);
/* Parse all code lines */
void ParseAllLines(void);
/* Parse a specific line */
void ParseLine(char * Line, Instruction_t * instruction);
/* Generate the machine code for all code */
void GetMachineCode(void);
/* Delete/Clear all data after generating the output */
void deleteAll(void);
#endif
