#ifndef GENERATE_OUTPUT_H_
#define GENERATE_OUTPUT_H_
/* Inclusion */
#include "SharedHeader.h"
#include "Configurations.h"
#include "HelperFunctions.h"
#include "UpdateOutputData.h"
#include "ParseMainCommands.h"
#include "MemoryCommandsHandler.h"
#include "GenerateOutput.h"

/* Functions prototype */
/* Print the machine code in binary form */
void print_binary(FullCoding_t * data);
/* print the bit representation of the data which presented in an 
   array of 0s and 1s from start_bit to end_bit */
void DisplayBits(char * data, int start_bit, int end_bit);
/* Display MemoryAllocData_t data */
void DisplayMemoryData(MemoryAllocData_t * Data);
/* Output the memory data to its file */
void OutMemoryData(signed int address, char * Data);
/* Generate the needed output in all output files */
void displayTable(void);
/* Generate output to .ent file*/
void diaplayEntry(void);
/* Generate output to .ext file*/
void diaplayExtern(void);
#endif
