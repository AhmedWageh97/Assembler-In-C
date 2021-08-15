#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Parser.h"
#include "ErrorHandler.h"


extern int current_line_number;

/* The input assembly files "For debugging", the names should be 
   based as parameters for executable file */
char files_names[2][10] = {
	"input1.as",
	"input2.as"
};

int main(int argc, char *argv[])
{
	int i;
	for (i = 1; i < argc; i++)
	{
		/* Prepare the assembler and provide it with file name */
		Init(argv[i]);
		printf("%s\n", argv[i]);
		
		/* Assembling the file and generate machine code */
		GetAllLabels();
		ParseAllLines();
		GetMachineCode();
		
		/* Print error messages if exists */
		if (Error_GetErrorsCount() == 0)
		{
			displayTable();
		}
		else
		{
			Error_DisplayErrorMessages();
		}
		
		/* Clear all data */
		deleteAll();
	}
	return 0;
}