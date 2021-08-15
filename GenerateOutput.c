/* Inclusion */
#include <stdio.h>
#include <stdlib.h>
#include "GenerateOutput.h"

/* Externed data */
extern FILE * OutputFileHandler;
extern FullCoding_t * FirstLine;
extern char pureInputFile[MAX_FILE_NAME_SIZE];
extern ExternOut_t * FirstExtOut;
extern MemoryAllocData_t * MemoryStack;
extern ExternOut_t * FirstEntOut;

/* Functions definition */
/* Print the machine code in binary form */
void print_binary(FullCoding_t * data)
{
	char outData[18] = { 0 };

	if (data->instruction_information.type == R_TYPE)
	{
		sprintf(outData, "%04d %02X %02X %02X %02X\n", data->Address,
			(unsigned int)(data->Machine_Code & 0xFF), (unsigned int)((data->Machine_Code >> 8) & 0xFF),
			(unsigned int)((data->Machine_Code >> 16) & 0xFF), (unsigned int)((data->Machine_Code >> 24) & 0xFF));

		fprintf(OutputFileHandler, "%s", outData);
	}
	else if (data->instruction_information.type == I_TYPE)
	{
		sprintf(outData, "%04d %02X %02X %02X %02X\n", data->Address,
			(unsigned int)(data->Machine_Code & 0xFF), (unsigned int)((data->Machine_Code >> 8) & 0xFF),
			(unsigned int)((data->Machine_Code >> 16) & 0xFF), (unsigned int)((data->Machine_Code >> 24) & 0xFF));

		fprintf(OutputFileHandler, "%s", outData);
	}
	else if (data->instruction_information.type == J_TYPE)
	{
		sprintf(outData, "%04d %02X %02X %02X %02X\n", data->Address,
			(unsigned int)(data->Machine_Code & 0xFF), (unsigned int)((data->Machine_Code >> 8) & 0xFF),
			(unsigned int)((data->Machine_Code >> 16) & 0xFF), (unsigned int)((data->Machine_Code >> 24) & 0xFF));
		fprintf(OutputFileHandler, "%s", outData);
	}
}

/* print the bit representation of the data which presented in an 
   array of 0s and 1s from start_bit to end_bit */
void DisplayBits(char * data, int start_bit, int end_bit)
{
	int i;
	for (i = start_bit; i >= end_bit; i--)
	{
		printf("%d", abs(data[i]));
	}
	printf(" ");
}

/* Display MemoryAllocData_t data */
void DisplayMemoryData(MemoryAllocData_t * Data)
{
	int BytesCount = 0;
	char OutData[4];
	int i;
	MemoryAllocData_t * temp = Data;
	signed int address = temp->Address;
	char outFileData[20] = { 0 };

	while (temp->nxtMemoryAlloc != NULL)
	{
		if (temp->InstructionType == DB || temp->InstructionType == ASCIZ)
		{
			for (i = 0; i < temp->count; i++)
			{
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)(temp->Data[i] & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
			}
		}
		else if (temp->InstructionType == DH)
		{
			for (i = 0; i < temp->count; i++)
			{
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)(temp->Data[i] & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)((temp->Data[i] >> 8) & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
			}
		}
		else if (temp->InstructionType == DW)
		{
			for (i = 0; i < temp->count; i++)
			{
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)(temp->Data[i] & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)((temp->Data[i] >> 8) & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)((temp->Data[i] >> 16) & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)((temp->Data[i] >> 24) & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
			}
		}

		temp = temp->nxtMemoryAlloc;
	}
	if (BytesCount == 1)
	{
		sprintf(outFileData, "%04d %02X\n", address,
			(OutData[0] & 0xFF));

		fprintf(OutputFileHandler, "%s", outFileData);
	}
	else if (BytesCount == 2)
	{
		sprintf(outFileData, "%04d %02X %02X\n", address,
			(OutData[0] & 0xFF), (OutData[1] & 0xFF));

		fprintf(OutputFileHandler, "%s", outFileData);
	}
	else if (BytesCount == 3)
	{
		sprintf(outFileData, "%04d %02X %02X %02X\n", address,
			(OutData[0] & 0xFF), (OutData[1] & 0xFF),
			(OutData[2] & 0xFF));

		fprintf(OutputFileHandler, "%s", outFileData);
	}
	else if (BytesCount == 4)
	{
		OutMemoryData(address, OutData);
	}
}

/* Output the memory data to its file */
void OutMemoryData(signed int address, char * Data)
{
	char outData[20] = { 0 };

	sprintf(outData, "%04d %02X %02X %02X %02X\n", address,
		(Data[0] & 0xFF), (Data[1] & 0xFF),
		(Data[2] & 0xFF), (Data[3] & 0xFF));

	fprintf(OutputFileHandler, "%s", outData);
}

/* Generate the needed output in all output files */
void displayTable(void)
{
	FullCoding_t * temp = FirstLine;

	/* .ob file */
	sprintf(pureInputFile, "%s.ob", pureInputFile);
	OutputFileHandler = fopen(pureInputFile, "w");

	while (temp->nxtCodeLine != NULL)
	{
		print_binary(temp);
		temp = temp->nxtCodeLine;
	}

	DisplayMemoryData(MemoryStack);

	fclose(OutputFileHandler);
	pureInputFile[strlen(pureInputFile) - 3] = 0;

	/* .ext file */
	sprintf(pureInputFile, "%s.ext", pureInputFile);
	OutputFileHandler = fopen(pureInputFile, "w");
	diaplayExtern();
	fclose(OutputFileHandler);
	pureInputFile[strlen(pureInputFile) - 4] = 0;

	/* .ent file */
	sprintf(pureInputFile, "%s.ent", pureInputFile);
	OutputFileHandler = fopen(pureInputFile, "w");
	diaplayEntry();
	fclose(OutputFileHandler);
	pureInputFile[strlen(pureInputFile) - 4] = 0;
}

/* Generate output to .ent file*/
void diaplayExtern(void)
{
	ExternOut_t * temp = FirstExtOut;
	char OutData[MAX_LABEL_SIZE + 6];

	while (temp->nxt != NULL)
	{
		sprintf(OutData, "%s %04d\n", temp->varName, temp->Address);
		fprintf(OutputFileHandler, "%s", OutData);
		temp = temp->nxt;
	}
}

/* Generate output to .ext file*/
void diaplayEntry(void)
{
	ExternOut_t * temp = FirstEntOut;
	char OutData[MAX_LABEL_SIZE + 6];

	while (temp->nxt != NULL)
	{
		sprintf(OutData, "%s %04d\n", temp->varName, temp->Address);
		fprintf(OutputFileHandler, "%s", OutData);
		temp = temp->nxt;
	}
}
