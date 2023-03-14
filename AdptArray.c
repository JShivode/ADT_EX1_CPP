#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"


typedef struct AdptArray_
{
  int len; //len = length of the current adptive array. 
 // int size; //size of the array in the memory.
  PElement* val; //pointer to any array of PElement pointers.
 //function pointers:
  COPY_FUNC copyF; 
  DEL_FUNC delF;
  PRINT_FUNC prinF;
}AdptArray;



PAdptArray CreateAdptArray(COPY_FUNC copyF, DEL_FUNC delF, PRINT_FUNC prinF){
    //ptr=(cast-type*)malloc(byte-size); => used to allocate Memory to structers.
    
    PAdptArray adpArr = (PAdptArray)malloc(sizeof(AdptArray)); //allocates  memory for an 'AdptArray' struct
    if (adpArr == NULL)  //if memory allocation fails, return NULL
    {
       // printf("Memory allocation was Failed");
        return NULL;
    }
    adpArr->len = 0;
   // adpArr->size = 1;

    adpArr->val = NULL;
    adpArr->copyF =copyF;
    adpArr->delF =delF;
    adpArr->prinF =prinF;
    return adpArr; //return a pointer to the initialized AdptArray object.
}

Result SetAdptArrayAt(PAdptArray pAdpArr, int index, PElement element){
    //The given index is invalid (negative) or the array is NULL
     if (index < 0 || pAdpArr == NULL)
   {
    return FAIL;
   }
   PElement *secPArr = (PElement)malloc((index+1)*sizeof(PElement));
   if(secPArr == NULL){ //if memory allocation fails, return NULL
            return FAIL;
        }
   int i=0;
   while (i < pAdpArr->len)
   {
   if(pAdpArr->val[i]==NULL)
        {
                secPArr[i] = NULL;
        }
        else
            {
                secPArr[i] = pAdpArr->copyF(pAdpArr->val[i]);
            }
            i++;
   }

        for(int i = pAdpArr->len; i<index; i++){
            secPArr[i] = NULL;
        }
        secPArr[index] = pAdpArr->copyF(element);
        free(pAdpArr->val);
        pAdpArr->val= secPArr;
        pAdpArr->len = index+1;
        return SUCCESS;
    
}

void DeleteAdptArray(PAdptArray pAdpArr){
    if(pAdpArr == NULL){//if the array in null exit
        return;
    }

    //if the pointer pAdpArr is NOT NULL:
    int j=0;
    while (j < pAdpArr->len)
    {
        if((PElement)pAdpArr->val[j] != NULL){
        pAdpArr->delF(pAdpArr->val[j]); //use the given DEL_FUN to delete the current value
        //free(pAdpArr->val[i]);//free memory space to the index i
        }
        j++;
    }
    free(pAdpArr->val);
    free(pAdpArr); //free memory space to the pAdpArr itself
}

PElement GetAdptArrayAt(PAdptArray pAdpArr, int index){
    //illegal cases
   if (index >= pAdpArr->len || index<0|| pAdpArr->val[index]==NULL)
   {
    return NULL;
   }
   //other cases
   else
   {
    PElement element = pAdpArr->val[index];
  // PElement copyEl = pAdpArr->copyF(element);
   return (PElement)pAdpArr->copyF(element);
    
   }
   
}

int GetAdptArraySize(PAdptArray pAdpArr){
    if (pAdpArr == NULL)
    {
        return -1;
    }
    
    return pAdpArr->len;
}

void PrintDB(PAdptArray pAdpArr){
    int k=0;
    while (k < pAdpArr->len)
    {
        if(pAdpArr->val[k] != NULL)
        {
        pAdpArr->prinF(pAdpArr->val[k]);
        }
        k++;
    }
}
