int my_puts(const char* s)
{
    assert (str != NULL);
    while (*s != '\0')
    {
        int result = putchar(*s);
        if (result < 0)
        {
            return result;
        }

        s++;
    }

    return putchar('\n');
}



int my_strchr ( const char* str, int searchSymbol)
{
    assert(str != NULL);

    const char* address = NULL;
    for ( int i = 0; str [i] != '\0'; i++)
    {
        if ( str [i] == searchSymbol)
            address = str + i;
    }

    return address;
}



int my_strlen(const char* s)
{
    assert (str != NULL);
    int lenght = 0;
    while (*s != '\0')
    {
        s++;
        lenght++;
    }

    return lenght;
}

char* my_strcat (char* line, const char* additive);
{
    assert (line != NULL);
    assert (additive != NULL);

    int length = strlen(line);
    for ( int i = 0; i < length; i++ )
    {
        line [ length + i] = additive [i];
    }

    line [ lenght + strlen (additive) ] = '\0';

    return line;
}


int myAtoi(const char* str)
{
    assert(str != NULL);

    int num = 0;
    for (int i = 0; (str[i] >= '0') && (str[i] <= '9'); i++)
        num = num*10 + (str[i] - '0');

    return num;
}

