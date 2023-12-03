#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Graph/Graph.h"
#include "../Graph/ColorizeStates.h"

#define TEST1_FILE_PATH "../test1.txt"
#define TEST2_FILE_PATH "../test2.txt"
#define TEST3_FILE_PATH "../test3.txt"
#define TEST4_FILE_PATH "../test4.txt"
#define TEST5_FILE_PATH "../test5.txt"

#define TEST_PASSED 0
#define TEST_FAILED 1

int test(const char* const testFilePath, const int testNumber)
{
    FILE* file = NULL;
    if (fopen_s(&file, testFilePath, "r") != 0)
    {
        printf("File not found. Test: %d\n", testNumber);
        return TEST_FAILED;
    }
    size_t n = 0;
    Graph* graph = getGraphFromStream(file, &n);
    if (graph == NULL)
    {
        printf("Memory lack in getGraphFromStream. Test: %d\n", testNumber);
        fclose(file);
        return TEST_FAILED;
    }
    size_t k = 0;
    size_t* capitals = getCapitalsFromStream(file, &k);
    if (capitals == NULL)
    {
        printf("Memory lack in getCapitalsFromStream. Test: %d\n", testNumber);
        deleteGraph(&graph);
        fclose(file);
        return TEST_FAILED;
    }
    size_t* correctColours = (size_t*)malloc(n * sizeof(size_t));
    if (correctColours == NULL)
    {
        printf("Memory lack. Test: %d\n", testNumber);
        deleteGraph(&graph);
        free(capitals);
        fclose(file);
        return TEST_FAILED;
    }
    for (size_t i = 0; i < n; ++i)
    {
        fscanf_s(file, "%lld", &correctColours[i]);
    }
    fclose(file);

    size_t* colours = colorizeStates(graph, n, capitals, k);
    deleteGraph(&graph);
    free(capitals);
    if (colours == NULL)
    {
        printf("Memory lack. Test: %d\n", testNumber);
        free(correctColours);
        return TEST_FAILED;
    }
    for (size_t node = 0; node < n; ++node)
    {
        if (colours[node] != correctColours[node])
        {
            printf("Incorrect answer. Test: %d\n", testNumber);
            free(correctColours);
            free(colours);
            return TEST_FAILED;
        }
    }
    printf("Test passed. Test: %d\n", testNumber);
    free(correctColours);
    free(colours);
    return TEST_PASSED;
}

int main(void)
{
    bool isTest1Passed = test(TEST1_FILE_PATH, 1) == TEST_PASSED;
    bool isTest2Passed = test(TEST2_FILE_PATH, 2) == TEST_PASSED;
    bool isTest3Passed = test(TEST3_FILE_PATH, 3) == TEST_PASSED;
    bool isTest4Passed = test(TEST4_FILE_PATH, 4) == TEST_PASSED;
    bool isTest5Passed = test(TEST5_FILE_PATH, 5) == TEST_PASSED;
    return isTest1Passed && isTest2Passed && isTest3Passed 
        && isTest4Passed && isTest5Passed ? TEST_PASSED : TEST_FAILED;
}
