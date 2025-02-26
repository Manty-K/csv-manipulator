
%{
    #include "csv-controller/csv-controller.h"
    int csvlex(void);
    void csverror(const char *);
%}

%define api.prefix {csv}

%token COMMA NEWLINE 
%token <s>  LABEL NUMBER

%type <s> entry

%start rowsMain


%union{
    int i;
    float f;
    char * s;
}

%%

rowsMain : rows
    | // Empty file
    ;

rows: row
    | row nl
    | row nl rows
    | nl rows
    | nl
    ;

row:  entry
    | cm
    | cm entry
    | row cm entry
    | row cm
    ;

entry : LABEL {addEntry($1,STR);}
    | NUMBER  {addEntry($1,NUM);}
    ;

cm : COMMA  {incrementColumn();}
    ;

nl : NEWLINE {nextRow();}
    ;

%%
