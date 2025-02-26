#include <stdio.h>
#include <stdarg.h>
#include "output.h"

char *outputFileName = NULL;
FILE *outfp;

void openOutfile()
{
    outfp = fopen(outputFileName, "w");

    if (outfp == NULL)
    {
        fprintf(stderr, "File Open Error");
    }
}

int appendFile(const char *format, ...)
{

    if (outfp == NULL)
    {
        fprintf(stderr, "File not initialized!\n");
        return -1;
    }

    va_list args;
    va_start(args, format);
    int result = vfprintf(outfp, format, args);
    va_end(args);

    return result;
}

void closeOutfile()
{
    fclose(outfp);
}