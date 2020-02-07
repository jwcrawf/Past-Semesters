/*
main.cpp
9/13/17
Jon Crawford

Main for cstring sorting project
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstringsort.h>
#include <cstring>


void PrintStrings(char* array[], size_t count)
{
    for (size_t i = 0; i < count; ++i)
        std::cout << "  " << array[i] << '\n';
}

// copies a string in buffer and returns a pointer to the copy in memory
char* CopyString (const char* buffer)
{
    size_t size = strlen(buffer);
    char* cptr = new char [1 + size];
    strcpy(cptr,buffer);
    cptr [size] = '\0';
    return cptr;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << " ** Arguments required:\n"
                  << "    1: A or D [A for ascii order, D for dictionary order]\n"
                  << "    2: max number of strings [default = 1000]\n"
                  << "    3: max string length     [default = 200]\n"
                  << " ** Try again\n";
        return EXIT_FAILURE;
    }
    size_t buffsize = 201;
    if (argc > 3)
    {
        buffsize = 1 + atoi(argv[3]);
    }
    size_t arraysize = 1000;
    if (argc > 2)
    {
        arraysize = atoi(argv[2]);
    }
    bool ascii = 1;
    if (argv[1][0] != 'a' && argv[1][0] != 'A')
        ascii = 0;

    char* array [arraysize];
    // init array elements to nullptr
    for (size_t i = 0; i < arraysize; ++i) array[i] = nullptr;

    size_t count = 0;
    char buffer [buffsize];
    while (std::cin >> std::setw(buffsize) >> buffer)
    {
        //storing the pointers 
        array[count] = CopyString(buffer);
        ++count;
    }
    std::cout << '\n' << count << " strings as read:\n";
    PrintStrings(array, count);
    if (ascii)
        LexStringSort(array, array + count);
    else
        DictionaryStringSort(array, array + count);
    std::cout << '\n' << count << " strings after sort:\n";
    PrintStrings(array, count);

    // delete array elements
    for (size_t i = 0; i < count; ++i) delete [] array[i];

    return (EXIT_SUCCESS);
}

