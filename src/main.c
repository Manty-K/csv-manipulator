#define _GNU_SOURCE
#include "common-headers.h"
#include "csv-controller/csv-controller.h"
#include "output/output.h"
#include "csv-controller/csv-data.h"

extern FILE *csvin;
extern FILE *rulesin;
extern char *outputFileName;

extern int csvparse(void);
extern int rulesparse(void);

void csverror(char *e)
{
    fprintf(stderr, "CSV Error : %s\n", e);
}

void ruleserror(const char *e)
{
    fprintf(stderr, "Rules Error : %s\n", e);
}

void showUsage(char *progName)
{

    fprintf(stderr, "Usage: %s -c <csv_file> -r <rules_file> -o <output_file>\n", progName);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int opt;
    char *csvFileName = NULL;
    char *rulesFileName = NULL;

    while ((opt = getopt(argc, argv, "c:r:o:h")) != -1)
    {

        switch (opt)
        {
        case 'c':
            csvFileName = strdup(optarg);
            break;
        case 'r':
            rulesFileName = strdup(optarg);
            break;
        case 'o':
            outputFileName = strdup(optarg);
            break;
        case 'h':
            showUsage(argv[0]);
            break;
        default:
            showUsage(argv[0]);
        }
    }

    if (!csvFileName || !outputFileName || !rulesFileName)
    {
        showUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    csvin = fopen(csvFileName, "r");
    if (!csvin)
    {
        perror("Error opening csv input file");
        exit(EXIT_FAILURE);
    }

    csvProgramStart();
    csvparse();
    csvProgramEnd();

    fclose(csvin);

    rulesin = fopen(rulesFileName, "r");
    if (!rulesin)
    {
        perror("Error opening rules input file");
        exit(EXIT_FAILURE);
    }

    rulesparse();

    fclose(rulesin);

    openOutfile();
    processOutput();
    closeOutfile();

    return 0;
}
