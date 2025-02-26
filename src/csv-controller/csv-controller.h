#ifndef CSV_CONTROLLER_H
void nextRow();
void incrementColumn();
void addEntry(char *entry, int entryType);

enum entryType
{
    NUM,
    STR,
};
#endif