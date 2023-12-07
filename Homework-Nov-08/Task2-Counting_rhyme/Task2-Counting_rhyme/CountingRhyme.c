#include <stdlib.h>

#include "CountingRhyme.h"
#include "../CyclicList/CyclicList.h"

CountingRhymeErrorCode getLastElementValue(const size_t n, const size_t m, int* const lastElementValue)
{
    CyclicList* cyclicList = createCyclicList();
    if (cyclicList == NULL)
    {
        return countingRhymeMemoryLack;
    }
    for (size_t i = 0; i < n; ++i)
    {
        CyclicListErrorCode errorCode = push(cyclicList, (int)(i + 1));
        if (errorCode != cyclicListDefaultErrorCode)
        {
            return countingRhymeMemoryLack;
        }
    }

    CyclicListElement* currentCyclicListElement = NULL;
    bool wereNoErrors = true;
    wereNoErrors &= getNext(cyclicList, &currentCyclicListElement) == cyclicListDefaultErrorCode;
    while (!isEmpty(cyclicList))
    {
        for (size_t i = 0; i < m - 1; ++i)
        {
            getNext(cyclicList, &currentCyclicListElement);
        }
        CyclicListElement* tempCyclicListElement = currentCyclicListElement;
        wereNoErrors &= getNext(cyclicList, &tempCyclicListElement) == cyclicListDefaultErrorCode;
        wereNoErrors &= getCyclicListElementValue(tempCyclicListElement, lastElementValue) == cyclicListDefaultErrorCode;
        tempCyclicListElement = NULL;
        wereNoErrors &= removeNext(&cyclicList, currentCyclicListElement) == cyclicListDefaultErrorCode;
        if (!wereNoErrors)
        {
            return countingRhymeExecutedUrgently;
        }
    }
    deleteCyclicList(&cyclicList);
    return countingRhymeDefaultErrorCode;
}
