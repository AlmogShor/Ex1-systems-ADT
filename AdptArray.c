#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct AdptArray_
{
    int ArrSize;

    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray, *PAdptArray;

//creating an adapting array class without given array
PAdptArray CreateAdptArray(COPY_FUNC copyfunc, DEL_FUNC delfunc,PRINT_FUNC printfunc){
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (pArr == NULL)
        return NULL;
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delfunc;
    pArr->copyFunc = copyfunc;
    pArr->printFunc = printfunc;
    return pArr;
}

// deleting an adapting array class
void DeleteAdptArray(PAdptArray pArray){
    int i;
    if(pArray == NULL){
        printf("Error: invalid input");
        return;
    }
    for(i = 0; i < pArray->size; i++){
        pArray->delFunc(pArray->array[i]);
    }
    free(pArray->array);
    free(pArray);
}

// setting an element in the adapting array
Result SetAdptArrayAt(PAdptArray pArray, int index, PElement element){
    if(pArray == NULL || index < 0 || element == NULL){
        printf("Error: invalid input");
        return FAIL;
    }
    if(index >= pArray->size){
        pArray->array = (PElement*)realloc(pArray->array, (index+1)*sizeof(PElement));
        if(pArray->array == NULL){
            printf("Error: memory allocation failed");
            return FAIL;
        }
        for(int i = pArray->size; i < index; i++){
            pArray->array[i] = NULL;
        }
        pArray->array[index] = pArray->copyFunc(element);
        pArray->size = index+1;
    }
    else{
        pArray->delFunc(pArray->array[index]);
        pArray->array[index] = pArray->copyFunc(element);
    }
    return SUCCESS;
}

// getting an element from the adapting array

PElement GetAdptArrayAt(PAdptArray pArray, int index){
    if(pArray == NULL || index < 0 || index >= pArray->size){
        printf("Error: invalid input");
        return NULL;
    }
    return pArray->array[index];
}

// getting the size of the adapting array
int GetAdptArraySize(PAdptArray pArray){
    if(pArray == NULL){
        printf("Error: invalid input");
        return -1;
    }
    return pArray->size;
}

// printing the adapting array

void PrintDB(PAdptArray pArray){
    if(pArray == NULL){
        printf("Error: invalid input");
        return;
    }
    for(int i = 0; i < pArray->size; i++){
        pArray->printFunc(pArray->array[i]);
    }
}

//

int main(){

}
