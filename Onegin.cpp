#include <TXLib.h>

struct line {
    char* ptrToString;
    size_t lengthOfString;
};


struct novel {
    char* text;
    struct line* arrOfStringStructs;
    size_t sizeOfText;
    size_t numberOfStrings;
};

void freeStruct (struct novel* structAddress);

size_t getSizeOfFile (int fileDescriptor);

size_t getNumberOfSymbols (char* text, char searchedSymbol);

void fillTheFile (struct novel* structAddress, const char* nameOfFile);

char* copyFileContent (struct novel* structAddress, const char* fileName);

void getStructNovel (struct novel* structAddress, const char* fileName);

void getLengthOfStrings (struct novel* structAddress);

void getArrOfStringStructs (struct novel* structAddress);

void fwriteNovel (struct novel Onegin, FILE* file);

void fwriteNovelAlphabetically (struct novel* structAddress, FILE* file);

void fwriteNovelAlphabeticallyFromEnd (struct novel* structAddress, FILE* file);

void fwriteNovelOriginal (struct novel novelName, FILE* file);

typedef int (*comparefunc_t)(struct line str1, struct line str2);

void intBubbleSort (int* arr, size_t sizeOfArr);

void stringsBubbleSort (struct novel* structAddress, comparefunc_t compareFuncAddress);


int main (void)
{
    struct novel Onegin = {};
    getStructNovel(&Onegin,"Onegin.txt");

    fillTheFile(&Onegin, "result.txt");

    freeStruct(&Onegin);
    return 0;
}

char* copyFileContent (struct novel* structAddress, const char* fileName)
{

    int fileDescriptor = open(fileName, O_RDONLY, 0);
    if (fileDescriptor == -1)
    {
        fprintf(stderr, "Error of opening file \"%s\"", fileName);
        perror("");
        return NULL;
    }

    ssize_t sizeOfFile = getSizeOfFile(fileDescriptor);
    if (sizeOfFile < 1)
    {
        close(fileDescriptor);
        return NULL;
    }

    char* fileCopyBuffer = (char*)calloc(sizeOfFile + 1, sizeof(char));

    size_t numOfReadSymbols = read(fileDescriptor, fileCopyBuffer, sizeOfFile);
    fileCopyBuffer[numOfReadSymbols] = '\0';

    if(close(fileDescriptor) != 0)
    {
        fprintf(stderr, "Error of closing file \"%s\"", fileName);
        perror("");
        return NULL;
    }

    structAddress->sizeOfText = numOfReadSymbols;

    return fileCopyBuffer;
}

void getStructNovel (struct novel* structAddress, const char* fileName)
{

    char* buffer = copyFileContent(structAddress, fileName);
    assert(buffer);

    size_t numberOfStrings    = getNumberOfSymbols(buffer, '\n');
    char** arrOfPtrsToStrings = (char**)calloc(numberOfStrings, sizeof(*arrOfPtrsToStrings));

    structAddress->text               = buffer;
    structAddress->numberOfStrings    = numberOfStrings;

    getArrOfStringStructs(structAddress);

}

void getArrOfStringStructs (struct novel* structAddress)
{
    assert(structAddress);

    structAddress->arrOfStringStructs = (struct line*)calloc(structAddress->numberOfStrings, sizeof(struct line));
    size_t line = 0;
    (structAddress->arrOfStringStructs[line]).ptrToString = structAddress->text;
    (structAddress->arrOfStringStructs[line]).lengthOfString = strlen((structAddress->arrOfStringStructs[line]).ptrToString) + 1;
    line++;

    size_t numOfCharInText = 0;
    for( ; (structAddress->text[numOfCharInText] != '\0') && (line < structAddress->numberOfStrings) ; numOfCharInText++)
    {

        if (structAddress->text[numOfCharInText] == '\n')
        {
            (structAddress->arrOfStringStructs[line]).ptrToString = structAddress->text + numOfCharInText + 1;
            line++;
        }
    }

    getLengthOfStrings(structAddress);
}

