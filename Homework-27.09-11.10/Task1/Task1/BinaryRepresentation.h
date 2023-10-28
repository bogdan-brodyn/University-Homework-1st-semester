#pragma once

#define NUMBER_SIZE sizeof(int) * 8

typedef enum
{
    defaultErrorCode,
    overflow
} ErrorCode;

int getDecimalRepresentation(const char binaryNumber[NUMBER_SIZE]);

// It is necessary to pass an array to the function to write a binary number representation to it
void getBinaryNumberRepresentation(const int number, char binaryNumberRepresentation[NUMBER_SIZE]);

// It is necessary to pass an array to the function to write a binary sum representation to it
// Returns 1 if an overflow occurred
ErrorCode addNumbersBinaryRepresentation(const char binaryNumber1[NUMBER_SIZE],
    const char binaryNumber2[NUMBER_SIZE], char binarySumRepresentation[NUMBER_SIZE]);
