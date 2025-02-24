
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
lines : line NEWLINE {nextRow();}
      | lines line NEWLINE  {nextRow();}
      ;

line:  entries
     |
     ;

entries: entry { addEntry($1); incrementColumn(); }
       | entries COMMA entry { addEntry($3); incrementColumn(); }
       | entries COMMA { incrementColumn(); };

entry : LABEL | NUMBER;

%%
