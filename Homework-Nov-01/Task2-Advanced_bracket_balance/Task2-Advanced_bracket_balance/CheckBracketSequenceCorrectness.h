#pragma once

#include <stdbool.h>

typedef enum
{
    bracketSequenceDefaultErrorCode,
    bracketSequenceMemoryLack
} BracketSequenceErrorCode;

BracketSequenceErrorCode checkBracketSequenceCorrectness(const char* const bracketSequence, bool* const isCorrect);
