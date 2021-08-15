/**
 *  Contains function that helps to all other modules in the project
 *  to do its job easier.
 */

#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_
/* Inclusion */
#include "SharedHeader.h"
#include <string.h>

/* Functions prototype */
/* Read assembly line */
int GetLine(char * RetLine);
/* Check if the line contains a label or not */
int ContainsALabel(char * Line, char * RetLabel);
/* Create new code line to prepare it to be processed */
void NewCodeLine(void);
/* Get the address of any labelName */
int GetLabelAddress(char * labelName);
/* Get the address of any  linetxt */
int GetLineAddress(char * linetxt);
/* Continue parsing th Line until you find the stopChar */
int ParseUntil(char * Line, char stopChar);
/* Continue parsing th Line until you find a number */
int ParseUntilNumber(char * Line);
/*  Remove all the whitespaces(continue increment the pointer)
	as long as you didn't find any characters except ' ' and \t */
int RemoveWhiteSpaces(char * Line);
/* Generate the machine code */
void GetMachine(FullCoding_t * DataPtr);
/* Get the curent line number */
int GetLineNumber(void);
#endif