#ifndef CSV_CONTROLLER_H
void nextRow();
void incrementColumn();
void addEntry(char *entry, int entryType);
void csvProgramStart();
void csvProgramEnd();

enum entryType
{
    NUM,
    STR,
};
#endif