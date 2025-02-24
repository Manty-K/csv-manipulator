
%{
    int csvlex(void);
    void csverror(const char *);
%}

%define api.prefix {csv}

%token NUMBER LABEL COMMA NEWLINE 

%start lines

%%
lines : line
    | line lines
line:  entries
    |  entries NEWLINE

entries: e
    | e COMMA entries

e: entry

entry : LABEL | NUMBER

%%
