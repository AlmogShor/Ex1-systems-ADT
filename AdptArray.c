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

/** creating an adapting array class without given array
 *
 * @param copyfunc
 * @param delfunc
 * @param printfunc
 * @return
 */
PAdptArray CreateAdptArray(COPY_FUNC copyfunc, DEL_FUNC delfunc, PRINT_FUNC printfunc) {
    PAdptArray pArr = (PAdptArray) malloc(sizeof(AdptArray));
    if (pArr == NULL) {
        printf("Error: failed to allocate memory\n");
        return NULL;
    }
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delfunc;
    pArr->copyFunc = copyfunc;
    pArr->printFunc = printfunc;
    return pArr;
}


/** deleting an adapting array class
 *
 * @param pArray
 */
void DeleteAdptArray(PAdptArray pArray) {
    int i;
    if (pArray == NULL) {
        printf("Error: invalid input");
        return;
    }

    for (i = 0; i < pArray->ArrSize; i++) {
        if (pArray->pElemArr[i] != NULL)
            pArray->delFunc((pArray->pElemArr)[i]);
    }

    free(pArray->pElemArr);
    free(pArray);
}


/**setting an element in the adapting array
 *
 * @param pArray
 * @param index
 * @param element
 * @return
 */
Result SetAdptArrayAt(PAdptArray pArray, int index, PElement element) {
    PElement *newpElemArr;
    if (pArray == NULL || element == NULL) {
        printf("Error: Invalid input");
        return FAIL;
    }
    if (index >= pArray->ArrSize) {

        // Extend Array
        if ((newpElemArr = (PElement *) calloc((index + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArray->pElemArr, (pArray->ArrSize) * sizeof(PElement));
        free(pArray->pElemArr);
        pArray->pElemArr = newpElemArr;
    }

    // Delete Previous Elem
    if ((pArray->pElemArr)[index] != NULL) {
        pArray->delFunc((pArray->pElemArr)[index]);
    }

    //Set new Elem
    if (pArray->pElemArr)
        (pArray->pElemArr)[index] = pArray->copyFunc(element);


    // Update Array Size
    pArray->ArrSize = (index >= pArray->ArrSize) ? (index + 1) : pArray->ArrSize;
    return SUCCESS;
}


/** getting an element from the adapting array
 *
 * @param pArray
 * @param index
 * @return
*/


PElement GetAdptArrayAt(PAdptArray pArray, int index) {
    if (pArray == NULL || index < 0 || index >= pArray->ArrSize) {
        printf("Error: invalid input");
        return NULL;
    }
    if (pArray->pElemArr[index] == NULL) {
        return NULL;
    }
    PElement pElemArr = pArray->copyFunc(pArray->pElemArr[index]);
    return pElemArr;
}

// getting the ArrSize of the adapting array
int GetAdptArraySize(PAdptArray pArray) {
    if (pArray == NULL) {
        printf("Error: invalid input");
        return FAIL; // should it be FAIL, NULL or -1?
    }
    return pArray->ArrSize;
}

/** printing the adapting array
 *
 * @param pArray
 */

void PrintDB(PAdptArray pArray) {
    if (pArray == NULL) {
        printf("Error: invalid input");
        return;
    }
    for (int i = 0; i < pArray->ArrSize; i++) {
        if (pArray->pElemArr[i] != NULL)
            pArray->printFunc(pArray->pElemArr[i]);
    }
}

//

//int main() {
//
//}
