#include <TXLib.h>


void getSquareStringArr (char textArr[][40], size_t numOfLines, size_t lengthOfLines, const char* pathToFile);

void printSquareStringArr (char textArr[][40], size_t numOfLines);

void badGetArrOfPtr(char* arrOfPtr[], size_t numOfLines, const char* pathToFile);

void goodGetArrOfPtr(char* arrOfPtr[], size_t numOfLines, const char* pathToFile);

int main ()
{


}

void getSquareStringArr (char textArr[][40], size_t numOfLines, size_t lengthOfLines, const char* pathToFile)
{
    assert(textArr != NULL);

    FILE* file = fopen(pathToFile, "r");
    assert(file != NULL);

    for (size_t line = 0; line < numOfLines; line++)
        fgets (textArr[line], lengthOfLines, file);

    fclose(file);
}

void printSquareStringArr (char textArr[][40], size_t numOfLines)
{
    assert(textArr != NULL);

    for(size_t line = 0; line < numOfLines; line++)
    {
        printf("[%d] = ", line);
        puts(textArr[line]);
    }
}

void badGetArrOfPtr(char* arrOfPtr[], size_t numOfLines, const char* pathToFile)
{
    assert(arrOfPtr != NULL);

    FILE* file = fopen(pathToFile, "r");
    assert(file != NULL);
    char str[40] = {};

    for(size_t line = 0; line < numOfLines; line++)
    {
        fgets(str, 40, file);
        arrOfPtr[line] = str;
    }

    fclose(file);
}

void goodGetArrOfPtr(char* arrOfPtr[], size_t numOfLines, const char* pathToFile)
{
    assert(arrOfPtr != NULL);

    FILE* file = fopen(pathToFile, "r");
    assert(file != NULL);

    for(size_t line = 0; line < numOfLines; line++)
    {
        char str[40] = {};
        fgets(str, 39, file);
        arrOfPtr[line] = strdup(str);
    }

    fclose(file);
}
