#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_ {
    int ArrSize;
    PElement *pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray, *PAdptArray;

//creating an adapting array class without given array
PAdptArray CreateAdptArray(COPY_FUNC copyfunc, DEL_FUNC delfunc, PRINT_FUNC printfunc) {
    PAdptArray pArr = (PAdptArray) malloc(sizeof(AdptArray));
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
void DeleteAdptArray(PAdptArray pArray) {
    int i;
    if (pArray == NULL) {
        printf("Error: invalid input");
        return;
    }
    for (i = 0; i < pArray->ArrSize; i++) {
        pArray->delFunc((pArray->pElemArr)[i]);
    }
    free(pArray->array);
    free(pArray);
}

// setting an element in the adapting array
Result SetAdptArrayAt(PAdptArray pArray, int index, PElement element) {
    PElement *newpElemArr;
    if (pArray == NULL)
        return FAIL;

    if (index >= pArray->ArrSize) {

// Extend Array
        if ((newpElemArr = (PElement *) calloc((index + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArray->pElemArr, (pArray->ArrSize) * sizeof(PElement));
        free(pArray->pElemArr);
        pArray->pElemArr = newpElemArr;
    }

    // Delete Previous Elem
    pArray->delFunc((pArray->pElemArr)[index]);
    (pArray->pElemArr)[index] = pArray->copyFunc(element);

    // Update Array Size
    pArray->ArrSize = (index >= pArray->ArrSize) ? (index + 1) : pArray->ArrSize;
    return SUCCESS;
}
// getting an element from the adapting array

PElement GetAdptArrayAt(PAdptArray pArray, int index) {
    if (pArray == NULL || index < 0 || index >= pArray->ArrSize) {
        printf("Error: invalid input");
        return NULL;
    }
    return pArray->array[index];
}

// getting the ArrSize of the adapting array
int GetAdptArraySize(PAdptArray pArray) {
    if (pArray == NULL) {
        printf("Error: invalid input");
        return -1;
    }
    return pArray->ArrSize;
}

// printing the adapting array

void PrintDB(PAdptArray pArray) {
    if (pArray == NULL) {
        printf("Error: invalid input");
        return;
    }
    for (int i = 0; i < pArray->ArrSize; i++) {
        pArray->printFunc(pArray->pElemArr[i]);
    }
}

//

int main() {

}
