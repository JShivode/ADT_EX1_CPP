#ifndef ADAPTARRAY_H
#define ADAPTARRAY_H
typedef struct AdptArray_* PAdptArray; //A pointer to a struct called AdptArray_
typedef enum  {FAIL = 0, SUCCESS=1} Result; //An enumeration type with two possible values: FAIL and SUCCESS.
typedef void* PElement; //A pointer to an unspecified type.

typedef void(*DEL_FUNC)(PElement); //A pointer to a function that takes a PElement argument and returns void. 
typedef PElement(*COPY_FUNC)(PElement); //returns a new PElement object that is a copy of the input element. 
typedef void(*PRINT_FUNC)(PElement); //A pointer to a function that takes a PElement argument and returns void.

PAdptArray CreateAdptArray(COPY_FUNC, DEL_FUNC,PRINT_FUNC);
void DeleteAdptArray(PAdptArray);
Result SetAdptArrayAt(PAdptArray, int, PElement);
PElement GetAdptArrayAt(PAdptArray, int);
int GetAdptArraySize(PAdptArray);
void PrintDB(PAdptArray);
#endif