/**
 *  Handles the memory allocation instructions 
 */
#ifndef MEMORY_COMMANDS_HANDLER_H_
#define MEMORY_COMMANDS_HANDLER_H_
/* Inclusion */
#include "Configurations.h"
#include "HelperFunctions.h"
#include "UpdateOutputData.h"
#include "ParseMainCommands.h"
#include "MemoryCommandsHandler.h"
#include "GenerateOutput.h"
#include "SharedHeader.h"
#include "HelperFunctions.h"

/* Functions prototype */
/* Handles(Parses) memory allocation instruction */
void MemoryAllocInstruction(char * instruction, MemoryAllocData_t * DataPtr);
/* Extract data from memory allocation instruction */
void MemoryGetData(char * instruction, MemoryAllocData_t * DataPtr);
/* Count number of parameters in the instruction */
int count_parameters(char * instruction);
/* Create a new memory line to prepare the needed data for processing */
void NewMemoryLine(void);
/* Handle memory allocation instruction */
void HandleMemoryAllocation(void);
/* Returns the start address you can use in memory */
int GetStartAddressForMemory(void);
/* Returns the instruction type of a memory allocation instruction */
MemoryAllocationInstructions_t GetMemoryInstruction(char * instructionText);
/* Count Asciz data */
int countAscizData(char * DataTxt);
#endif
