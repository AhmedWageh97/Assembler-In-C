#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_
/* Inclusion */

/* User-defined data type */
/* The type of the errors */
enum ErrorType_t
{
	ERROR_NOT_AN_INSTRUCTION = 0,
	ERROR_NOT_A_REGISTER,
	ERROR_IMMIDIATE_VALUE,
	ERROR_SYNTAX_ERROR,
	ERROR_NOT_A_LABEL
};
typedef enum ErrorType_t ErrorType_t;

/* Error data */
struct Error_t
{
	int line_number;
	char * error_message;
	ErrorType_t error_type;
	struct Error_t * nxt_error;
	struct Error_t * pre_error;
};
typedef struct Error_t Error_t;

/* Public functions prototype */
/* Initializing error list */
void Error_InitErrorHandler(void);
/* Report error with its type(errorType) and the 
   line number(lineNumber) where the error happened */
void Error_ReportError(ErrorType_t errorType, int lineNumber);
/* Display all error messages */
void Error_DisplayErrorMessages(void);
/* Count number of errors in the code */
int Error_GetErrorsCount(void);
#endif