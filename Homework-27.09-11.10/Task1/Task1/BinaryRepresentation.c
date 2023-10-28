#include "BinaryRepresentation.h"

int getDecimalRepresentation(const char binaryNumber[NUMBER_SIZE])
{
    int decimalNumber = 0;
    for (int i = NUMBER_SIZE - 2; i >= 0; --i)
    {
        decimalNumber += (binaryNumber[i] - '0') << (NUMBER_SIZE - 2 - i);
    }
    return decimalNumber;
}

void getBinaryNumberRepresentation(const int number, char binaryNumberRepresentation[NUMBER_SIZE])
{
    for (int i = NUMBER_SIZE - 2; i >= 0; --i)
    {
        binaryNumberRepresentation[NUMBER_SIZE - 2 - i] = '0' + ((number >> i) & 1);
    }
    binaryNumberRepresentation[NUMBER_SIZE - 1] = '\0';
}

ErrorCode addNumbersBinaryRepresentation(const char binaryNumber1[NUMBER_SIZE],
    const char binaryNumber2[NUMBER_SIZE], char binarySumRepresentation[NUMBER_SIZE])
{
    for (int i = NUMBER_SIZE - 2; i >= 0; --i)
    {
        binarySumRepresentation[i] = binaryNumber1[i] + binaryNumber2[i] - '0';
    }
    binarySumRepresentation[NUMBER_SIZE - 1] = '\0';

    for (int i = NUMBER_SIZE - 2; i >= 0; --i)
    {
        if (binarySumRepresentation[i] >= '2')
        {
            binarySumRepresentation[i] -= 2;
            if (i == 0)
            {
                return overflow;
            }
            ++binarySumRepresentation[i - 1];
        }
    }
    return defaultErrorCode;
}
