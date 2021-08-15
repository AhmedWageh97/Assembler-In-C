/* Inclusion */
#include <stdlib.h>
#include "MemoryCommandsHandler.h"
#include "ErrorHandler.h"

/* Externed variables */
extern char memory_alloc_instruction_txt[NUMBER_OF_ALLOC_INSTRUCTIONS][7];
extern MemoryAllocData_t * CurrentMemoryLocation;
extern MemoryAllocData_t * MemoryStack;
extern FullCoding_t * FirstLine;

/* Functions definition */
/* Handles(Parses) memory allocation instruction */
void MemoryAllocInstruction(char * instruction, MemoryAllocData_t * DataPtr)
{
	char text[8];
	int text_index = 0;
	int i;

	while (instruction[text_index] != ' ' && instruction[text_index] != '\n' && instruction[text_index] != '\0' && instruction[text_index] != 13)
	{
		text[text_index] = instruction[text_index];
		text_index++;
	}
	text[text_index] = 0;

	for (i = 0; i < NUMBER_OF_ALLOC_INSTRUCTIONS; i++)
	{
		if (strcmp(text, memory_alloc_instruction_txt[i]) == 0)
		{
			break;
		}
	}
	if (i == NUMBER_OF_ALLOC_INSTRUCTIONS)
	{
		/* Not exist */
	}
	else
	{
		CurrentMemoryLocation->InstructionType = i;
	}

	text_index += RemoveWhiteSpaces(&instruction[text_index]);
	MemoryGetData(&instruction[text_index], DataPtr);

}

/* Extract data from memory allocation instruction */
void MemoryGetData(char * instruction, MemoryAllocData_t * DataPtr)
{
	int line_index = 0;
	int txt_index = 0;
	char txt[5];
	int iteration;
	memset(txt, 0, 5);


	if (DataPtr->InstructionType >= DB && DataPtr->InstructionType <= DW)
	{
		DataPtr->Data = calloc(sizeof(MemoryAllocData_t), count_parameters(instruction));
		while (instruction[line_index] != '\0' && instruction[line_index] != '\n')
		{
			while ((instruction[line_index] >= '0' && instruction[line_index] <= '9') || (instruction[line_index] == '-'))
			{
				txt[txt_index] = instruction[line_index];
				line_index++;
				txt_index++;
			}
			DataPtr->Data[DataPtr->count] = atoi(txt);
			DataPtr->count++;
			memset(txt, 0, 5);
			txt_index = 0;
			if (instruction[line_index] == ',' && 
				(instruction[line_index + 1] == '\n' || instruction[line_index + 1] == '\0' || instruction[line_index + 1] == 13))
			{
				Error_ReportError(ERROR_SYNTAX_ERROR, GetLineNumber());
				line_index++;
			}
			else if (instruction[line_index] == ',')
			{
				line_index++;
				line_index += RemoveWhiteSpaces(&instruction[line_index]);
				if (instruction[line_index] == '\n' || instruction[line_index] == '\0' || instruction[line_index] == 13)
				{
					Error_ReportError(ERROR_SYNTAX_ERROR, GetLineNumber());
				}
			}
		}

	}
	else if (DataPtr->InstructionType == ASCIZ)
	{
		DataPtr->count = countAscizData(&instruction[1]) + 1;
		DataPtr->Data = calloc(sizeof(MemoryAllocData_t), DataPtr->count);
		
		for (iteration = 0; iteration < DataPtr->count - 1; iteration++)
		{
			DataPtr->Data[iteration] = instruction[iteration + 1];
		}
		DataPtr->Data[DataPtr->count - 1] = 0;
	}
}

/* Count number of parameters in the instruction */
int count_parameters(char * instruction)
{
	int count = 0;
	int index = 0;

	while (instruction[index] != '\n' && instruction[index] != '\0' && instruction[index] != 13)
	{
		count += (instruction[index] == ',');
		index++;
	}

	return count + 1;
}

/* Create a new memory line to prepare the needed data for processing */
void NewMemoryLine(void)
{
	CurrentMemoryLocation->nxtMemoryAlloc = (MemoryAllocData_t *)calloc(sizeof(MemoryAllocData_t), 1);
	CurrentMemoryLocation->nxtMemoryAlloc->Address = 0;
	CurrentMemoryLocation->nxtMemoryAlloc->Data = NULL;
	CurrentMemoryLocation->nxtMemoryAlloc->nxtMemoryAlloc = NULL;
	CurrentMemoryLocation->nxtMemoryAlloc->count = 0;

	CurrentMemoryLocation = CurrentMemoryLocation->nxtMemoryAlloc;
}

/* Handle memory allocation instruction */
void HandleMemoryAllocation(void)
{
	MemoryAllocData_t * temp = MemoryStack;
	int address;

	address = GetStartAddressForMemory();
	while (temp->nxtMemoryAlloc != NULL)
	{
		temp->Address = address;
		if (temp->InstructionType == DB)
		{
			address += 1 * temp->count;
		}
		else if (temp->InstructionType == DH)
		{
			address += 2 * temp->count;
		}
		else if (temp->InstructionType == DW)
		{
			address += 4 * temp->count;
		}
		else if (temp->InstructionType == ASCIZ)
		{
			address += 1 * temp->count;
		}
		temp = temp->nxtMemoryAlloc;
	}
}

/* Returns the start address you can use in memory */
int GetStartAddressForMemory(void)
{
	FullCoding_t * temp = FirstLine;
	int retData;

	while (temp->nxtCodeLine != NULL)
	{
		temp = temp->nxtCodeLine;
	}

	if (temp->Address - 4 < 100)
	{
		retData = 100;
	}
	else
	{
		retData = temp->Address;
	}

	return retData;
}

/* Returns the instruction type of a memory allocation instruction */
MemoryAllocationInstructions_t GetMemoryInstruction(char * instructionText)
{
	char txt[7] = { 0 };
	int index = 0;

	while (instructionText[index] != ' ' && instructionText[index] != '\t' &&
		instructionText[index] != '\n' && instructionText[index] != '\0' && instructionText[index] != 13)
	{
		txt[index] = instructionText[index];
		index++;
	}
	txt[index] = 0;

	for (index = 0; index < NUMBER_OF_ALLOC_INSTRUCTIONS; index++)
	{
		if (strcmp(txt, memory_alloc_instruction_txt[index]) == 0)
		{
			break;
		}
	}
	if (index == NUMBER_OF_ALLOC_INSTRUCTIONS) /* Not an instruction */
	{
		Error_ReportError(ERROR_NOT_AN_INSTRUCTION, GetLineNumber());
	}
	return index;
}

/* Count Asciz data */
int countAscizData(char * DataTxt)
{
	int index = 0;
	int temp_index;

	while (DataTxt[index] != '\'' && DataTxt[index] != '\"')
	{
		index++;
	}

	temp_index = index + 1 + RemoveWhiteSpaces(&DataTxt[index]);
	if (DataTxt[temp_index] == ',')
	{
		Error_ReportError(ERROR_SYNTAX_ERROR, GetLineNumber());
	}

	return index;
}