void getLengthOfStrings (struct novel* structAddress)
{
    assert(structAddress);

    for(size_t line = 0; line < structAddress->numberOfStrings - 1; line++)
        (structAddress->arrOfStringStructs[line]).lengthOfString = (size_t)((structAddress->arrOfStringStructs[line+1]).ptrToString - (structAddress->arrOfStringStructs[line]).ptrToString);

    (structAddress->arrOfStringStructs[structAddress->numberOfStrings - 1]).lengthOfString = strlen((structAddress->arrOfStringStructs[structAddress->numberOfStrings - 1]).ptrToString) + 1;
}

void fwriteNovel (struct novel nameOfNovel, FILE* file)
{
    assert(file);

    for(size_t line = 0; line < nameOfNovel.numberOfStrings; line++)
    {
        assert(((nameOfNovel.arrOfStringStructs)[line]).ptrToString);
        myputs(((nameOfNovel.arrOfStringStructs)[line]).ptrToString, file);
    }
}

void freeStruct (struct novel* structAddress)
{
    assert(structAddress);

    free(structAddress->text);
    free(structAddress->arrOfStringStructs);
}

size_t getSizeOfFile (int fileDescriptor)
{
    struct stat fileInfo = {};

    if (fstat(fileDescriptor, &fileInfo) == 0)
        return fileInfo.st_size;

    perror("Error of getting the size of the file");
    return -1;
}

size_t getNumberOfSymbols (char* text, char searchedSymbol)
{
    assert(text);

    size_t numOfSymbolsFound = 0;
    for(size_t numOfChar = 0; text[numOfChar] != '\0'; numOfChar++)
        if (text[numOfChar] == searchedSymbol)
            numOfSymbolsFound++;

    return numOfSymbolsFound;
}

void fillTheFile (struct novel* structAddress, const char* nameOfFile)
{
    assert(structAddress);
    assert(nameOfFile);

    FILE* file = fopen("result.txt", "w");
    if (file == NULL)
    {
        fprintf(stderr, "Error of opening file \"%s\"", nameOfFile);
        perror("");
        return;
    }

    fwriteNovelAlphabetically(structAddress, file);
    fwriteNovelAlphabeticallyFromEnd(structAddress, file);
    fwriteNovelOriginal(*structAddress, file);

    if (fclose(file) != 0)
    {
        fprintf(stderr, "Error of closing file \"%s\"", nameOfFile);
        perror("");
    }

}

typedef int (*comparefunc_t)(const struct line str1, const struct line str2);

void intBubbleSort (int* arr, size_t sizeOfArr)
{
    for(unsigned int numOfCycle = 0; numOfCycle < sizeOfArr; numOfCycle++)
        for (size_t numOfChar = 0; numOfChar < (sizeOfArr - numOfCycle); numOfChar++)
        {
            if (arr[numOfChar] > arr[numOfChar + 1])
            {
                int cell = arr[numOfChar];
                arr[numOfChar] = arr[numOfChar + 1];
                arr[numOfChar + 1] = cell;
            }
        }
}

void stringsBubbleSort (struct novel* structAddress, comparefunc_t compareFuncAddress)
{
    for(unsigned int numOfCycle = 0; numOfCycle < structAddress->numberOfStrings; numOfCycle++)

        for (size_t numOfPtr = 0; numOfPtr < (structAddress->numberOfStrings - numOfCycle - 1); numOfPtr++)
        {

            assert(((structAddress->arrOfStringStructs)[numOfPtr]).ptrToString);
            assert(((structAddress->arrOfStringStructs)[numOfPtr + 1]).ptrToString);

            if ((*compareFuncAddress)((structAddress->arrOfStringStructs)[numOfPtr], (structAddress->arrOfStringStructs)[numOfPtr + 1]) > 0)
            {
                struct line cell = (structAddress->arrOfStringStructs)[numOfPtr];
                (structAddress->arrOfStringStructs)[numOfPtr] = (structAddress->arrOfStringStructs)[numOfPtr + 1];
                (structAddress->arrOfStringStructs)[numOfPtr + 1] = cell;
            }
        }
}
