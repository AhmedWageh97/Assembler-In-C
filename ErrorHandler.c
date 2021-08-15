/* Inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ErrorHandler.h"
#include "Configurations.h"

/* Private variables */
Error_t * errors_list = NULL;
Error_t * current_error = NULL;

/* Error messages */
static char * error_messages[][50] = {
	"Unrecognised assembly instruction\0",
	"Unrecognized register number(greater than 31)\0",
	"Immidiate value MUST be integer\0",
	"Syntax error\0",
	"Not recognized label\0"
};
int number_of_errors = 0;
extern char inputFileName[MAX_FILE_NAME_SIZE];

/* Functions definition */
/* Initializing error list */
void Error_InitErrorHandler(void)
{
	errors_list = (Error_t *)malloc(sizeof(Error_t));
	errors_list->line_number = 0;
	errors_list->nxt_error = NULL;
	errors_list->pre_error = NULL;
	current_error = errors_list;
}

/* Report error with its type(errorType) and the 
   line number(lineNumber) where the error happened */
void Error_ReportError(ErrorType_t errorType, int lineNumber)
{
	Error_t * temp;
	Error_t * trav = errors_list;

	/* Increment error count */
	number_of_errors++;
	if (Error_GetErrorsCount() == 1)
	{
		errors_list->line_number = lineNumber;
		errors_list->error_type = errorType;
		errors_list->error_message = error_messages[0][errorType];
		errors_list->nxt_error = NULL;

		current_error = errors_list->nxt_error;
	}
	else
	{
		temp = (Error_t *)malloc(sizeof(Error_t));
		temp->line_number = lineNumber;
		temp->error_type = errorType;
		temp->error_message = error_messages[0][errorType];
		temp->nxt_error = NULL;
		temp->pre_error = NULL;

		/* Put it in order according to line number */
		if (temp->line_number < trav->line_number)
		{
			trav->pre_error = temp;
			temp->nxt_error = trav;
			errors_list = temp;
		}
		else
		{
			while (trav->nxt_error != NULL && temp->line_number > trav->line_number)
			{
				trav = trav->nxt_error;
			}

			if (temp->line_number >= trav->line_number)
			{
				trav->nxt_error = temp;
				temp->pre_error = trav;
				current_error = temp;
			}
			else
			{
				temp->pre_error = trav->pre_error;
				trav->pre_error->nxt_error = temp;
				temp->nxt_error = trav;
				trav->pre_error = temp;
				current_error = trav;
			}
		}
	}

}

/* Display all error messages */
void Error_DisplayErrorMessages(void)
{
	Error_t * temp = errors_list;
	int count = 1;
	
	printf("%d Errors found in %s\n", Error_GetErrorsCount(), inputFileName);
	while (temp != NULL)
	{
		printf("%-4d%s in line: %d\n", count, temp->error_message, temp->line_number);

		temp = temp->nxt_error;
		count++;
	}
}

/* Count number of errors in the code */
int Error_GetErrorsCount(void)
{
	return number_of_errors;
}