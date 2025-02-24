
%{
    #include "csv-controller/csv-controller.h"
    int csvlex(void);
    void csverror(const char *);
%}

%define api.prefix {csv}

%token COMMA NEWLINE 
%token <s>  LABEL NUMBER

%type <s> entry

%start lines

%union{
    int i;
    float f;
    char * s;
}

%%
lines : line
    | line lines
line:  entries
    |  entries n

entries: e
    | e COMMA entries

e: entry  {addEntry($1); incrementColumn();}
|   {incrementColumn();}
;


entry : LABEL | NUMBER

n: NEWLINE  {nextRow();}

%%
