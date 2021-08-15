#ifndef SHARED_HEADER_H_
#define SHARED_HEADER_H_
/* Inclusion */
#include "Configurations.h"

/* User-defined data types */
/* Needed/Helper data structures */
enum Instruction_Name_t
{
	ADD = 0,
	SUB,
	AND,
	OR,
	NOR,
	MOVE,
	MVHI,
	MVLO,
	ADDI,
	SUBI,
	ANDI,
	ORI,
	NORI,
	BNE,
	BEQ,
	BLT,
	BGT,
	LB,
	SB,
	LW,
	SW,
	LH,
	SH,
	JMP,
	LA,
	CALL,
	STOP
};
typedef enum Instruction_Name_t Instruction_Name_t;

enum MemoryAllocationInstructions_t
{
	DB = 0,
	DH,
	DW,
	ASCIZ,
	ENTRY,
	EXTERN
};
typedef enum MemoryAllocationInstructions_t MemoryAllocationInstructions_t;

struct MemoryAllocData_t
{
	signed int Address;
	signed char count;
	char label[MAX_LABEL_SIZE];
	char code[MAX_LINE_SIZE];
	signed long * Data;
	MemoryAllocationInstructions_t InstructionType;
	struct MemoryAllocData_t * nxtMemoryAlloc;
};
typedef struct MemoryAllocData_t MemoryAllocData_t;


enum Instruction_Type_t {
	R_TYPE = 0,
	I_TYPE,
	J_TYPE
};
typedef enum Instruction_Type_t Instruction_Type_t;

struct Instruction_t
{
	signed int immidiateValue;
	unsigned char RS;
	unsigned char RD;
	unsigned char RT;
	unsigned char function;
	unsigned char opCode;
	Instruction_Name_t Instruction_Name;
	Instruction_Type_t type;
	signed long Address;
	int lineNumber;
	unsigned int Reg : 1;
};
typedef struct Instruction_t Instruction_t;

struct FullCoding_t
{
	signed int Address;
	signed long Machine_Code;
	char code[80];
	char label[MAX_LABEL_SIZE];
	struct FullCoding_t * nxtCodeLine;
	Instruction_t instruction_information;
};
typedef struct FullCoding_t FullCoding_t;

struct ExternVarData_t
{
	char varName[MAX_VAR_NAME];
	char label[MAX_LABEL_SIZE];
	char code[MAX_LINE_SIZE];
	struct ExternVarData_t * nxtVar;
};
typedef struct  ExternVarData_t ExternVarData_t;

struct ExternOut_t
{
	char varName[MAX_VAR_NAME];
	signed int Address;

	struct ExternOut_t * nxt;
};
typedef struct ExternOut_t ExternOut_t;

#endif