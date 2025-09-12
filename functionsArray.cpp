#include <TXLib.h>

void fillingSquareArr (int* array, size_t sizeY, size_t sizeX);

void printSquareArr (int* array, size_t sizeY, size_t sizeX);

int sumSquareArr (int* array, size_t sizeY, size_t sizeX);

int* findNumInSquareArr (int* array, size_t sizeY, size_t sizeX, int requiredNumber);





void fillingSquareArr (int* array, size_t sizeY, size_t sizeX)
{
    assert(array != NULL);

    for (size_t y = 0; y < sizeY; y++)
        for (size_t x = 0; x < sizeX; x++)
            scanf("%d", ((int*) array + y*sizeX + x));
}


void printSquareArr (int* array, size_t sizeY, size_t sizeX)
{
    assert(array != NULL);

    for (size_t y = 0; y < sizeY; y++)
    {
        for (size_t x = 0; x < sizeX; x++)
            printf("[%d][%d] = %d  ", y, x, *((int* )array + y*sizeX + x));
        putchar('\n');
    }
}

int sumSquareArr (int* array, size_t sizeY, size_t sizeX)
{
    assert(array != NULL);

    int sum = 0;
    for (size_t y = 0; y < sizeY; y++)
        for (size_t x = 0; x < sizeX; x++)
            sum += *((int*)array + y*sizeX + x);

    return sum;
}

int* findNumInSquareArr (int* array, size_t sizeY, size_t sizeX, int requiredNumber)
{
    assert(array != NULL);
    int* pointerToRequiredNumber = NULL;

    for (size_t y = 0; y < sizeY; y++)
        for (size_t x = 0; x < sizeX; x++)
            if (*((int*)array + y*sizeX + x) == requiredNumber)
                pointerToRequiredNumber = ((int*)array + y*sizeX + x);

    return pointerToRequiredNumber;
}

void fillingTriangularArr (int* array, size_t sizeOfArr)
{
    assert(array != NULL);

    size_t sizeY = (-1 + (size_t)sqrt(1 + 8*sizeOfArr))/2;
    size_t sizeX = 0;
    for (size_t y = 0; y < sizeY; y++)
    {
        sizeX++;
        for (size_t x = 0; x < sizeX; x++)
            scanf("%d", ((int*)array + (1+y)*y/2 + x));
    }
}
