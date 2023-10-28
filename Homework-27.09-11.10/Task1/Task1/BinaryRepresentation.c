#include "BinaryRepresentation.h"

int getDecimalRepresentation(const char binaryNumber[NUMBER_SIZE])
{
    int decimalNumber = 0;
    for (unsigned char i = NUMBER_SIZE; i--;)
    {
        decimalNumber += binaryNumber[i] << (NUMBER_SIZE - 1 - i);
    }
    return decimalNumber;
}

void getBinaryNumberRepresentation(const int number, char binaryNumberRepresentation[NUMBER_SIZE])
{
    for (unsigned char i = NUMBER_SIZE; i--;)
    {
        binaryNumberRepresentation[NUMBER_SIZE - 1 - i] = (number >> i) & 1;
    }
}

ErrorCode addNumbersBinaryRepresentation(const char binaryNumber1[NUMBER_SIZE],
    const char binaryNumber2[NUMBER_SIZE], char binarySumRepresentation[NUMBER_SIZE])
{
    for (unsigned char i = NUMBER_SIZE; i--;)
    {
        binarySumRepresentation[i] = binaryNumber1[i] + binaryNumber2[i];
    }

    for (unsigned char i = NUMBER_SIZE; i--;)
    {
        if (binarySumRepresentation[i] >= 2)
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
